#ifndef GBRENDERER_H
#define GBRENDERER_H

#include "irenderer.h"
#include "layer/ibackground.h"
#include "layer/iobjects.h"
#include "layer/iwindow.h"

class GbRenderer : public IRenderer {
public:
  explicit GbRenderer(IBackgroundUP bg, IWindowUP win, IObjectsUP obj);

  void render(GbPixelBuffer& buffer, const uint8_t currentLine) override;

private:
  IBackgroundUP bg_;
  IWindowUP win_;
  IObjectsUP obj_;
};

#endif // GBRENDERER_H
