#include <QApplication>

#include "widgets/mainwindow.h"


int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  a.setApplicationName("GBEmu");
  a.setOrganizationName("Mehrdraufhaber");
  MainWindow w;
  w.show();

  return a.exec();
}
