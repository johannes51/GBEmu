#ifndef OAMDMA_H
#define OAMDMA_H

#include "tickable.h"

#include <limits>

#include "mem/imemoryview.h"
#include "mem/registers/iregisteradapter.h"

class OamDma : public Tickable {
public:
  explicit OamDma(IRegisterAdapter& dmaRegister, IMemoryView& mem);

  void clock() override;

private:
  void startTransfer();
  void clockTransfer();
  void endTransfer();

  static constexpr uint16_t NoTransfer = std::numeric_limits<uint16_t>::max();
  static constexpr uint16_t OamStart = 0xFE00U;
  static constexpr uint16_t DmaTransferSize = 160U;

  IRegisterAdapter& dmaRegister_;
  IMemoryView& mem_;
  uint16_t startAddress_ = NoTransfer;
  size_t bytesTransferred_ = 0U;
};

#endif // OAMDMA_H
