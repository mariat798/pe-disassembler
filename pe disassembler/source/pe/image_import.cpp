/// image_import.cpp

#include "../pe disassembler.hpp"

image_thunk_data::image_thunk_data(void* const base, unsigned long const offset) :
	rva<IMAGE_THUNK_DATA32>(base, offset)
{ }

image_thunk_data::image_thunk_data(rva<IMAGE_THUNK_DATA32> const rhs) :
	rva<IMAGE_THUNK_DATA32>(rhs)
{ }

rva<const char*> image_thunk_data::name()
{
	if ((*this)->u1.Ordinal & IMAGE_ORDINAL_FLAG32)
		return rva<const char*>(IMAGE_ORDINAL32((*this)->u1.Ordinal), 0);

	auto const import_by_name = rva<IMAGE_IMPORT_BY_NAME>(base, (*this)->u1.AddressOfData);

	return rva<const char*>(&import_by_name->Name, 0);
}

image_import::image_import(void* const base, unsigned long const offset) :
	rva<IMAGE_IMPORT_DESCRIPTOR>(base, offset)
{ }

image_import::image_import(rva<IMAGE_IMPORT_DESCRIPTOR> const rhs):
	rva<IMAGE_IMPORT_DESCRIPTOR>(rhs)
{ }

rva<IMAGE_THUNK_DATA32> image_import::first_thunk()
{
	return rva<IMAGE_THUNK_DATA32>(base, (*this)->OriginalFirstThunk);
}