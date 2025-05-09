#ifndef IOBJECTS_H
#define IOBJECTS_H

#include <memory>

#include "ilayer.h"

class IObjects : public ILayer {
public:
  ~IObjects() override = default;
  DEFAULT_COPY_AND_MOVE(IObjects)
protected:
  IObjects() = default;
};

using IObjectsSP = std::shared_ptr<IObjects>;

#endif // IOBJECTS_H
