#ifndef MEMORYTOOLS_H
#define MEMORYTOOLS_H

#include "imemorymanager.h"

namespace mem_tools {
address_type translateAdressSafe(const address_type inputAdress, MemoryArea area);
address_type translateAdressSafe(const address_type inputAdress,
                                 address_type startAdress, const address_type size);
address_type translateAdressSafe(const address_type inputAdress, MemoryArea mirror,
                                 int offset);
bool isSafe(const address_type &address, const MemoryArea &area);
} // namespace mem_tools

#endif // MEMORYTOOLS_H
