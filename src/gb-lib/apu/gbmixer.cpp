#include "gbmixer.h"

GbMixer::GbMixer(std::array<IChannel*, 4>&& channels, IRegisterAdapterUP&& registers)
    : channels_(channels)
    , registers_(std::move(registers))
{
}
