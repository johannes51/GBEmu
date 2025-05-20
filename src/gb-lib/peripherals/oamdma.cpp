#include "oamdma.h"

#include "constants.h"

OamDma::OamDma(IRegisterAdapter& dmaRegister, IMemoryView& mem)
    : dmaRegister_(dmaRegister)
    , mem_(mem)
{
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
    mem_.getLocation8(OamStart | bytesTransferred_) = mem_.getLocation8(startAddress_ | bytesTransferred_);
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
