#include "MainWindow_OLD.hpp"
#include <QString>

MainWindow_OLD::MainWindow_OLD() {
  counter_ = 0;
  resize(300, 300);
  setText(QString::number(counter_));
  connect(this, SIGNAL (released()), this, SLOT (OnClick()));
}

MainWindow_OLD::~MainWindow_OLD() {
  
}

int MainWindow_OLD::GetCount() const {
  return counter_;
}

void MainWindow_OLD::OnClick() {
  setText(QString::number(++counter_));
}
