#ifndef IOBANK_H
#define IOBANK_H

#include "mem/common/singleareaview.h"

#include <unordered_map>

#include "defines.h"
#include "iregisteradapter.h"

class IoBank : public SingleAreaView {
public:
  explicit IoBank();
  DISABLE_COPY_AND_MOVE(IoBank)
  ~IoBank() override = default;

  ILocation8& getLocation8(const address_type address) override;

  void registerRegister(const address_type add, ILocation8* reg);

protected:
  static constexpr MemoryArea Io = { 0xFF00U, 0xFF7FU };

  ILocation8* selectRegister(const address_type add);

private:
  std::unordered_map<address_type, ILocation8*> registeredRegisters_;
};

using IoBankUP = std::unique_ptr<IoBank>;

#endif // IOBANK_H
