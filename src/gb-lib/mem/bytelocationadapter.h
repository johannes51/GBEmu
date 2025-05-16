#ifndef BYTELOCATIONADAPTER_H
#define BYTELOCATIONADAPTER_H

#include <memory>

class ByteLocationAdapter {
public:
  virtual ~ByteLocationAdapter() = default;

  virtual const uint8_t& get() const = 0;
  virtual void set(const uint8_t& value) = 0;
};

using ByteLocationAdapterUP = std::unique_ptr<ByteLocationAdapter>;

#endif // BYTELOCATIONADAPTER_H
