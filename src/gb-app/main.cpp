#include <QApplication>

#include "widgets/mainwindow.h"


auto main(int argc, char* argv[]) -> int
{
  QApplication a(argc, argv); // NOLINT(misc-const-correctness)
  a.setApplicationName("GBEmu"); // NOLINT(readability-static-accessed-through-instance)
  a.setOrganizationName("Mehrdraufhaber"); // NOLINT(readability-static-accessed-through-instance)

  MainWindow w;
  w.show();

  return a.exec(); // NOLINT(readability-static-accessed-through-instance)
}
