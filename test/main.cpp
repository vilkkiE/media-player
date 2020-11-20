#include <QTest>
#include <QApplication>
#include "MainWindowTest.hpp"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  int status = 0;
  auto runTest = [&status, argc, argv](QObject* obj) {
    status |= QTest::qExec(obj, argc, argv);
  };

  runTest(new MainWindowTest);
  //runTest(new otherTest);

  return status;
}

