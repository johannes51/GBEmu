#ifndef IRENDERER_H
#define IRENDERER_H

#include <memory>

class IPixelBuffer;

class IRenderer {
public:
  virtual ~IRenderer() = default;

  virtual void render(IPixelBuffer& buffer) = 0;

protected:
  IRenderer() = default;
};

using IRendererSP = std::shared_ptr<IRenderer>;

#endif // IRENDERER_H
