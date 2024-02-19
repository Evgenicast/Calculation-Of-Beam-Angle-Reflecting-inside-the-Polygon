#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QLabel>
#include <QMessageBox>
#include <NewMainWindow.h>
#include <QJsonObject>
#include "mywidgetdraw.h"
#include "MyDesk.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class mainwindow : public QMainWindow
{
    Q_OBJECT

private:

    Ui::MainWindow * ui; NewMainWindow * m_NewMainWindow;
    MyWidgetDraw * m_MyWidgetDraw = nullptr;
    QLabel *lblX, *lblY, *label = nullptr;

    MyDesk m_MyDesk;
    int m_VerteciesCount;
    QJsonObject obj;

public:
    mainwindow(QWidget *parent = nullptr);
    ~mainwindow();   

    void GetPolygonData();
    void SaveToJson(QJsonArray &mainObject_);

private slots:
    void on_actionFree_triggered();
    void on_actionFixed_triggered();
    void on_actionAdd_N_of_Vertecies_triggered();
    void on_Information_clicked();
    void on_ClearDesk_clicked();
    void on_DrawPolygon_clicked();
    void on_actionLOAD_from_Json_triggered();
    void on_Example_clicked();
    void on_Example2_clicked();
    void on_pushButton_clicked();
    void on_dial_valueChanged(int value);
};
#endif // MAINWINDOW_H
