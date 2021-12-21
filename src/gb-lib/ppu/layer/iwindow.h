#ifndef IWINDOW_H
#define IWINDOW_H

#include <memory>

#include "ilayer.h"

class IWindow : public ILayer {
protected:
  IWindow() = default;
};

using IWindowSP = std::shared_ptr<IWindow>;

#endif // IWINDOW_H
