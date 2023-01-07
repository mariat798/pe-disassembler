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

	auto imports = nt.get_directory<image_import_list>();
	auto exports = nt.get_directory<image_export>();

	std::cout << "=========================" << std::endl;
	std::cout << "\tEXPORTS" << std::endl;
	std::cout << "=========================\n" << std::endl;

	for (auto e : exports)
	{
		std::cout << e.first << " at IMAGE_BASE + 0x" << std::hex << e.second << std::endl;
	}

	std::cout << "\n=========================" << std::endl;
	std::cout << "\tIMPORTS" << std::endl;
	std::cout << "=========================\n" << std::endl;

	for (auto i : imports)
	{
		std::cout << i.name() << ":" << std::endl;
	}

	/*for (auto i = 0;; i++)
	{
		auto d = image_import(imports[i]);

		if (!d)
			break;

		std::cout << &d.name() << std::endl;
		auto f = d.first_thunk();
		
		for (auto j = 0;; j++) {

			auto f1 = image_thunk_data(f[j]);

			auto name = f1.name();

			if (!name)
				break;

			std::cout << "\t" << &name << std::endl;
		}
	}*/

	while (true);
}
