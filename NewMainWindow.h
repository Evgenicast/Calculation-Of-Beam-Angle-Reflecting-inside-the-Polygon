#ifndef NEWMAINWINDOW_H
#define NEWMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class NewMainWindow; }
QT_END_NAMESPACE

class NewMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    NewMainWindow(QWidget *parent = nullptr);
    ~NewMainWindow();

private:
    Ui::NewMainWindow *ui;
};
#endif // NEWMAINWINDOW_H
