#include "joypad.h"

#include "util/helpers.h"

Joypad::Joypad(IMemoryViewSP controllerRegister)
    : controllerRegister_(std::move(controllerRegister))
    , buttonState_({ { Button::Up, false }, { Button::Down, false }, { Button::Left, false }, { Button::Right, false },
          { Button::A, false }, { Button::B, false }, { Button::Start, false }, { Button::Select, false } })
{
}

void Joypad::clock()
{
  auto ctrReg = controllerRegister_->getLocation(ControllerRegisterAddress)->getByte();
  if (hlp::checkBit(ctrReg, SelectAction)) {
    affectInputBit(ctrReg, Button::A, RightOrA);
    affectInputBit(ctrReg, Button::B, LeftOrB);
    affectInputBit(ctrReg, Button::Select, UpOrSelect);
    affectInputBit(ctrReg, Button::Start, DownOrStart);
  }
  if (hlp::checkBit(ctrReg, SelectDirection)) {
    affectInputBit(ctrReg, Button::Right, RightOrA);
    affectInputBit(ctrReg, Button::Left, LeftOrB);
    affectInputBit(ctrReg, Button::Up, UpOrSelect);
    affectInputBit(ctrReg, Button::Down, DownOrStart);
  }
  *controllerRegister_->getLocation(ControllerRegisterAddress) = ctrReg;
}

void Joypad::press(Button button) { buttonState_[button] = true; }

void Joypad::release(Button button) { buttonState_[button] = false; }

void Joypad::affectInputBit(uint8_t& controlRegister, const Button& button, const uint8_t& bit)
{
  if (buttonState_[button]) {
    hlp::clearBit(controlRegister, bit);
  }
}
