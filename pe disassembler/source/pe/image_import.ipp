/// image_import.ipp

#pragma once

#include "../pe disassembler.hpp"

inline image_import_list::image_import_iterator<IMAGE_IMPORT_DESCRIPTOR>::image_import_iterator() :
	IMAGE_IMPORT_DESCRIPTOR({})
{ }

inline image_import_list::image_import_iterator<IMAGE_IMPORT_DESCRIPTOR>::image_import_iterator(IMAGE_IMPORT_DESCRIPTOR&& im) :
	IMAGE_IMPORT_DESCRIPTOR(im)
{ }

inline image_import_list::image_import_iterator<rva<IMAGE_IMPORT_DESCRIPTOR>>::image_import_iterator(void* const base, unsigned long const offset) :
	rva<IMAGE_IMPORT_DESCRIPTOR>(base, offset)
{ }

inline image_import_list::image_import_iterator<rva<IMAGE_IMPORT_DESCRIPTOR>>::image_import_iterator(rva<IMAGE_IMPORT_DESCRIPTOR> const& rhs) :
	rva<IMAGE_IMPORT_DESCRIPTOR>(rhs)
{ }

inline bool image_import_list::image_import_iterator<rva<IMAGE_IMPORT_DESCRIPTOR>>::operator!=(image_import_iterator<IMAGE_IMPORT_DESCRIPTOR> const& rhs)
{
	return (*this)->Characteristics != rhs.Characteristics && (*this)->OriginalFirstThunk != rhs.OriginalFirstThunk;
}

inline image_import_list::image_import_iterator<rva<IMAGE_IMPORT_DESCRIPTOR>>
image_import_list::image_import_iterator<rva<IMAGE_IMPORT_DESCRIPTOR>>::operator++()
{
	return *this = rva<IMAGE_IMPORT_DESCRIPTOR>(base, offset) + 1;
}

inline image_import_list::image_import
image_import_list::image_import_iterator<rva<IMAGE_IMPORT_DESCRIPTOR>>::operator*()
{
	return image_import(reinterpret_cast<void *>(base), offset);
}
