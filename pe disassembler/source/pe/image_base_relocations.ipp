/// image_base_relocations.ipp

#pragma once

#include "../pe disassembler.hpp"

inline image_base_relocations::block_iterator<IMAGE_BASE_RELOCATION>::block_iterator() :
	IMAGE_BASE_RELOCATION({})
{ }

inline image_base_relocations::block_iterator<IMAGE_BASE_RELOCATION>::block_iterator(IMAGE_BASE_RELOCATION&& rhs) :
	IMAGE_BASE_RELOCATION(rhs)
{ }

inline image_base_relocations::block_iterator<rva<IMAGE_BASE_RELOCATION>>::block_iterator(void* const base, unsigned long const offset) :
	rva<IMAGE_BASE_RELOCATION>(base, offset)
{ }

inline image_base_relocations::block_iterator<rva<IMAGE_BASE_RELOCATION>>::block_iterator(rva<IMAGE_BASE_RELOCATION> const& rhs) :
	rva<IMAGE_BASE_RELOCATION>(rhs)
{ }

inline image_base_relocations::block_table
image_base_relocations::block_iterator<rva<IMAGE_BASE_RELOCATION>>::operator*()
{
	return block_table(reinterpret_cast<void *>(base), offset);
}

inline image_base_relocations::block_iterator<rva<IMAGE_BASE_RELOCATION>>&
image_base_relocations::block_iterator<rva<IMAGE_BASE_RELOCATION>>::operator++()
{
	advance((*this)->SizeOfBlock);

	return *this;
}

inline bool image_base_relocations::block_iterator<rva<IMAGE_BASE_RELOCATION>>::operator!=(block_iterator<IMAGE_BASE_RELOCATION> const& rhs)
{
	return (*this)->VirtualAddress != rhs.VirtualAddress;
}
