#ifndef MYPOLYGON_H
#define MYPOLYGON_H

#include "MyFigure.h"
#include <QPolygonF>
#include <QLineF>
#include <QList>
#include <iterator>

class MyPolygon : public MyFigure
{
private:

    std::vector<QPointF> m_PointsVector;
    std::vector<int> m_RadsToVerteciesVec;
    QList<QPoint> m_PolygonList;
    std::unique_ptr<QPolygonF> m_Polygon_uniq;
    void CreatePolygon();

public:
    MyPolygon() = default;

    MyPolygon(const MyPoint & point_fig, const QColor & color_rect_)
    : MyFigure(point_fig, color_rect_) {}

    MyPolygon(const QList<QPoint> & polygon_)
    : MyFigure()
    {
        m_PolygonList = std::move(polygon_);
        CreatePolygon();
    }

    const QList<QPoint> GetPolygonData() const { return m_PolygonList; }
    virtual void Translate(int dx, int dy) override;
    const  std::unique_ptr<QPolygonF> & GetPolygon() const { return m_Polygon_uniq; }

    void Clear()
    {
        m_PolygonList.clear();
    }
};


#endif // MYRECT_H
