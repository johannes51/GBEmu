#ifndef ILAYER_H
#define ILAYER_H

#include <array>
#include <cstdint>

using IPixelBuffer = std::array<std::array<uint8_t, 144>, 160>;

class ILayer {
public:
  virtual ~ILayer() = default;

  virtual void draw(IPixelBuffer& buffer) = 0;

protected:
  ILayer() = default;
};

#endif // ILAYER_H
