#ifndef JOYPAD_H
#define JOYPAD_H

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

class Joypad {
public:
  explicit Joypad(IRegisterAdapterSP controllerRegister);

  void clock();

  void press(Button button);
  void release(Button button);

private:
  void affectInputBit(uint8_t& controlRegister, const Button& button, const uint8_t& bit);

  IRegisterAdapterSP controllerRegister_;
  std::unordered_map<Button, bool> buttonState_;
};

using JoypadUP = std::unique_ptr<Joypad>;

#endif // JOYPAD_H
