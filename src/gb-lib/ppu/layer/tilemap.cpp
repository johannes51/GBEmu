#include "tilemap.h"

#include "tiledata.h"

TileMap::TileMap(IRegisterAdapterSP lcdc, IMemoryViewSP mem)
    : lcdc_(std::move(lcdc))
    , mem_(std::move(mem))
    , tiles_(std::make_unique<TileData>(lcdc_, mem_))
{
}

TileMap::~TileMap() = default;
