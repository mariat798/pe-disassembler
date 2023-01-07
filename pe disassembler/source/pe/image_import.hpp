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

		class thunk : public rva<IMAGE_THUNK_DATA32>
		{
		public:

			thunk(void* const base, unsigned long const offset);

			const char* name();
		};

		template<typename T>
		class thunk_iterator : T
		{ };

		template<>
		class thunk_iterator<IMAGE_THUNK_DATA32> : public IMAGE_THUNK_DATA32
		{
		public:

			thunk_iterator();
			thunk_iterator(IMAGE_THUNK_DATA32&& th);
		};

		template<>
		class thunk_iterator<rva<IMAGE_THUNK_DATA32>> : public rva<IMAGE_THUNK_DATA32>
		{
		public:

			thunk_iterator(void* const base, unsigned long const offset);
			thunk_iterator(rva<IMAGE_THUNK_DATA32> const& rhs);

			bool operator!=(thunk_iterator<IMAGE_THUNK_DATA32> const& rhs);
			thunk_iterator<rva<IMAGE_THUNK_DATA32>> operator++();
			thunk operator*();
		};

		image_import(void* const base, unsigned long const offset);
		image_import(rva<IMAGE_IMPORT_DESCRIPTOR> const rhs);

		thunk_iterator<rva<IMAGE_THUNK_DATA32>> begin();
		thunk_iterator<IMAGE_THUNK_DATA32> end();

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
