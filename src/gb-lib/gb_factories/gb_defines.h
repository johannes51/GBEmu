#ifndef GB_DEFINES_H
#define GB_DEFINES_H

#include <memory>

namespace gb {

class CartLoader;
using RomLoaderUP = std::unique_ptr<CartLoader>;

} // namespace gb

#endif // GB_DEFINES_H
