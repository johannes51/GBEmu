#ifndef MEMORYTOOLS_H
#define MEMORYTOOLS_H

#include <vector>

#include "../mem_defines.h"

namespace mem_tools {
address_type translateAddressSafe(const address_type& inputAddress, const MemoryArea& area);
address_type translateAddressSafe(
    const address_type& inputAddress, const address_type& startAddress, const address_type& size);
address_type translateAddressSafe(const address_type& inputAddress, const MemoryArea& mirror, const int offset);
void assertSafe(const address_type& address, const MemoryArea& area);
void assertSafe(const address_type& inputAddress, const address_type& startAddress, const address_type& size);
bool isSafe(const address_type& address, const MemoryArea& area);
bool isSafe(const address_type& inputAddress, const address_type& startAddress, const address_type& size);
bool isDisjunct(const MemoryArea& area1, const MemoryArea& area2);
bool isDisjunct(const MemoryArea& area, const std::vector<MemoryArea>& oldAreas);
} // namespace mem_tools

#endif // MEMORYTOOLS_H
