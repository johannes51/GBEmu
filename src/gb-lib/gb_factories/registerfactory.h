#ifndef REGISTERFACTORY_H
#define REGISTERFACTORY_H

#include <unordered_map>

#include "mem/registers/iobank.h"
#include "mem/registers/memoryregisteradapter.h"

template <typename E>
std::unordered_map<E, IRegisterAdapterUP> constructRegisterMap(
    const IMemoryView& ioBank, const std::unordered_map<E, address_type>& map);

template <typename E> class RegisterFactory {
public:
  IRegisterAdapter& get(E name);
  std::unordered_map<E, IRegisterAdapterUP> getAll();

protected:
  explicit RegisterFactory(IoBank& ioBank, const std::unordered_map<E, address_type>& map);

private:
  std::unordered_map<E, IRegisterAdapterUP> registers_;
};

template <typename E> IRegisterAdapter& RegisterFactory<E>::get(E name) { return *registers_.at(name); }

template <typename E> inline std::unordered_map<E, IRegisterAdapterUP> RegisterFactory<E>::getAll()
{
  return std::move(registers_);
}

template <typename E>
RegisterFactory<E>::RegisterFactory(IoBank& ioBank, const std::unordered_map<E, address_type>& map)
    : registers_(constructRegisterMap<E>(ioBank, map))
{
}

template <typename E>
std::unordered_map<E, IRegisterAdapterUP> constructRegisterMap(
    IoBank& ioBank, const std::unordered_map<E, address_type>& map)
{
  std::unordered_map<E, IRegisterAdapterUP> result;
  for (const auto& regAddPair : map) {
    result.emplace(
        regAddPair.first, std::make_unique<MemoryRegisterAdapter>(ioBank.getRegisterLocation(regAddPair.second)));
  }
  return result;
}

#endif // REGISTERFACTORY_H
