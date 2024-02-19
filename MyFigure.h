#ifndef MYFIGURE_H
#define MYFIGURE_H

#include <QColor>
#include <vector>

struct MyPoint // Мало времени. Сделал пока на КТ типах
{
    int x = 0;
    int y = 0;

    MyPoint() = default;
    MyPoint(int x_, int y_) : x(x_), y(y_) {}
    void Translate(int dx_, int dy_) {x += dx_; y += dy_;}
};

class MyFigure
{
protected:
    MyPoint m_PointFigure;
    QColor m_ColorFugre {0, 0, 0};

public:
    MyFigure() = default;
    MyFigure(const MyPoint & point_fig_, const QColor & color_fig_)
    : m_PointFigure(point_fig_), m_ColorFugre(color_fig_){}

    void setColor(const QColor & color_fig_) {m_ColorFugre = color_fig_;}
    const QColor & getColor() const {return m_ColorFugre;}

    virtual void Translate(int dx, int dy) = 0;
    virtual ~MyFigure() {};
};

#endif // MYFIGURE_H
