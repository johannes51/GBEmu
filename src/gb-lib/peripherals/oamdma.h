#ifndef OAMDMA_H
#define OAMDMA_H

#include "tickable.h"

#include <limits>

#include "io/iobank.h"
#include "io/ioregister.h"
#include "mem/imemoryview.h"

class OamDma : public Tickable {
public:
  explicit OamDma(IoBank& io, IMemoryView& mem);
  DISABLE_COPY_AND_MOVE(OamDma)
  ~OamDma() override = default;

  void clock() override;

private:
  void startTransfer();
  void clockTransfer();
  void endTransfer();

  static constexpr uint16_t NoTransfer = std::numeric_limits<uint16_t>::max();
  static constexpr uint16_t OamStart = 0xFE00U;
  static constexpr uint16_t DmaTransferSize = 160U;

  IoRegister dmaRegister_;
  IMemoryView& mem_;
  uint16_t startAddress_ = NoTransfer;
  size_t bytesTransferred_ = 0U;
};

#endif // OAMDMA_H
