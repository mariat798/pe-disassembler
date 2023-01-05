/// const.hpp

#pragma once

#define DUMMYUNIONNAME

#define IMAGE_NUMBEROF_DIRECTORY_ENTRIES    16

#define IMAGE_DIRECTORY_ENTRY_EXPORT          0   // Export Directory
#define IMAGE_DIRECTORY_ENTRY_IMPORT          1   // Import Directory
#define IMAGE_DIRECTORY_ENTRY_RESOURCE        2   // Resource Directory
#define IMAGE_DIRECTORY_ENTRY_EXCEPTION       3   // Exception Directory
#define IMAGE_DIRECTORY_ENTRY_SECURITY        4   // Security Directory
#define IMAGE_DIRECTORY_ENTRY_BASERELOC       5   // Base Relocation Table
#define IMAGE_DIRECTORY_ENTRY_DEBUG           6   // Debug Directory
//      IMAGE_DIRECTORY_ENTRY_COPYRIGHT       7   // (X86 usage)
#define IMAGE_DIRECTORY_ENTRY_ARCHITECTURE    7   // Architecture Specific Data
#define IMAGE_DIRECTORY_ENTRY_GLOBALPTR       8   // RVA of GP
#define IMAGE_DIRECTORY_ENTRY_TLS             9   // TLS Directory
#define IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG    10   // Load Configuration Directory
#define IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT   11   // Bound Import Directory in headers
#define IMAGE_DIRECTORY_ENTRY_IAT            12   // Import Address Table
#define IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT   13   // Delay Load Import Descriptors
#define IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR 14   // COM Runtime descriptor

#define IMAGE_ORDINAL_FLAG32 0x80000000
#define IMAGE_ORDINAL32(Ordinal) (Ordinal & 0xffff)

#define IMAGE_SIZEOF_SHORT_NAME              8

constexpr auto DOS_SIGNATURE_LENGTH = 2;
constexpr unsigned char DOS_SIGNATURE[DOS_SIGNATURE_LENGTH] = { 'M', 'Z' };

constexpr auto NT_SIGNATURE_LENGTH = 4;
constexpr unsigned char NT_SIGNATURE[NT_SIGNATURE_LENGTH] = { 'P', 'E', 0, 0};
