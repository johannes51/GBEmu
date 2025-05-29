#ifndef SINGLEREGISTERBANK_H
#define SINGLEREGISTERBANK_H

#include "../imemoryview.h"

#include "../rest/variablelocation.h"

class SingleRegisterBank final : public IMemoryView {
public:
  SingleRegisterBank(const address_type& start, const uint8_t& initial = 0x00);
  DISABLE_COPY_AND_MOVE(SingleRegisterBank)

  ILocation8& getLocation8(const address_type address) override;

private:
  address_type start_;
  VariableLocation8 loc_;
};

#endif // SINGLEREGISTERBANK_H
