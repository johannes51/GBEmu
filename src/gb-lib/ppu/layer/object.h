#ifndef OBJECT_H
#define OBJECT_H

#include <cstdint>

class Object {
public:
  Object();
  Object(uint8_t (*buffer)[4]);

  uint8_t getY() const;
  uint8_t getX() const;
  uint8_t getTileIndex() const;

  bool hasLowPriority() const;
  bool isFlippedX() const;
  bool isFlippedY() const;
  bool isSecondPalette() const;

private:
  uint8_t (*buffer_)[4];
};

#endif // OBJECT_H
