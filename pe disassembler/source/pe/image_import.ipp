/// image_import.ipp

#pragma once

#include "../pe disassembler.hpp"
#include "image_import.hpp"

inline image_import_list::image_import::thunk_iterator<IMAGE_THUNK_DATA32>::thunk_iterator() :
	IMAGE_THUNK_DATA32({})
{ }

inline image_import_list::image_import::thunk_iterator<IMAGE_THUNK_DATA32>::thunk_iterator(IMAGE_THUNK_DATA32&& th) :
	IMAGE_THUNK_DATA32(th)
{ }

inline image_import_list::image_import::thunk_iterator<rva<IMAGE_THUNK_DATA32>>::thunk_iterator(void* const base, unsigned long const offset) :
	rva<IMAGE_THUNK_DATA32>(base, offset)
{ }

inline image_import_list::image_import::thunk_iterator<rva<IMAGE_THUNK_DATA32>>::thunk_iterator(rva<IMAGE_THUNK_DATA32> const& rhs) :
	rva<IMAGE_THUNK_DATA32>(rhs)
{ }

inline bool image_import_list::image_import::thunk_iterator<rva<IMAGE_THUNK_DATA32>>::operator!=(thunk_iterator<IMAGE_THUNK_DATA32> const& rhs)
{
	return (*this)->u1.AddressOfData != rhs.u1.AddressOfData;
}

inline image_import_list::image_import::thunk_iterator<rva<IMAGE_THUNK_DATA32>> image_import_list::image_import::thunk_iterator<rva<IMAGE_THUNK_DATA32>>::operator++()
{
	return *this = rva<IMAGE_THUNK_DATA32>(base, offset) + 1;
}

inline image_import_list::image_import::thunk image_import_list::image_import::thunk_iterator<rva<IMAGE_THUNK_DATA32>>::operator*()
{
	return thunk(reinterpret_cast<void *>(base), offset);
}

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
