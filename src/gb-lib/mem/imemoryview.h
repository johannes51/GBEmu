#ifndef IMEMORYVIEW_H
#define IMEMORYVIEW_H

#include <memory>

#include "defines.h"
#include "ilocation16.h"
#include "ilocation8.h"
#include "mem_defines.h"

class IMemoryView {
public:
  virtual ~IMemoryView() = default;
  DISABLE_COPY_AND_MOVE(IMemoryView)

  virtual ILocation8& getLocation8(const address_type address) = 0;

protected:
  IMemoryView() = default;
};

using IMemoryViewUP = std::unique_ptr<IMemoryView>;

#endif // IMEMORYVIEW_H
