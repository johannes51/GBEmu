#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTimer>

#include "sys/systemmanager.h"
#include "ppu/ppu.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

public slots:
  void drawGbFrame();

private:
  std::unique_ptr<Ui::MainWindow> ui_;

  std::unique_ptr<SystemManager> sm_;

  QTimer timer_;

  const IPixelBuffer* buffer_;

  QImage img_;
};

#endif // MAINWINDOW_H
