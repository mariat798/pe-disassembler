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
inline image_import
nt_header::get_directory<image_import>()
{
	return image_import(
		reinterpret_cast<void*>(base),
		(*this)->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
}

template<>
inline image_base_relocation
nt_header::get_directory<image_base_relocation>()
{
	return image_base_relocation(
		reinterpret_cast<void*>(base),
		(*this)->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress);
}
