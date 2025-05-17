#include "mocktilemap.h"

#include "mockregisteradapter.h"
#include "testbank.h"

IRegisterAdapterUP MockTileMap::fakeReg = MockRegisterAdapter::make();
