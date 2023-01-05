/// header.hpp

#pragma once

template<typename T>
class header : public rva<T>
{
public:

	header(void* const base, unsigned long const offset);
};

#include "header.ipp"
