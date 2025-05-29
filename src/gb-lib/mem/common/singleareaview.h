#ifndef SINGLEAREAVIEW_H
#define SINGLEAREAVIEW_H

#include "../imemoryview.h"

#include "../mem_defines.h"

class SingleAreaView : public IMemoryView {
public:
  DISABLE_COPY_AND_MOVE(SingleAreaView)
  ~SingleAreaView() = default;

protected:
  explicit SingleAreaView(const MemoryArea& area);

  const MemoryArea area_;
};

#endif // SINGLEAREAVIEW_H
