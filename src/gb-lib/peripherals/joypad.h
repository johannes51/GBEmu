#ifndef JOYPAD_H
#define JOYPAD_H

#include "tickable.h"

#include <memory>
#include <unordered_map>

#include "mem/registers/iregisteradapter.h"

enum class Button { Up, Down, Left, Right, A, B, Start, Select };

constexpr uint8_t RightOrA = 0x0;
constexpr uint8_t LeftOrB = 0x1;
constexpr uint8_t UpOrSelect = 0x2;
constexpr uint8_t DownOrStart = 0x3;
constexpr uint8_t SelectDirection = 0x4;
constexpr uint8_t SelectAction = 0x5;

class Joypad : public Tickable {
public:
  explicit Joypad(IRegisterAdapter& controllerRegister, IRegisterAdapter& rIf);

  void clock() override;

  void press(Button button);
  void release(Button button);

private:
  void affectInputBit(uint8_t& controlRegister, const Button& button, const uint8_t& bit);

  static constexpr uint8_t ControllerRegisterSetBits = 0b11000000U;

  IRegisterAdapter& controllerRegister_;
  std::unordered_map<Button, bool> buttonState_;
  IRegisterAdapter& if_;
};

using JoypadUP = std::unique_ptr<Joypad>;

#endif // JOYPAD_H
