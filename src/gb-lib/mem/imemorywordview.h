#ifndef IMEMORYWORDVIEW_H
#define IMEMORYWORDVIEW_H

#include "imemoryview.h"

#include <memory>

class IMemoryWordView : public IMemoryView {
public:
  IMemoryWordView() = default;
  virtual ~IMemoryWordView() = default;
  DISABLE_COPY_AND_MOVE(IMemoryWordView)

  virtual ILocation16& getLocation16(const address_type address) = 0;
};

using IMemoryWordViewUP = std::unique_ptr<IMemoryWordView>;

#endif // IMEMORYWORDVIEW_H
