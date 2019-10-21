#ifndef MEMORYTOOLS_H
#define MEMORYTOOLS_H

#include "imemorymanager.h"

namespace mem_tools {
address_type translateAdressSafe(address_type inputAdress, MemoryArea area);
address_type translateAdressSafe(address_type inputAdress,
                                 address_type startAdress, address_type size);
address_type translateAdressSafe(address_type inputAdress, MemoryArea mirror,
                                 int offset);
} // namespace mem_tools

#endif // MEMORYTOOLS_H
