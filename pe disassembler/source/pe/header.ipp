/// header.ipp

#pragma once

#include "../pe disassembler.hpp"

template<typename T>
header<T>::header(void* const base, unsigned long const offset):
	rva<T>(base, offset)
{ }
