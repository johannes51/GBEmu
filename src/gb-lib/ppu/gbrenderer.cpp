#include "gbrenderer.h"

GbRenderer::GbRenderer(IBackgroundSP bg, IWindowSP win, IObjectsSP obj)
    : bg_(std::move(bg))
    , win_(std::move(win))
    , obj_(std::move(obj))
{
}

void GbRenderer::render(GbPixelBuffer& buffer, const uint8_t currentLine)
{
  bg_->draw(buffer, currentLine);
  win_->draw(buffer, currentLine);
  obj_->draw(buffer, currentLine);
}
