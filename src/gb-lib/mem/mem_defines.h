#ifndef MEM_DEFINES_H
#define MEM_DEFINES_H

#include <memory>


using address_type = uint16_t;

class MemoryView;
using MemoryViewSP = std::shared_ptr<MemoryView>;

#endif // MEM_DEFINES_H
