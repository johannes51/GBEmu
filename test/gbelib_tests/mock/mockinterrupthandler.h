#ifndef MOCKINTERRUPTHANDLER_H
#define MOCKINTERRUPTHANDLER_H

#include "cpu/registers/registersinterface.h"
#include "peripherals/interrupthandler.h"

class MockInterruptHandler : public InterruptHandler {
public:
  void execute(RegistersInterface& registers, IMemoryWordView& memory) override
  {
    (void)memory;
    registers.get(WordRegister::PC) = pc_;
    wasExecuted_ = true;
  }
  bool isInterrupt() const override { return isInterrupt_; }

  void setInterrupt(bool value) { isInterrupt_ = value; }
  void setPc(address_type value) { pc_ = value; }

  bool wasExecuted() const { return wasExecuted_; }

  static InterruptHandlerUP make(bool isInterrupt = false, address_type pc = 0x0U)
  {
    return std::unique_ptr<MockInterruptHandler>(new MockInterruptHandler { isInterrupt, pc });
  }
  static InterruptHandlerUP make(MockInterruptHandler*& handler, bool isInterrupt = false, address_type pc = 0x0U)
  {
    handler = new MockInterruptHandler { isInterrupt, pc };
    return std::unique_ptr<MockInterruptHandler>(handler);
  }

private:
  explicit MockInterruptHandler(bool isInterrupt, address_type pc)
      : isInterrupt_(isInterrupt)
      , pc_(pc)
  {
  }

  bool isInterrupt_;
  address_type pc_;
  bool wasExecuted_ = false;
};

#endif // MOCKINTERRUPTHANDLER_H
