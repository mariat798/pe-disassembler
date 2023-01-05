/// pe.cpp

#include "../pe disassembler.hpp"

pe::pe(void* const ptr, std::size_t const size)
{
	auto dos = dos_header(ptr);
	auto nt = nt_header(ptr, dos->e_lfanew);

	data = std::make_unique<unsigned char[]>(nt->OptionalHeader.SizeOfImage);

	std::memcpy(data.get(), ptr, nt->OptionalHeader.SizeOfHeaders);

	auto const sect = section(data.get(), dos->e_lfanew + sizeof(IMAGE_NT_HEADERS32));
	auto const delta = reinterpret_cast<std::uintptr_t>(data.get()) - nt->OptionalHeader.ImageBase;
	
	for (auto i = 0; i < nt->FileHeader.NumberOfSections; i++)
	{
		auto const s = sect[i];
		auto sz = s->Name;

		if (0 == s->SizeOfRawData)
			continue;

		std::memcpy(data.get() + s->VirtualAddress,
					reinterpret_cast<unsigned char const*>(ptr) + sect->PointerToRawData,
					sect->SizeOfRawData);
	}

	unsigned char * pBase = data.get();
	auto* pOpt = &reinterpret_cast<IMAGE_NT_HEADERS32*>(pBase + reinterpret_cast<_IMAGE_DOS_HEADER*>((uintptr_t)pBase)->e_lfanew)->OptionalHeader;
	IMAGE_BASE_RELOCATION* pRelocData = reinterpret_cast<IMAGE_BASE_RELOCATION*>(pBase + pOpt->DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress);

	auto new_nt = nt_header(data.get(), dos_header(data.get())->e_lfanew);

	auto reloc = new_nt.get_directory<image_base_relocation>();

	while (reloc->VirtualAddress)
	{
		auto s = reloc->SizeOfBlock;
		auto const entries = (reloc->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / sizeof(WORD);
		auto first_patch = rva<WORD>(&reloc, sizeof(IMAGE_BASE_RELOCATION));

		for (auto i = 0u; i < entries; i++)
		{
			auto patch = rva<DWORD>(&first_patch, *first_patch[i] & 0xFFF);

			*patch += delta;
		}

		reloc.advance(reloc->SizeOfBlock);
	}

	if (!valid_pe())
		throw std::runtime_error("invalid PE");
}

bool pe::valid_pe()
{
	auto const dos = get_dos();
	
	if (0 != std::memcmp(&dos->e_magic, DOS_SIGNATURE, DOS_SIGNATURE_LENGTH))
		return false;

	auto const nt = get_nt();

	return 0 == std::memcmp(&nt->Signature, NT_SIGNATURE, NT_SIGNATURE_LENGTH);
}

dos_header pe::get_dos()
{
	return dos_header(data.get());
}

nt_header pe::get_nt()
{
	auto const dos = get_dos();

	return nt_header(data.get(), dos->e_lfanew);
}
