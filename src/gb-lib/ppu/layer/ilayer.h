#ifndef ILAYER_H
#define ILAYER_H

#include "../pixelbuffer.h"
#include "defines.h"

class ILayer {
public:
  virtual ~ILayer() = default;
  DEFAULT_COPY_AND_MOVE(ILayer)

  virtual void draw(GbPixelBuffer& buffer, const uint8_t currentLine) = 0;

protected:
  ILayer() = default;
};

#endif // ILAYER_H
