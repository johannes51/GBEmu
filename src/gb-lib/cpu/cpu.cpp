#include "cpu.h"

#include "cpu_defines.h"
#include "location/location.h"
#include "mem/imemoryview.h"
#include "operation.h"
#include "registersinterface.h"
#include "util/helpers.h"
#include "util/ops.h"

Cpu::Cpu(RegistersInterfaceUP &&registers, IMemoryViewSP mem)
    : mem_(std::move(mem)), registers_(std::move(registers)),
      nextOperation_(nullptr) {}

Cpu::~Cpu() = default;

void Cpu::clock() {
  if (!nextOperation_) {
    nextOperation_ = std::make_unique<Operation>();
    while (nextOperation_->nextOpcode(
        **mem_->getByte(hlp::indirect(registers_->pc())))) {
      ops::increment(registers_->pc());
    }
  }
  nextOperation_->clock();
  if (nextOperation_->isDone()) {
  }
}
