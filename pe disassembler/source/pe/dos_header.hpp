/// dos_header.hpp

#pragma once

class dos_header: public header<_IMAGE_DOS_HEADER>
{
public:

	dos_header(void* base);
};
