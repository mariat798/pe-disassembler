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
	image_import
	get_directory<image_import>();
	template<>
	image_base_relocation
	get_directory<image_base_relocation>();
};

#include "nt_header.ipp"
