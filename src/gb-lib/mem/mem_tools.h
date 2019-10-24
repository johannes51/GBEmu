#ifndef MEMORYTOOLS_H
#define MEMORYTOOLS_H

#include "imemorymanager.h"

namespace mem_tools {
address_type translateAdressSafe(const address_type inputAdress,
                                 MemoryArea area);
address_type translateAdressSafe(const address_type inputAdress,
                                 const address_type startAdress,
                                 const address_type size);
address_type translateAdressSafe(const address_type inputAdress,
                                 MemoryArea mirror, int offset);
void assertSafe(const address_type &address, const MemoryArea &area);
void assertSafe(const address_type &inputAdress,
                const address_type &startAdress, const address_type &size);
bool isSafe(const address_type &address, const MemoryArea &area);
bool isSafe(const address_type &inputAdress, const address_type &startAdress,
            const address_type &size);
bool isDisjunct(const MemoryArea &area1,
                const MemoryArea &area2);
bool isDisjunct(const MemoryArea &area,
                const std::vector<MemoryArea> &oldAreas);
} // namespace mem_tools

#endif // MEMORYTOOLS_H
