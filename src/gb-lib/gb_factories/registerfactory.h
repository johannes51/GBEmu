#ifndef REGISTERFACTORY_H
#define REGISTERFACTORY_H

#include <unordered_map>

#include "mem/imemoryview.h"
#include "mem/registers/memoryregisteradapter.h"

template <typename E>
std::unordered_map<E, IRegisterAdapterSP> constructRegisterMap(
    const IMemoryViewSP& ioBank, const std::unordered_map<E, address_type>& map);

template <typename E> class RegisterFactory {
public:
  IRegisterAdapterSP get(E name);

protected:
  explicit RegisterFactory(const IMemoryViewSP& ioBank, const std::unordered_map<E, address_type>& map);

private:
  std::unordered_map<E, IRegisterAdapterSP> registers_;
};

template <typename E> IRegisterAdapterSP RegisterFactory<E>::get(E name) { return registers_.at(name); }

template <typename E>
RegisterFactory<E>::RegisterFactory(const IMemoryViewSP& ioBank, const std::unordered_map<E, address_type>& map)
    : registers_(constructRegisterMap<E>(ioBank, map))
{
}

template <typename E>
std::unordered_map<E, IRegisterAdapterSP> constructRegisterMap(
    const IMemoryViewSP& ioBank, const std::unordered_map<E, address_type>& map)
{
  std::unordered_map<E, IRegisterAdapterSP> result;
  for (const auto& regAddPair : map) {
    result.emplace(regAddPair.first, std::make_shared<MemoryRegisterAdapter>(ioBank, regAddPair.second));
  }
  return result;
}

#endif // REGISTERFACTORY_H
