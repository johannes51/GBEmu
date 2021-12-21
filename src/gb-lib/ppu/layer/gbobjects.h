#ifndef GBOBJECTS_H
#define GBOBJECTS_H

#include "iobjects.h"

class GbObjects : public IObjects {
public:
  GbObjects() = default;

  void draw(IPixelBuffer& buffer) override;
};

#endif // GBOBJECTS_H
