/// section.cpp

#include "../pe disassembler.hpp"

section::section(void* const base, unsigned long const offset) :
	rva<IMAGE_SECTION_HEADER>(base, offset)
{ }

section::section(rva<IMAGE_SECTION_HEADER> const rhs) :
	rva<IMAGE_SECTION_HEADER>(rhs)
{ }
