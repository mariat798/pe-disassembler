/// image_export.cpp

#include "../pe disassembler.hpp"

image_export::export_iterator::export_iterator(image_export* const exports, unsigned const i) :
	exports(exports), i(i)
{ }

image_export::export_iterator& image_export::export_iterator::operator++()
{
	i++;
	return *this;
}

bool image_export::export_iterator::operator!=(const export_iterator& rhs)
{
	return i != rhs.i;
}

bool image_export::export_iterator::operator==(const export_iterator& rhs)
{
	return i == rhs.i;
}

std::pair<const char*, unsigned long> image_export::export_iterator::operator*()
{
	const auto f = *exports->name_table()[i];
	return std::make_pair<const char*, unsigned long>(
		reinterpret_cast<const char*>(exports->base + *exports->name_table()[i]),
		std::move(*exports->function_table()[i]));
}

rva<unsigned long> image_export::function_table()
{
	return rva<unsigned long>(base, (*this)->AddressOfFunctions);
}

rva<unsigned long> image_export::name_table()
{
	return rva<unsigned long>(base, (*this)->AddressOfNames);
}

image_export::image_export(void* const base, unsigned long const offset) :
	rva<IMAGE_EXPORT_DIRECTORY>(base, offset)
{ }

image_export::export_iterator image_export::begin()
{
	return export_iterator(this, 0);
}

image_export::export_iterator image_export::end()
{
	return export_iterator(this, (*this)->NumberOfNames);
}
