#include <QTest>

/* https://doc.qt.io/qt-5/qtest-overview.html
 *
 * - "To create a test, subclass QObject and add one or more 
 *   private slots to it. Each private slot is a test function 
 *   in your test." 
 */
class MainWindowTest : public QObject {
  Q_OBJECT
private slots:
  void TestCounter();
};
