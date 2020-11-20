#include <QPushButton>

class MainWindow_OLD : public QPushButton {
  Q_OBJECT
public:
  MainWindow_OLD();
  ~MainWindow_OLD();
  int GetCount() const;
private slots:
  void OnClick();
private:
  int counter_;
};
