#ifndef JOYPAD_H
#define JOYPAD_H

#include "peripheral.h"

#include <unordered_map>

#include "mem/registerbank.h"

enum class Button { Up, Down, Left, Right, A, B, Start, Select };

constexpr address_type ControllerRegisterAddress = 0xFF00;

constexpr uint8_t RightOrA = 0x0;
constexpr uint8_t LeftOrB = 0x1;
constexpr uint8_t UpOrSelect = 0x2;
constexpr uint8_t DownOrStart = 0x3;
constexpr uint8_t SelectDirection = 0x4;
constexpr uint8_t SelectAction = 0x5;

class Joypad : public Peripheral {
public:
  explicit Joypad(IMemoryViewSP controllerRegister);

  virtual void clock();

  void press(Button button);
  void release(Button button);

private:
  void affectInputBit(uint8_t& controlRegister, const Button& button, const uint8_t& bit);

  IMemoryViewSP controllerRegister_;
  std::unordered_map<Button, bool> buttonState_;
};

#endif // JOYPAD_H
