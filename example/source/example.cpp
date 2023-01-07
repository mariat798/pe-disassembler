/// example.cpp

#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <iostream>
#include <vector>
#include <fstream>

#define NO_TYPES
#include <pe disassembler.hpp>
#pragma comment(lib, "pe disassembler.lib")

std::vector<char> read_file()
{
	std::ifstream file(R"(C:\Users\cole\Desktop\messagebox.dll)", std::ios::binary);
	std::vector<char> out;

	file.seekg(0, std::ios::end);
	
	auto size = file.tellg();
	
	file.seekg(0);
	out.resize(size);
	file.read(&out[0], size);

	return out;
}

void main()
{
	auto data = read_file();

	auto mb = pe(&data[0], data.size());
	auto dos = mb.get_dos();
	auto nt = mb.get_nt();

	auto imports = nt.get_directory<image_import_list>();
	auto exports = nt.get_directory<image_export>();
	auto relocs  = nt.get_directory<image_base_relocations>();

	std::time_t time = nt->FileHeader.TimeDateStamp;

	std::cout << "\n=========================" << std::endl;
	std::cout << "\tNT HEADER INFO" << std::endl;
	std::cout << "=========================\n" << std::endl;

	std::cout << "IMAGE BASE: \t0x" << std::hex << nt->OptionalHeader.ImageBase << std::endl;
	std::cout << "IMAGE SIZE: \t0x" << std::hex << nt->OptionalHeader.SizeOfImage << std::endl;
	std::cout << "BUILD  TIME: \t" << std::asctime(std::localtime(&time)) << std::endl;
	std::cout << "ENTRY POINT: 0x" << std::hex << nt->OptionalHeader.AddressOfEntryPoint << std::endl;

	std::cout << "\n=========================" << std::endl;
	std::cout << "\tSECTIONS" << std::endl;
	std::cout << "=========================\n" << std::endl;

	for (auto s : nt.get_sections())
	{
		std::cout << s->Name << ":" << std::endl;
		std::cout << "\tSIZE: " << "\t0x" << std::hex << s->SizeOfRawData << std::endl;
		std::cout << "\tRVA: " << "\t0x" << std::hex << s->VirtualAddress << std::endl;
	}

	std::cout << "\n=========================" << std::endl;
	std::cout << "\tEXPORTS" << std::endl;
	std::cout << "=========================\n" << std::endl;

	for (auto e : exports)
		std::cout << e.first << " at IMAGE_BASE + 0x" 
				  << std::hex << e.second << std::endl;

	std::cout << "\n=========================" << std::endl;
	std::cout << "\tIMPORTS" << std::endl;
	std::cout << "=========================\n" << std::endl;

	for (auto i : imports)
	{
		std::cout << i.name() << ":" << std::endl;

		for (auto t : i)
			std::cout << "\t" << t.name() << std::endl;

		std::cout << std::endl;
	}

	std::cout << "=========================" << std::endl;
	std::cout << "\tRELOCATIONS" << std::endl;
	std::cout << "=========================\n" << std::endl;

	for (auto reloc : relocs)
		std::cout << "TABLE AT IMAGE_BASE + 0x" << std::hex 
				  << reloc->VirtualAddress << " (" << std::dec 
				  << reloc.entries() << " ENTRIES)" << std::endl;

	while (true);
}
