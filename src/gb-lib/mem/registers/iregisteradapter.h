#ifndef IREGISTERADAPTER_H
#define IREGISTERADAPTER_H

#include <memory>

class IRegisterAdapter {
public:
  virtual ~IRegisterAdapter() = default;

protected:
  IRegisterAdapter() = default;
};

using IRegisterAdapterSP = std::shared_ptr<IRegisterAdapter>;

#endif // IREGISTERADAPTER_H
