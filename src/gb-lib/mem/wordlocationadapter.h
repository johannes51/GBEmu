#ifndef WORDLOCATIONADAPTER_H
#define WORDLOCATIONADAPTER_H

#include <memory>

class WordLocationAdapter {
public:
  virtual ~WordLocationAdapter() = default;

  virtual const uint16_t& get() const = 0;
  virtual void set(const uint16_t&) = 0;
};

using WordLocationAdapterUP = std::unique_ptr<WordLocationAdapter>;

#endif // BYTELOCATIONADAPTER_H
