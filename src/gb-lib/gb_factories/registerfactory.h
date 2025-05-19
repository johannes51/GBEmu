#ifndef REGISTERFACTORY_H
#define REGISTERFACTORY_H

#include <unordered_map>

#include "mem/registers/iobank.h"
#include "mem/registers/memoryregisteradapter.h"

template <typename E> class RegisterFactory {
public:
  using InputMap = std::unordered_map<E, std::pair<address_type, uint8_t>>;
  using OutputMap = std::unordered_map<E, IRegisterAdapterUP>;

  IRegisterAdapter& get(E name);
  OutputMap getAll();

protected:
  explicit RegisterFactory(IoBank& ioBank, const InputMap& map);

private:
  static OutputMap constructRegisterMap(IoBank& ioBank, const InputMap& map);

  OutputMap registers_;
};

template <typename E> IRegisterAdapter& RegisterFactory<E>::get(E name) { return *registers_.at(name); }

template <typename E> inline RegisterFactory<E>::OutputMap RegisterFactory<E>::getAll()
{
  return std::move(registers_);
}

template <typename E>
RegisterFactory<E>::RegisterFactory(IoBank& ioBank, const InputMap& map)
    : registers_(constructRegisterMap(ioBank, map))
{
}

template <typename E>
RegisterFactory<E>::OutputMap RegisterFactory<E>::constructRegisterMap(IoBank& ioBank, const InputMap& map)
{
  OutputMap result;
  for (const auto& regAddPair : map) {
    auto emplaceResult = result.emplace(
        regAddPair.first, std::make_unique<MemoryRegisterAdapter>(ioBank.getRegisterLocation(regAddPair.second.first)));
    (emplaceResult.first)->second->setByte(regAddPair.second.second);
  }
  return result;
}

#endif // REGISTERFACTORY_H
