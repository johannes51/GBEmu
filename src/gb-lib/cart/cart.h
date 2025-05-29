#ifndef CART_H
#define CART_H

#include "peripherals/tickable.h"

#include "mem/imemoryview.h"

class Cart : public Tickable {
public:
  explicit Cart(IMemoryViewUP banks);

  void clock() override;

  IMemoryView& getBanks();

private:
  IMemoryViewUP banks_;
};

using CartUP = std::unique_ptr<Cart>;

#endif // CART_H
