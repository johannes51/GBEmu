#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTimer>

#include "defines.h"
#include "ppu/irenderer.h"
#include "sys/systemmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget* parent = nullptr);
  DISABLE_COPY_AND_MOVE(MainWindow)
  ~MainWindow();

public slots:
  void drawGbFrame();

private:
  std::unique_ptr<Ui::MainWindow> ui_;

  SystemManagerUP sm_ = nullptr;

  QTimer timer_;

  const IPixelBuffer* buffer_ = nullptr;

  QImage img_;
};

#endif // MAINWINDOW_H
