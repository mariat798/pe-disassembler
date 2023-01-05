/// image_base_relocation.cpp

#include "../pe disassembler.hpp"

image_base_relocation::image_base_relocation(void* const base, unsigned long const offset) :
	rva<IMAGE_BASE_RELOCATION>(base, offset)
{ }

image_base_relocation::image_base_relocation(rva<IMAGE_BASE_RELOCATION> const rhs) :
	rva<IMAGE_BASE_RELOCATION>(rhs)
{ }
