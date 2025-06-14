#ifndef IBACKGROUND_H
#define IBACKGROUND_H

#include <memory>

#include "ilayer.h"

class IBackground : public ILayer {
public:
  ~IBackground() override = default;

protected:
  IBackground() = default;
};

using IBackgroundUP = std::unique_ptr<IBackground>;

#endif // IBACKGROUND_H
