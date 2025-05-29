#ifndef ZEROBANK_H
#define ZEROBANK_H

#include "../common/singleareaview.h"

#include "zerolocation.h"

class ZeroBank final : public SingleAreaView {
public:
  ZeroBank(const MemoryArea& area);
  DISABLE_COPY_AND_MOVE(ZeroBank)

  ILocation8& getLocation8(const address_type address) override;

private:
  ZeroLocation loc_;
};

#endif // ZEROBANK_H
