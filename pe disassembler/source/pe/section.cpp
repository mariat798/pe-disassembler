/// section.cpp

#include "../pe disassembler.hpp"

section_list::section::section(void* const base, unsigned long const offset) :
	rva<IMAGE_SECTION_HEADER>(base, offset)
{ }

section_list::section::section(rva<IMAGE_SECTION_HEADER> const rhs) :
	rva<IMAGE_SECTION_HEADER>(rhs)
{ }

section_list::section_list(void* const base, unsigned long const offset, unsigned const n) :
	rva<IMAGE_SECTION_HEADER>(base, offset), n(n)
{ }

section_list::section_iterator section_list::begin()
{
	return section_iterator(this);
}

section_list::section_iterator section_list::end()
{
	return section_iterator(this, n);
}

section_list::section_iterator::section_iterator(section_list* const list, unsigned const i) :
	list(list), i(i)
{ }

section_list::section section_list::section_iterator::operator*()
{
	return section(reinterpret_cast<void *>(list->base), list->offset + i * sizeof(IMAGE_SECTION_HEADER));
}

section_list::section_iterator& section_list::section_iterator::operator++()
{
	i++;

	return *this;
}

bool section_list::section_iterator::operator!=(section_iterator const& rhs)
{
	return i != rhs.i;
}
