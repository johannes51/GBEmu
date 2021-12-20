#include "ppu.h"

Ppu::Ppu(IRendererSP renderer)
    : renderer_(std::move(renderer))
{
}

void Ppu::clock() { }
