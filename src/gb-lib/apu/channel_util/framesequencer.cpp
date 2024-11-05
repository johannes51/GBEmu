#include "framesequencer.h"

#include "util/helpers.h"

FrameSequencer::FrameSequencer()
    : oldDivApu_(0U)
{
}

auto FrameSequencer::get() const -> FrameSequence
{
  return static_cast<FrameSequence>(hlp::getBits(oldDivApu_, 0U, 3U));
}

auto FrameSequencer::isTick(const uint8_t divApu) -> bool
{
  if (divApu != oldDivApu_) {
    oldDivApu_ = divApu;
    return true;
  } else {
    return false;
  }
}
