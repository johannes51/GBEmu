#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "gb_factories/gbfactory.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui_(std::make_unique<Ui::MainWindow>())
    , timer_(this)
    , img_(160, 144, QImage::Format_Indexed8) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
{
  ui_->setupUi(this);

  GbFactory f { "cpu_instrs.gb", "cpu_instrs.sav" };
  sm_ = f.constructSystem();
  buffer_ = sm_->getBuffer(); // NOLINT(cppcoreguidelines-prefer-member-initializer)

  timer_.start(
      static_cast<int>(1000. / 60.)); // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  connect(&timer_, &QTimer::timeout, this, &MainWindow::drawGbFrame);
}

MainWindow::~MainWindow() = default;

void MainWindow::drawGbFrame()
{
  constexpr auto CYCLES_PER_FRAME = 1000000 / 60;
  for (auto i = 0; i < CYCLES_PER_FRAME; ++i) {
    sm_->clock();
  }

  for (int y = 0; y < img_.height(); y++) {
    QRgb* line = (QRgb*)img_.scanLine(y); // NOLINT(cppcoreguidelines-pro-type-cstyle-cast,google-readability-casting)
    for (int x = 0; x < img_.width(); x++) {
      // line[x] has an individual pixel
      line[x] = buffer_->at(x).at(y); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    }
  }
}
