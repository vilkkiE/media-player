#include "MainWindowTest.hpp"
#include "MainWindow_OLD.hpp"

void MainWindowTest::TestCounter() {
  MainWindow_OLD window;
  // Simulate button click
  QTest::mouseClick(&window, Qt::LeftButton, Qt::NoModifier, QPoint(0, 0));
  // MainWindow_OLD state should now change and click count should be 1
  QVERIFY(window.GetCount() == 1);
}
