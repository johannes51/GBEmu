#ifndef MIRRORBANK_H
#define MIRRORBANK_H

#include "../common/singleareaview.h"

#include "../mem_defines.h"

class MirrorBank : public SingleAreaView {
public:
  MirrorBank(const MemoryArea& mirrorArea, const MemoryArea& originalArea, IMemoryView& mirrored);
  DISABLE_COPY_AND_MOVE(MirrorBank)

  ILocation8& getLocation8(const address_type address) override;

private:
  const int offset_;
  IMemoryView& mirrored_;
};

#endif // MIRRORBANK_H
