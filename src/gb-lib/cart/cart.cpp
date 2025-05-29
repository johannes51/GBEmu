#include "cart.h"

Cart::Cart(IMemoryViewUP banks)
    : banks_(std::move(banks))
{
}

void Cart::clock() { }

auto Cart::getBanks() -> IMemoryView& { return *banks_; }
