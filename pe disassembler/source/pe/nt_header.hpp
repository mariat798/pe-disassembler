/// nt_header.hpp

#pragma once

class nt_header: public header<IMAGE_NT_HEADERS32>
{
public:

	nt_header(void* const base, unsigned long const e_lfanew);

	template<typename T>
	T get_directory();

	template<>
	image_export
	get_directory<image_export>();
	template<>
	image_import_list
	get_directory<image_import_list>();
	template<>
	image_base_relocations
	get_directory<image_base_relocations>();

	section_list get_sections();
};

#include "nt_header.ipp"
