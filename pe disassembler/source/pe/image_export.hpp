/// image_export_table.hpp

#pragma once

class image_export : public rva<IMAGE_EXPORT_DIRECTORY>
{
public:

	image_export(void* const base, unsigned long const offset);
};
