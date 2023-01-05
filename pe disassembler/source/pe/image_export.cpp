/// image_export.cpp

#include "../pe disassembler.hpp"

image_export::image_export(void* const base, unsigned long const offset) :
	rva<IMAGE_EXPORT_DIRECTORY>(base, offset)
{ }
