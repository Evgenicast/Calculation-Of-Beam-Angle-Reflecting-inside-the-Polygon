#include "mywidgetdraw.h"
#include <QPainter>
#include <QMouseEvent>
#include <Calculation.h>

void MyWidgetDraw::resizeEvent([[maybe_unused]]QResizeEvent * event)
{
    m_MyDesk_ref.NormalizeAxis(event->size().width(), event->size().height());
    m_XsizeAspect = 1 / event->size().width();
    m_YsizeAspect = 1 / event->size().height();    
}

void MyWidgetDraw::mousePressEvent(QMouseEvent * event)
{
    if(OldX == 0 && OldY == 0)
    {
        OldX = event->pos().x();
        OldY = event->pos().y();
    }
    else if(event->buttons() & Qt::LeftButton)
    {
        if(m_MyDesk_ref.GetMode())// free
        {
            CurX = event->pos().x();
            CurY = event->pos().y();
        }
        OldX = CurX;
        OldY = CurY;
        MouseDown = true;
    }

    this->repaint();
}

void MyWidgetDraw::mouseMoveEvent(QMouseEvent *event)
{
    if(CurX == 0 && CurY == 0)
    {
        OldX = event->pos().x();
        OldY = event->pos().y();
    }
    if (event->buttons() & Qt::LeftButton)
    {
        CurX = event->pos().x();
        CurY = event->pos().y();
    }
    this->repaint();
}

void MyWidgetDraw::mouseReleaseEvent(QMouseEvent *event)
{
    MouseDown = false;
    QPointF p1{OldX, OldY};
    QPointF p2{CurX, CurY};
    QLineF line(p1, p2);

    if(!m_MyDesk_ref.getFigures().empty())
    {
        auto MyPolygonClass = dynamic_cast<MyPolygon*>(m_MyDesk_ref.getFigures().back());
        auto polygon = MyPolygonClass->GetPolygon().get();
        if(!polygon->containsPoint(p2, Qt::OddEvenFill)) // if contains then inside will alarm
        {
            qDebug() << "FOUND " << p2 << " " ;
            m_IntersectionPoint = p2;
            m_IsIntersection = true;
        }
    }

    m_LinesList.push_back(line);
    m_FixLine = true;
}

void MyWidgetDraw::paintEvent([[maybe_unused]] QPaintEvent *event)
{
    QPainter painter(this);

    painter.setPen(QPen(Qt::darkCyan, 4));
    painter.drawRect(1, 0, this->width() - 2, this->height()); // холст

    painter.setPen(QPen(Qt::darkRed, 3));
    painter.drawText(40, 40, QString().setNum(OldX));
    painter.drawText(40, 60, QString().setNum(OldY));

    painter.drawText(40, 20, QString().setNum(CurX));
    painter.drawText(100, 20, QString().setNum(CurY));

    double y_rad = std::fabs(1.57 - (m_MyDesk_ref.GetNormilizeAxisY() * CurY));
    double x_rad = 3.14 - (m_MyDesk_ref.GetNormilizeAxisX() * CurX);
    painter.drawText(700, 20, QString().setNum(y_rad));
    painter.drawText(700, 60, QString().setNum(x_rad));

    if (MouseDown)
    {
        int vPenW = 3;
        QPen vPen(QColor(220, 20, 20), vPenW);
        painter.setPen(vPen);
        painter.drawLine(QPoint(OldX, OldY), {static_cast<int>(CurX), static_cast<int>(CurY)});
    }

    if(m_FixLine == true)
    {
        for(const auto & line : m_LinesList)
        {
            painter.drawLine(QLineF(line));
        }
    }

    if(m_MyDesk_ref.GetModeInput() && !m_MyDesk_ref.GetIsClear())
    {
        auto polygon_to_prepare = dynamic_cast<MyPolygon*>(m_MyDesk_ref.getFigures().back());
        int vPenW = 7;
        QPen vPen(QColor(0, 100, 200), vPenW);
        painter.setPen(vPen);
        painter.drawPolygon(polygon_to_prepare->GetPolygon()->toPolygon());
    }

    if(m_IsIntersection == true)
    {
        int vPenW = 6;
        QPen vPen(QColor(0, 255, 200), vPenW);
        painter.setPen(vPen);
        painter.drawText(40, 100, QString().setNum(m_IntersectionPoint.x()));
        painter.drawText(40, 120, QString().setNum(m_IntersectionPoint.y()));
    }

    if(m_MyDesk_ref.GetIsCalcExample_1() == true)
    {
        calculations::DrawReflection(&painter);
    }

    if(m_MyDesk_ref.GetIsCalcExample_2() == true)
    {
        calculations::DrawReflection2(&painter);
    }
    if(m_MyDesk_ref.GetIsStartGame())
    {
        int vPenW = 6;
        QPen vPen(QColor(0, 255, 200), vPenW);
        painter.setPen(vPen);
        painter.drawLine(m_MyDesk_ref.GetStartVector());
    }
    if(m_isShoot)
    {
        int vPenW = 6;
        QPen vPen(QColor(255, 255, 200), vPenW);
        painter.setPen(vPen);
        for(const auto & i : m_MyDesk_ref.GetReflectedBeams())
        {
            painter.drawLine(i);
        }
    }
    if(m_isObject)
    {
        int vPenW = 6;
        QPen vPen(QColor(255, 255, 200), vPenW);
        QBrush brush(Qt::red);
        painter.setPen(vPen);
        painter.setBrush(brush);
        painter.drawRect(m_MyDesk_ref.GetObject());
    }

}

void MyWidgetDraw::keyPressEvent(QKeyEvent * press_event)
{
    angle_koaf += 0.5;
    switch (press_event->key())
    {
    case Qt::Key_V:
    {
        m_MyDesk_ref.Shoot();
        m_isShoot = true;
    }
        break;
    case Qt::Key_Left:

        break;
    case Qt::Key_Right:

        break;
    case Qt::Key_Down:

        break;
    case Qt::Key_B:
    {
        m_MyDesk_ref.InitiateObject();
        m_isObject = true;
    }
        break;
    }
    this->repaint();
}
