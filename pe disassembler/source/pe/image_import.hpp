/// image_import.hpp

#pragma once

class image_thunk_data : public rva<IMAGE_THUNK_DATA32>
{
public:

	image_thunk_data(void* const base, unsigned long const offset);
	image_thunk_data(rva<IMAGE_THUNK_DATA32> const rhs);

	rva<const char> name();
};

class image_import_list : public rva<IMAGE_IMPORT_DESCRIPTOR>
{
public:

	class image_import : public rva<IMAGE_IMPORT_DESCRIPTOR>
	{
	public:

		image_import(void* const base, unsigned long const offset);
		image_import(rva<IMAGE_IMPORT_DESCRIPTOR> const rhs);

		rva<IMAGE_THUNK_DATA32> first_thunk();
		const char* name();
	};

	template<typename T>
	class image_import_iterator: T
	{ };

	template<>
	class image_import_iterator<IMAGE_IMPORT_DESCRIPTOR> : public IMAGE_IMPORT_DESCRIPTOR
	{
	public:

		image_import_iterator();
		image_import_iterator(IMAGE_IMPORT_DESCRIPTOR&& im);
	};

	template<>
	class image_import_iterator<rva<IMAGE_IMPORT_DESCRIPTOR>>: public rva<IMAGE_IMPORT_DESCRIPTOR>
	{
	public:

		image_import_iterator(void* const base, unsigned long const offset);
		image_import_iterator(rva<IMAGE_IMPORT_DESCRIPTOR> const & rhs);

		bool operator!=(image_import_iterator<IMAGE_IMPORT_DESCRIPTOR> const& rhs);
		image_import_iterator<rva<IMAGE_IMPORT_DESCRIPTOR>> operator++();
		image_import operator*();
	};

	image_import_list(void* const base, unsigned long const offset);

	image_import_iterator<rva<IMAGE_IMPORT_DESCRIPTOR>> begin();
	image_import_iterator<IMAGE_IMPORT_DESCRIPTOR> end();
};

#include "image_import.ipp"
