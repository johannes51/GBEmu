#ifndef ILAYER_H
#define ILAYER_H

#include "../pixelbuffer.h"

class ILayer {
public:
  virtual ~ILayer() = default;

  virtual void draw(GbPixelBuffer& buffer) = 0;

protected:
  ILayer() = default;
};

#endif // ILAYER_H
