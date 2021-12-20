#include "gbrenderer.h"

GbRenderer::GbRenderer(IBackgroundSP bg, IWindowSP win, IObjectsSP obj)
    : bg_(std::move(bg))
    , win_(std::move(win))
    , obj_(std::move(obj))
{
}

void GbRenderer::render(IPixelBuffer& buffer) { (void)buffer; }
