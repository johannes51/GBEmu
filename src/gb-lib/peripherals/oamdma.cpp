#include "oamdma.h"

#include "constants.h"

constexpr address_type DmaAddress = 0xFF46U;
constexpr uint8_t DmaInitial = 0xFFU;

OamDma::OamDma(IoBank& io, IMemoryView& mem)
    : dmaRegister_(DmaInitial)
    , mem_(mem)
{
  io.registerRegister(DmaAddress, &dmaRegister_);
}

void OamDma::clock()
{
  if (startAddress_ != NoTransfer) {
    clockTransfer();
  } else if (dmaRegister_.getByte() != 0U) {
    startTransfer();
  }
}

void OamDma::startTransfer()
{
  startAddress_ = (dmaRegister_.getByte() << BYTE_SHIFT);
  bytesTransferred_ = 0U;
}

void OamDma::clockTransfer()
{
  if (bytesTransferred_ < DmaTransferSize) {
    mem_.getLocation8(OamStart | bytesTransferred_) = mem_.getLocation8(startAddress_ | bytesTransferred_).get();
    ++bytesTransferred_;
  }
  if (bytesTransferred_ == DmaTransferSize) {
    endTransfer();
  }
}

void OamDma::endTransfer()
{
  dmaRegister_.setByte(0U);
  startAddress_ = NoTransfer;
}
