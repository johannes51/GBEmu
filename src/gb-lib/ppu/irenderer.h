#ifndef IRENDERER_H
#define IRENDERER_H

#include <memory>

#include "pixelbuffer.h"

class IRenderer {
public:
  virtual ~IRenderer() = default;

  virtual void render(GbPixelBuffer& buffer, const uint8_t currentLine) = 0;

protected:
  IRenderer() = default;
};

using IRendererSP = std::shared_ptr<IRenderer>;

#endif // IRENDERER_H
