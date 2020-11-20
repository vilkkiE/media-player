#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QToolBar>
#include <iostream>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QToolBar *toolbar = addToolBar("Toolbar");
    QAction *action1 = toolbar->addAction("miniplayer on/off");
    connect(action1, &QAction::triggered, [&](){ui->centralwidget->toggleTlist();});
    connect(action1, &QAction::triggered, [&](){adjustSize(),resize(0,0), adjustSize();});
    QAction *action2 = toolbar->addAction("mute");
    connect(action2, &QAction::triggered, [&](){ui->centralwidget->mute();});
    QAction *action3 = toolbar->addAction("add songs");
    connect(action3, &QAction::triggered, [&](){ui->centralwidget->setFolder();});
    QAction *action4 = toolbar->addAction("reset folder");
    connect(action4, &QAction::triggered, [&](){ui->centralwidget->resetFolder(), ui->centralwidget->setFolder();});
    

}

MainWindow::~MainWindow()
{
    delete ui;
}


