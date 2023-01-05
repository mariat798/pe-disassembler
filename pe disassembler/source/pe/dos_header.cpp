/// dos_header.cpp

#include "../pe disassembler.hpp"

dos_header::dos_header(void* base) :
	header<_IMAGE_DOS_HEADER>(base, 0)
{ }
