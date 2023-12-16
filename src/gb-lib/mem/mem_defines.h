#ifndef MEM_DEFINES_H
#define MEM_DEFINES_H

#include <memory>

using address_type = uint16_t;

class IMemoryView;
using IMemoryViewSP = std::shared_ptr<IMemoryView>;

class IMemoryManager;
using IMemoryManagerSP = std::shared_ptr<IMemoryManager>;

#endif // MEM_DEFINES_H
