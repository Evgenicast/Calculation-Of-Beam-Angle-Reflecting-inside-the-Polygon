#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QIntValidator>
#include <QInputDialog>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


mainwindow::mainwindow(QWidget *parent)
: QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    lblX = new QLabel("X = n/a"); //пока не работает
    lblY = new QLabel("Y = n/a");
    lblX->setFixedWidth(100);
    lblY->setFixedWidth(100);
    ui->statusbar->addWidget(lblX);
    ui->statusbar->addWidget(lblY);

    m_MyWidgetDraw = new MyWidgetDraw(m_MyDesk);
    ui->scrollArea->setWidget(m_MyWidgetDraw);

    m_MyWidgetDraw->setContextMenuPolicy(Qt::ActionsContextMenu);
    m_MyWidgetDraw->addAction(ui->actionFree);
    m_MyWidgetDraw->addAction(ui->actionFixed);

    m_MyWidgetDraw->setMouseTracking(true);
    m_MyWidgetDraw->setFocusPolicy(Qt::StrongFocus);
    m_NewMainWindow = new NewMainWindow();
}

mainwindow::~mainwindow()
{
    delete ui;
}

void mainwindow::GetPolygonData()
{
    QDialog dialog(this);
    QFormLayout form(&dialog);
    label = new QLabel("ENTER VERTECIES COORDS");
    label->setStyleSheet("QLabel { color : white; }");
    form.addRow(label);
    std::list<QLineEdit *> fieldsList;

    QLineEdit * lineEdit1 = new QLineEdit();
    lineEdit1->setValidator(new QIntValidator(0, 5000, this));

    for(int i = 0; i < m_VerteciesCount; ++i)
    {
        QLineEdit * lineEdit = new QLineEdit(&dialog);
        QString label = QString("<span style=\" color:#f93;\"> Coord %1</span>").arg(i%2 ? "y" : "x");
        lineEdit->setStyleSheet("color : black; color : white; ");
        form.addRow(label, lineEdit);
        fieldsList.emplace_back(lineEdit);
    }

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QColor red({90,110,102});
    buttonBox.setStyleSheet(QString("background:%1").arg(red.name()));
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    QJsonArray mainObject;
    dialog.exec();

    int i = 1;
    double x = 0.0;
    for(const auto & it : fieldsList)
    {
        if( i % 2 == 0 )
        {
            auto data1 = QJsonObject(
            {
                qMakePair(QString("x"), QJsonValue(x)),
                qMakePair(QString("y"), QJsonValue( it->text().toDouble()) ),
            });
            mainObject.push_back(data1);
        }
        else
        {
            x = it->text().toDouble();
        }
        ++i;
    }
    SaveToJson(mainObject);
}

void mainwindow::on_actionFree_triggered()
{
    m_MyDesk.SetMode(true);
}

void mainwindow::on_actionFixed_triggered()
{
    m_MyDesk.SetMode(false);
    m_MyDesk.SetModeInput(false);
}

void mainwindow::on_actionAdd_N_of_Vertecies_triggered()
{
    QString redPart = QString("<span style=\" color:#f93;\"> N = %1</span>").arg("");
    m_VerteciesCount = (QInputDialog::getInt(this, ("Enter N of Vertecies"), (redPart), 2, -50, 50, 1) * 2);
    GetPolygonData();
}

void mainwindow::on_Information_clicked()
{
    m_NewMainWindow->show();
}

void mainwindow::on_ClearDesk_clicked()
{
    m_MyDesk.ClearAll();
    m_MyDesk.SetIsClear(true);
    m_MyWidgetDraw->clear();
    m_MyDesk.SetIsCalcExampleTrue_1(false);
    m_MyDesk.SetIsCalcExampleTrue_2(false);
}

void mainwindow::on_DrawPolygon_clicked()
{
    if(m_MyDesk.getFigures().empty())
    {
         ui->label->setText(QString("Can't Draw! NO DATA! "));
         return;
    }
    m_MyDesk.SetModeInput(true);
    m_MyDesk.SetIsClear(false);
    this->repaint();
}

void mainwindow::SaveToJson(QJsonArray & mainObject_)
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save to JSON Format", ".", "JSON files (*.json)");
    qDebug() << "fileName =" << fileName;
    if (fileName.isEmpty())
        return;

    QJsonDocument jsonDoc;
    obj.insert("Vertecies", mainObject_);
    jsonDoc.setObject(obj);
    QFile myFile(fileName);
    if (!myFile.open(QIODevice::WriteOnly))
        throw std::runtime_error("Something is wrong during writting a file");

    myFile.write(jsonDoc.toJson());
}

void mainwindow::on_actionLOAD_from_Json_triggered()
{
    QList<QPoint> polygon;
    QString fileName = QFileDialog::getOpenFileName(this, "Load from JSON Format", ".", "JSON files (*.json)");
    qDebug() << "fileName =" << fileName;
    if (fileName.isEmpty())
        return;

    QFile myFile(fileName);
    if (myFile.open(QIODevice::ReadOnly))
    {
        QJsonParseError parseError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(myFile.readAll(), &parseError);
        if (parseError.error == QJsonParseError::NoError)
        {
            if (jsonDoc.isObject())
            {
                obj = jsonDoc.object();
                const QJsonArray & figArray = obj["Vertecies"].toArray();
                for(auto it = figArray.begin(); it != figArray.end(); ++it)
                {
                    const QJsonObject &obj = it->toObject();
                    int x = obj["x"].toInt();
                    int y = obj["y"].toInt();
                    int z = ui->scrollArea->window()->size().height();
                    z += 200;
                    polygon.push_back(QPoint(x, z - y));
                }
                m_MyDesk.AddPolygon(polygon);
            }
        }
        else
        {
            qDebug() << parseError.errorString();
        }
    }
    else
    {
        qDebug() << "json file not open";
    }
}

void mainwindow::on_Example_clicked()
{
    m_MyDesk.SetIsCalcExampleTrue_1(true);
}


void mainwindow::on_Example2_clicked()
{
    m_MyDesk.SetIsCalcExampleTrue_2(true);
}


void mainwindow::on_pushButton_clicked()
{
    m_MyDesk.SetEdges();
    m_MyDesk.Start();
    this->repaint();
}


void mainwindow::on_dial_valueChanged(int value)
{
    ui->lcdNumber->display(value);
    m_MyDesk.SetBeam(value);    
    this->repaint();
}

