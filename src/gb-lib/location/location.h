#ifndef LOCATION_H
#define LOCATION_H

#include <span>

#include "defines.h"
#include "mem/mem_defines.h"

class Location {
public:
  virtual ~Location() = default;
  DISABLE_COPY_AND_MOVE(Location)

  enum class Type { Single, Both, None };

  bool isWord() const;
  void fuse(const Location& other);

  template <typename T> const T& get() const;

  virtual const uint8_t& getByte() const = 0;
  virtual const uint16_t& getWord() const = 0;

  virtual Location& operator=(const uint8_t& rhs) = 0;
  virtual Location& operator=(const uint16_t& rhs) = 0;

protected:
  explicit Location(Type type)
      : type_(type)
  {
  }

private:
  Type type_;
};

using LocationUP = std::unique_ptr<Location>;

#endif // LOCATION_H
