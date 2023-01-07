/// nt_header.ipp

#include "../pe disassembler.hpp"

#pragma once

template<>
inline image_export
nt_header::get_directory<image_export>()
{
	return image_export(
		reinterpret_cast<void*>(base),
		(*this)->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
}

template<>
inline image_import_list
nt_header::get_directory<image_import_list>()
{
	return image_import_list(
		reinterpret_cast<void*>(base),
		(*this)->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
}

template<>
inline image_base_relocations
nt_header::get_directory<image_base_relocations>()
{
	return image_base_relocations(
		reinterpret_cast<void*>(base),
		(*this)->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress);
}
