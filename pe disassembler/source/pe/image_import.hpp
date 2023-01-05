/// image_import.hpp

#pragma once

class image_thunk_data : public rva<IMAGE_THUNK_DATA32>
{
public:

	image_thunk_data(void* const base, unsigned long const offset);
	image_thunk_data(rva<IMAGE_THUNK_DATA32> const rhs);

	rva<const char*> name();
};

class image_import: public rva<IMAGE_IMPORT_DESCRIPTOR>
{
public:

	image_import(void* const base, unsigned long const offset);
	image_import(rva<IMAGE_IMPORT_DESCRIPTOR> const rhs);

	rva<IMAGE_THUNK_DATA32> first_thunk();
};
