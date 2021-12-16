#ifndef REGISTERFACTORY_H
#define REGISTERFACTORY_H

#include <unordered_map>

#include "mem/imemoryview.h"
#include "mem/registers/iregisteradapter.h"

template <typename E> class RegisterFactory {
public:
  RegisterFactory();

  IRegisterAdapterSP get(E name);

protected:
  void add(E name, IRegisterAdapterSP reg);

private:
  std::unordered_map<E, IRegisterAdapterSP> registers_;
};

template <typename E>
RegisterFactory<E>::RegisterFactory()
    : registers_()
{
}

template <typename E> IRegisterAdapterSP RegisterFactory<E>::get(E name) { return registers_.at(name); }

template <typename E> void RegisterFactory<E>::add(E name, IRegisterAdapterSP reg) { registers_[name] = reg; }

#endif // REGISTERFACTORY_H
