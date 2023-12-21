#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "cpu/cpu.h"
#include "cpu/cpuregisters.h"
#include "gb_factories/apufactory.h"
#include "gb_factories/cartloader.h"
#include "gb_factories/instructionsetbuilder.h"
#include "gb_factories/memoryfactory.h"
#include "gb_factories/ppufactory.h"
#include "gb_factories/registerfactory.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui_(std::make_unique<Ui::MainWindow>())
  , sm_()
  , timer_(this)
  , buffer_(nullptr)
  , img_(160, 144, QImage::Format_Indexed8) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
{
  ui_->setupUi(this);

  gb::MemoryFactory m(std::make_unique<gb::CartLoader>("cpu_instrs.gb", "cpu_instrs.sav"));
  auto ml = m.constructMemoryLayout();
  std::vector<PeripheralSP> ps {};
  ApuFactory c { ml };
  ps.emplace_back(c.constructApu());
  PpuFactory p { ml };
  ps.emplace_back(p.constructPpu());
  buffer_ = &std::dynamic_pointer_cast<Ppu>(ps.back())->getBuffer();
  sm_ = std::make_unique<SystemManager>(ml, std::make_unique<Cpu>(std::make_unique<CpuRegisters>(), ml, InstructionSetBuilder::construct()), ps);

  timer_.start(static_cast<int>(1000./60.)); // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  connect(&timer_, &QTimer::timeout, this, &MainWindow::drawGbFrame);
}

MainWindow::~MainWindow() = default;

void MainWindow::drawGbFrame()
{
  constexpr auto CYCLES_PER_FRAME = 1000000/60;
  for (auto i = 0; i < CYCLES_PER_FRAME; ++i) {
    sm_->clock();
  }

  for (int y = 0; y < img_.height(); y++) {
    QRgb *line = (QRgb *) img_.scanLine(y); // NOLINT(cppcoreguidelines-pro-type-cstyle-cast,google-readability-casting)
    for (int x = 0; x < img_.width(); x++) {
        // line[x] has an individual pixel
        line[x] = buffer_->at(x).at(y); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    }
  }
}

