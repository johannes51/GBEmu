#ifndef APU_H
#define APU_H

#include "defines.h"
#include "iapu.h"
#include "imixer.h"

class Apu : public IApu {
public:
  Apu(IMixerUP&& mixer);
  DISABLE_COPY_AND_MOVE(Apu)
  ~Apu() override = default;

  void clock() override;

private:
  IMixerUP mixer_;
  // FIXME: apu braucht kanäle
};

#endif // APU_H
