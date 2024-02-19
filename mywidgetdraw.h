#ifndef MYWIDGETDRAW_H
#define MYWIDGETDRAW_H

#include "MyDesk.h"
#include <QWidget>

class MyWidgetDraw : public QWidget
{
    Q_OBJECT

private:
    MyDesk & m_MyDesk_ref;

    float m_XsizeAspect = 0.0f;
    float m_YsizeAspect = 0.0f;
    double angle_koaf = 0.0;
    float CurX = 0.0f, CurY = 0.0f;
    float OldX = 0.0f, OldY = 0.0f;
    bool MouseDown = false;
    bool m_FixLine = false;
    bool m_IsIntersection = false;
    bool m_isShoot = false;
    bool m_isObject = false;

    std::list<QLineF> m_LinesList; // не должен быть тут! Временно. Потом перенести.
    QPointF m_IntersectionPoint;

    virtual void resizeEvent(QResizeEvent * event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void keyPressEvent(QKeyEvent * press_event) override;

public:
    explicit MyWidgetDraw(MyDesk & my_desk_, QWidget * parent = nullptr)
    : m_MyDesk_ref(my_desk_), QWidget(parent){}

    const bool & GetIsShoot() { return m_isShoot; }

    void clear()
    {
        m_LinesList.clear();
    }
};


#endif // MYWIDGETDRAW_H
