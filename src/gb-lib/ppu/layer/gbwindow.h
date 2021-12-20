#ifndef GBWINDOW_H
#define GBWINDOW_H

#include "iwindow.h"

class GbWindow : public IWindow {
public:
  GbWindow() = default;

  void draw(IPixelBuffer& buffer) override;
};

#endif // GBWINDOW_H
