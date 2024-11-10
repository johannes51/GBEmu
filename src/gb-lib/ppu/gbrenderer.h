#ifndef GBRENDERER_H
#define GBRENDERER_H

#include "irenderer.h"
#include "layer/ibackground.h"
#include "layer/iobjects.h"
#include "layer/iwindow.h"

class GbRenderer : public IRenderer {
public:
  explicit GbRenderer(IBackgroundSP bg, IWindowSP win, IObjectsSP obj);

  void render(GbPixelBuffer& buffer) override;

private:
  IBackgroundSP bg_;
  IWindowSP win_;
  IObjectsSP obj_;
};

#endif // GBRENDERER_H
