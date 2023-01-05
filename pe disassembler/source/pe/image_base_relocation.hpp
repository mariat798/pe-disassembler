/// base_relocation.hpp

#pragma once

class image_base_relocation : public rva<IMAGE_BASE_RELOCATION>
{
public:

	image_base_relocation(void* const base, unsigned long const offset);
	image_base_relocation(rva<IMAGE_BASE_RELOCATION> const rhs);
};
