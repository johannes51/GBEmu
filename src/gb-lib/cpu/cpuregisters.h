#ifndef REGISTERSIMPL_H
#define REGISTERSIMPL_H

#include <array>
#include <unordered_map>

#include "registersinterface.h"

class CpuRegisters final : public RegistersInterface {
public:
  CpuRegisters();
  ~CpuRegisters();
  DISABLE_COPY_AND_MOVE(CpuRegisters)

  Register8UP get(ByteRegister registerName) override;
  Register16UP get(WordRegister registerName) override;

  FlagsView& getFlags() override;
  const FlagsView& getFlags() const override;

private:
  static constexpr uint8_t INITIAL_A = 0x01;
  static constexpr uint8_t INITIAL_F = 0xB0;
  static constexpr uint8_t INITIAL_B = 0x00;
  static constexpr uint8_t INITIAL_C = 0x13;
  static constexpr uint8_t INITIAL_D = 0x00;
  static constexpr uint8_t INITIAL_E = 0xD8;
  static constexpr uint8_t INITIAL_H = 0x01;
  static constexpr uint8_t INITIAL_L = 0x4D;
  static constexpr uint8_t INITIAL_SPu = 0xFF;
  static constexpr uint8_t INITIAL_SPl = 0xFF;
  static constexpr uint8_t INITIAL_PCu = 0x01;
  static constexpr uint8_t INITIAL_PCl = 0x00;

  static const std::unordered_map<ByteRegister, std::pair<WordRegister, bool>> Mappings;

  std::array<uint16_t, static_cast<size_t>(WordRegister::NumRegs)> registers_;
  FlagsViewUP flags_;
};

#endif // REGISTERSIMPL_H
