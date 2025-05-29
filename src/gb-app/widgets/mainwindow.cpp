#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

#include "gb_factories/gbfactory.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui_(std::make_unique<Ui::MainWindow>())
    , timer_(this)
    , img_(160, 144, QImage::Format_Indexed8) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
{
  ui_->setupUi(this);

  const auto fn = QFileInfo { QFileDialog::getOpenFileName(
      nullptr, "", "/home/jo/Downloads/gb/gb-test-roms-master/", "ROMs (*.gb *.gbc)") };

  GbFactory f { fn.absoluteFilePath().toStdString(), (fn.absolutePath() + fn.baseName() + ".sav").toStdString() };
  sm_ = f.constructSystem();
  buffer_ = sm_->getPixBuffer(); // NOLINT(cppcoreguidelines-prefer-member-initializer)

  timer_.setSingleShot(true);
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
  // NOLINTBEGIN
  ui_->label->setPixmap(QPixmap::fromImage(QImage(reinterpret_cast<const uint8_t*>(buffer_->data()), buffer_->width(),
                                               buffer_->height(), QImage::Format_RGB32))
                            .scaled(ui_->label->width(), ui_->label->height(), Qt::KeepAspectRatio));
  // NOLINTEND

  timer_.start(
      static_cast<int>(1000. / 60.)); // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
}
