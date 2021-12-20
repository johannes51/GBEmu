#ifndef IBACKGROUND_H
#define IBACKGROUND_H

#include <memory>

#include "ilayer.h"

class IBackground : public ILayer {
protected:
  IBackground() = default;
};

using IBackgroundSP = std::shared_ptr<IBackground>;

#endif // IBACKGROUND_H
