/// nt_header.cpp

#include "../pe disassembler.hpp"

nt_header::nt_header(void* const base, unsigned long const e_lfanew) :
	header<IMAGE_NT_HEADERS32>(base, e_lfanew)
{ }
