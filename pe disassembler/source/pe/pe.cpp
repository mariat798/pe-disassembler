/// pe.cpp

#include "../pe disassembler.hpp"

pe::pe(void* const ptr, std::size_t const size)
{
	auto dos = dos_header(ptr);
	auto nt = nt_header(ptr, dos->e_lfanew);

	data = std::make_unique<unsigned char[]>(nt->OptionalHeader.SizeOfImage);

	std::memcpy(data.get(), ptr, nt->OptionalHeader.SizeOfHeaders);

	auto const delta = reinterpret_cast<std::uintptr_t>(data.get()) - nt->OptionalHeader.ImageBase;
	
	for (auto section: nt.get_sections())
	{
		auto sz = section->Name;

		if (0 == section->SizeOfRawData)
			continue;

		std::memcpy(data.get() + section->VirtualAddress,
					reinterpret_cast<unsigned char const*>(ptr) + section->PointerToRawData,
					section->SizeOfRawData);
	}

	auto new_nt = nt_header(data.get(), dos_header(data.get())->e_lfanew);

	for (auto reloc : new_nt.get_directory<image_base_relocations>())
		for (auto p : reloc)
		{
			auto patch = rva<DWORD>(data.get(), reloc->VirtualAddress + *p);

			*patch += delta;
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
