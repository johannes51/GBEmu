#ifndef FRAMESEQUENCER_H
#define FRAMESEQUENCER_H

#include <cstdint>

enum class FrameSequence : uint8_t {
  Phase0 = 0U,
  Phase2 = 2U,
  Phase4 = 4U,
  Phase6 = 6U,
  Phase7 = 7U,
};

class FrameSequencer {
public:
  FrameSequencer();

  bool isTick(const uint8_t divApu);

  FrameSequence get() const;

private:
  uint8_t oldDivApu_;
};

#endif // FRAMESEQUENCER_H
