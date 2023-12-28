#ifndef OBJECT_H
#define OBJECT_H

#include <cstdint>
#include <span>

class Object {
public:
  Object(std::span<uint8_t, 4> buffer);

  uint8_t getY() const;
  uint8_t getX() const;
  uint8_t getTileIndex() const;

  bool hasLowPriority() const;
  bool isFlippedX() const;
  bool isFlippedY() const;
  bool isSecondPalette() const;

private:
  std::span<uint8_t, 4> buffer_;
};

#endif // OBJECT_H
