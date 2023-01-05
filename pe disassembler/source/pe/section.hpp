/// section.hpp

#pragma once

class section : public rva<IMAGE_SECTION_HEADER>
{
public:

	section(void* const base, unsigned long const offset);
	section(rva<IMAGE_SECTION_HEADER> const rhs);
};
