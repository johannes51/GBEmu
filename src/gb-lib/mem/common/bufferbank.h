#ifndef BUFFERBANK_H
#define BUFFERBANK_H

#include "../common/singleareaview.h"

#include <span>

#include "../mem_defines.h"

class BufferBank : public SingleAreaView {
public:
  DISABLE_COPY_AND_MOVE(BufferBank)
  ~BufferBank() override = default;

protected:
  BufferBank(const MemoryArea& area, std::span<uint8_t, std::dynamic_extent> buffer)
      : SingleAreaView(area)
      , buffer_(std::move(buffer))
  {
  }

  std::span<uint8_t, std::dynamic_extent> buffer_;
};

#endif // BUFFERBANK_H
