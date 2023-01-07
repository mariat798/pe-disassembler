/// image_base_relocations.hpp

#pragma once

class image_base_relocations : public rva<IMAGE_BASE_RELOCATION>
{
public:

	class block_table : public rva<IMAGE_BASE_RELOCATION>
	{
	public:

		class block_table_entry : public rva<WORD>
		{
		public:

			block_table_entry(void* const base, unsigned long const offset);
			block_table_entry(rva<WORD> const& rhs);
		};

		class block_table_iterator : public rva<WORD>
		{
		private:

			unsigned i;

		public:

			block_table_iterator(void * const base, unsigned const offset, unsigned const i = 0);

			block_table_entry operator*();
			block_table_iterator& operator++();
			bool operator!=(block_table_iterator const& rhs);
		};

		block_table(void* const base, unsigned long const offset);
		block_table(rva<IMAGE_BASE_RELOCATION> const& rhs);

		std::size_t entries();

		block_table_iterator begin();
		block_table_iterator end();

		friend class block_table_iterator;
	};

	template<typename T>
	class block_iterator : public T
	{ };

	template<>
	class block_iterator<IMAGE_BASE_RELOCATION> : public IMAGE_BASE_RELOCATION
	{
	public:

		block_iterator();
		block_iterator(IMAGE_BASE_RELOCATION&& rhs);
	};

	template<>
	class block_iterator<rva<IMAGE_BASE_RELOCATION>> : public rva<IMAGE_BASE_RELOCATION>
	{
	public:

		block_iterator(void* const base, unsigned long const offset);
		block_iterator(rva<IMAGE_BASE_RELOCATION> const& rhs);

		block_table operator*();
		block_iterator<rva<IMAGE_BASE_RELOCATION>>& operator++();
		bool operator!=(block_iterator<IMAGE_BASE_RELOCATION> const& rhs);
	};

	image_base_relocations(void* const base, unsigned long const offset);
	image_base_relocations(rva<IMAGE_BASE_RELOCATION> const rhs);

	block_iterator<rva<IMAGE_BASE_RELOCATION>> begin();
	block_iterator<IMAGE_BASE_RELOCATION> end();
};

#include "image_base_relocations.ipp"
