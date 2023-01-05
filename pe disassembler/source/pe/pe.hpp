/// pe.hpp

#pragma once

#include "rva.hpp"
#include "header.hpp"
#include "section.hpp"
#include "dos_header.hpp"
#include "image_export.hpp"
#include "image_import.hpp"
#include "image_base_relocation.hpp"
#include "nt_header.hpp"

class pe
{
public: // todo make this private

	std::unique_ptr<unsigned char[]> data;

public:

	pe(void* const ptr, std::size_t const size);

	bool valid_pe();

	dos_header get_dos();
	nt_header get_nt();
};
