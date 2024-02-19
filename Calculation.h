#ifndef CALCULATION_H
#define CALCULATION_H

#include <QPointF>
#include <cmath>

#include <QPainter>

namespace calculations
{
    QPointF CalcLengthOfVector(const double & x1, const double & y1, const double & x2, const double & y2);
    QPointF Normalize(const QPointF & Vec);
    double GetHypotinuse(const QPointF & Vec);
    QPointF CalcNormal(const QPointF & Vec);
    void ScaleX(double & x);

    QLineF DrawReflection(QPainter * painter);
    void DrawReflection2(QPainter * painter);

    int calcFirstReflection(int beam_angle_, int edge_angle_);

}// namespace calculation

#endif // CALCULATION_H
