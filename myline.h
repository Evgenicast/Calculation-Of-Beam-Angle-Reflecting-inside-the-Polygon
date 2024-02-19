#ifndef MYLINE_H
#define MYLINE_H
#include "MyFigure.h"

class MyLine : public MyFigure // Пока сделал на КТ типах для экономии времени.
{
private:
    MyPoint m_Point_A;
    MyPoint m_Point_B;
    QColor m_Color_line {255, 0, 0};

public:
    MyLine() = default;
    MyLine(const MyPoint & point_a_, const MyPoint & point_b_, const QColor & color_)
    : m_Point_A(point_a_), m_Point_B(point_b_), m_Color_line(color_) {}

    virtual void Translate(int dx, int dy);
};

#endif // MYLINE_H
