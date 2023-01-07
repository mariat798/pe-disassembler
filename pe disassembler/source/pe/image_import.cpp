/// image_import.cpp

#include "../pe disassembler.hpp"

image_thunk_data::image_thunk_data(void* const base, unsigned long const offset) :
	rva<IMAGE_THUNK_DATA32>(base, offset)
{ }

image_thunk_data::image_thunk_data(rva<IMAGE_THUNK_DATA32> const rhs) :
	rva<IMAGE_THUNK_DATA32>(rhs)
{ }

image_import_list::image_import::image_import(void* const base, unsigned long const offset) :
	rva<IMAGE_IMPORT_DESCRIPTOR>(base, offset)
{ }

image_import_list::image_import::image_import(rva<IMAGE_IMPORT_DESCRIPTOR> const rhs) :
	rva<IMAGE_IMPORT_DESCRIPTOR>(rhs)
{ }

image_import_list::image_import::thunk_iterator<rva<IMAGE_THUNK_DATA32>> image_import_list::image_import::begin()
{
	return thunk_iterator<rva<IMAGE_THUNK_DATA32>>(reinterpret_cast<void *>(base), (*this)->OriginalFirstThunk);
}

image_import_list::image_import::thunk_iterator<IMAGE_THUNK_DATA32> image_import_list::image_import::end()
{
	return thunk_iterator<IMAGE_THUNK_DATA32>();
}

const char* image_import_list::image_import::name()
{
	return reinterpret_cast<const char*>(base + (*this)->Name);
}

rva<const char> image_thunk_data::name()
{
	if ((*this)->u1.Ordinal & IMAGE_ORDINAL_FLAG32)
		return rva<const char>(IMAGE_ORDINAL32((*this)->u1.Ordinal), 0);

	if (!(*this)->u1.AddressOfData)
		return rva<const char>(nullptr, 0);

	auto const import_by_name = rva<IMAGE_IMPORT_BY_NAME>(base, (*this)->u1.AddressOfData);

	return rva<const char>(&import_by_name->Name, 0);
}

image_import_list::image_import_list(void* const base, unsigned long const offset) :
	rva<IMAGE_IMPORT_DESCRIPTOR>(base, offset)
{ }

image_import_list::image_import_iterator<rva<IMAGE_IMPORT_DESCRIPTOR>> image_import_list::begin()
{
	return image_import_iterator<rva<IMAGE_IMPORT_DESCRIPTOR>>(reinterpret_cast<void *>(base), offset);
}

image_import_list::image_import_iterator<IMAGE_IMPORT_DESCRIPTOR> image_import_list::end()
{
	return image_import_iterator<IMAGE_IMPORT_DESCRIPTOR>();
}

image_import_list::image_import::thunk::thunk(void* const base, unsigned long const offset) :
	rva<IMAGE_THUNK_DATA32>(base, offset)
{ }

const char* image_import_list::image_import::thunk::name()
{
	if ((*this)->u1.Ordinal & IMAGE_ORDINAL_FLAG32)
		return reinterpret_cast<const char*>(IMAGE_ORDINAL32((*this)->u1.Ordinal), 0);

	if (!(*this)->u1.AddressOfData)
		return reinterpret_cast<const char*>(nullptr, 0);

	auto const import_by_name = rva<IMAGE_IMPORT_BY_NAME>(base, (*this)->u1.AddressOfData);

	return reinterpret_cast<const char*>(&import_by_name->Name );
}
