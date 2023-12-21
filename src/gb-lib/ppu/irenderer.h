#ifndef IRENDERER_H
#define IRENDERER_H

#include <array>
#include <memory>

using IPixelBuffer = std::array<std::array<uint8_t, 144>, 160>;

class IRenderer {
public:
  virtual ~IRenderer() = default;

  virtual void render(IPixelBuffer& buffer) = 0;

protected:
  IRenderer() = default;
};

using IRendererSP = std::shared_ptr<IRenderer>;

#endif // IRENDERER_H
