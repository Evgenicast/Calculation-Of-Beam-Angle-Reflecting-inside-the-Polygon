#include "MyPolygon.h"
#include <iostream>

void MyPolygon::Translate(int dx, int dy)
{
    if(!m_PointsVector.empty())
    {
        for(auto & it : m_PointsVector) // const закрывает Translate в структуре MyPoint;
        {
            auto x = it.x();
            x += dx;
            auto y = it.y();
            y += dy;
            it.setX(x);
            it.setY(y);
        }
    }
}

void MyPolygon::CreatePolygon()
{
    m_Polygon_uniq = std::make_unique<QPolygonF>(m_PolygonList);
}


