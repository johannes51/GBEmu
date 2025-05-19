#include "joypad.h"

#include "gbinterrupthandler.h"
#include "util/helpers.h"

Joypad::Joypad(IRegisterAdapter& controllerRegister, IRegisterAdapter& rIf)
    : controllerRegister_(controllerRegister)
    , buttonState_({ { Button::Up, false }, { Button::Down, false }, { Button::Left, false }, { Button::Right, false },
          { Button::A, false }, { Button::B, false }, { Button::Start, false }, { Button::Select, false } })
    , if_(rIf)
{
}

void Joypad::clock()
{
  auto ctrReg = controllerRegister_.getByte();
  if (!hlp::checkBit(ctrReg, SelectAction)) {
    affectInputBit(ctrReg, Button::A, RightOrA);
    affectInputBit(ctrReg, Button::B, LeftOrB);
    affectInputBit(ctrReg, Button::Select, UpOrSelect);
    affectInputBit(ctrReg, Button::Start, DownOrStart);
  } else if (!hlp::checkBit(ctrReg, SelectDirection)) {
    affectInputBit(ctrReg, Button::Right, RightOrA);
    affectInputBit(ctrReg, Button::Left, LeftOrB);
    affectInputBit(ctrReg, Button::Up, UpOrSelect);
    affectInputBit(ctrReg, Button::Down, DownOrStart);
  } else {
    hlp::setBit(ctrReg, RightOrA);
    hlp::setBit(ctrReg, LeftOrB);
    hlp::setBit(ctrReg, UpOrSelect);
    hlp::setBit(ctrReg, DownOrStart);
  }
  controllerRegister_.setByte(ctrReg | ControllerRegisterSetBits);
}

void Joypad::press(Button button) { buttonState_[button] = true; }

void Joypad::release(Button button) { buttonState_[button] = false; }

void Joypad::affectInputBit(uint8_t& controlRegister, const Button& button, const uint8_t& bit)
{
  if (buttonState_[button]) {
    if (hlp::checkBit(controlRegister, bit)) {
      if_.setBit(JoypadInterruptBit, true);
    }
    hlp::clearBit(controlRegister, bit);
  } else {
    hlp::setBit(controlRegister, bit);
  }
}
