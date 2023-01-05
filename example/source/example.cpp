/// example.cpp

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

	auto imports = nt.get_directory<image_import>();

	//auto hModule = (void*)LoadLibrary(LR"(C:\Users\cole\Desktop\messagebox.dll)");
	//auto p = (void*)mb.data.get();
	auto hModule = (void*)mb.data.get();
	const auto pDOSHeaders = reinterpret_cast<IMAGE_DOS_HEADER*>(hModule);
	const auto pNTHeaders = reinterpret_cast<IMAGE_NT_HEADERS32*>(std::uintptr_t(hModule) + pDOSHeaders->e_lfanew);
	const auto pImportList = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(std::uintptr_t(hModule) + pNTHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);

	for (auto i = 0;; i++)
	{
		const auto pImport = pImportList[i];
		const auto sz1 = reinterpret_cast<const char*>(std::uintptr_t(hModule) + pImport.Name);

		auto d = image_import(imports[i]);
		auto f = d.first_thunk();
		auto* im = &pImportList[i];
		
		for (auto j = 0;; j++) {
			auto& o = reinterpret_cast<IMAGE_THUNK_DATA32*>(std::uintptr_t(hModule) + pImport.OriginalFirstThunk)[j];
			const auto szImport = reinterpret_cast<const char*>((o.u1.Ordinal & IMAGE_ORDINAL_FLAG32) > 0 ? IMAGE_ORDINAL32(o.u1.Ordinal)
				: std::uintptr_t(reinterpret_cast<IMAGE_IMPORT_BY_NAME*>(std::uintptr_t(hModule) + o.u1.AddressOfData)->Name));

			auto f1 = image_thunk_data(f[j]);

			auto sz = f1.name();

			std::cout << *sz << std::endl;
		}
		std::cout << "test" << std::endl;
	}

	while (true);
}
