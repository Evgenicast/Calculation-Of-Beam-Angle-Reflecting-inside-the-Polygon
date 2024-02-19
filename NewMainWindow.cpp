#include "NewMainWindow.h"
#include "ui_NewMainWindow.h"

NewMainWindow::NewMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::NewMainWindow)
{
    ui->setupUi(this);
}

NewMainWindow::~NewMainWindow()
{
    delete ui;
}

