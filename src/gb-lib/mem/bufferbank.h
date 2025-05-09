#ifndef BUFFER_BANK_H
#define BUFFER_BANK_H

#include <span>

#include "singleareamanager.h"

class BufferBank : public SingleAreaManager {
public:
  friend class BufferLocation;

  virtual ~BufferBank() = default;
  DISABLE_COPY_AND_MOVE(BufferBank)

protected:
  explicit BufferBank(const MemoryArea& area, std::span<uint8_t, std::dynamic_extent> buffer);

private:
  uint8_t& getByteReference(address_type address);

  std::span<uint8_t, std::dynamic_extent> buffer_;
};

#endif // BUFFER_BANK_H
