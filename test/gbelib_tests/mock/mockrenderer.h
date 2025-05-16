#ifndef MOCKRENDERER_H
#define MOCKRENDERER_H

#include "ppu/irenderer.h"

class MockRenderer : public IRenderer {
public:
  void render(GbPixelBuffer& buffer, const uint8_t currentLine) override
  {
    (void)buffer;
    (void)currentLine;
  }
};

#endif // MOCKRENDERER_H
