#include "MyDesk.h"
#include "Calculation.h"

void MyDesk::OnMousePress(int x, int y)
{
    ReStateLastCursorType(x, y);
    m_isMousDown = true;
}

void MyDesk::OnMouseRelease(int x, int y)
{
    m_CurX = x, m_CurY = y;
    m_isMousDown = false;
}

void MyDesk::ReStateLastCursorType(int x, int y)
{
    m_OldX = x;
    m_OldY = y;
}

void MyDesk::AddPolygon(const QList<QPoint> & polygon_)
{
    m_Figures.emplace_back(new MyPolygon(polygon_));
}

const std::pair<double, double> MyDesk::GetNormilisedAxis()
{
    return std::make_pair(m_NormaliseAxisX, m_NormaliseAxisY);
}

void MyDesk::NormalizeAxis(const double & widget_width_, const double & widget_height_)
{
    m_NormaliseAxisX = 3.1 / widget_width_;
    m_NormaliseAxisY = 6.3 / widget_height_;
}

void MyDesk::SetEdges()
{
    m_Edges.clear();
    MyPolygon * m  = dynamic_cast<MyPolygon*>(m_Figures.back());
    auto begin = m->GetPolygonData().begin();
    auto end = m->GetPolygonData().end() - 1;

    QPointF p1(begin->x(), begin->y());
    QPointF p5(end->x(), end->y());
    QLineF EdgeA(p1, p5);

    m_Edges.push_back(EdgeA);

    int cnt = 0;
    auto it = end - 1;
    for(; it != begin - 1; --it)
    {
        QLineF Edge(m_Edges[cnt].p2(), {static_cast<qreal>(it->x()), static_cast<qreal>(it->y())});
        m_Edges.push_back(Edge);
        ++cnt;
    }
}

void MyDesk::SetBeam(int val)
{
    m_angle = double(val);
    m_Start_Vector.setAngle((double)val);
}

void MyDesk::Start()
{
    m_Start_Vector.setP1(m_Edges.front().center());
    m_Start_Vector.setLength(50);
    m_IsStartGame = true;
}

void MyDesk::Shoot()
{
    std::vector<double> angles;
    auto begin = m_Edges.begin() + 1;
    double angle = m_Start_Vector.angle();
    for(; begin != m_Edges.end(); ++begin)
    {
        double prev_angle = angle;
        double next_angle = calculations::calcFirstReflection(prev_angle, begin->angle());
        angles.push_back(next_angle);
        angle = next_angle;
    }

    m_ReflectedBeams.clear();
    m_ReflectedBeams.append(m_Start_Vector);
    MyPolygon * polygon  = dynamic_cast<MyPolygon*>(m_Figures.back());
    int wall_hits_cnt = 0;
    double angle0 = m_Start_Vector.angle();
    for(int i = 0; i < 2000; ++i)
    {
        m_Start_Vector.setP1(m_Start_Vector.p2());
        m_Start_Vector.setLength(30);
        m_Start_Vector.setP2({m_Start_Vector.p2().x() + 1, m_Start_Vector.p2().y() + 1});
        m_Start_Vector.setAngle(angle0);
        if(!(polygon->GetPolygon()->containsPoint(m_Start_Vector.p2(), Qt::OddEvenFill)))
        {
            if(wall_hits_cnt == 1)
            {
               angle0 = angles[1];
               ++wall_hits_cnt;
            }
            else if(wall_hits_cnt == 2)
            {
                angle0 = angles[2];
                ++wall_hits_cnt;
            }
            else if(wall_hits_cnt == 3)
            {
                angle0 = angles[3];
                ++wall_hits_cnt;
            }
            else if(wall_hits_cnt == 4)
            {
                angle0 = angles[4];
                ++wall_hits_cnt;
            }
            else
            {
                ++wall_hits_cnt;
                angle0 = angles[0];
            }
        }
        else
        {
            if(m_object.contains(m_Start_Vector.p2()))
            {
                break;
            }
            m_ReflectedBeams.append(m_Start_Vector);
        }
    }
}

void MyDesk::InitiateObject()
{
    m_object.setCoords(400, 450, 450, 500);
}

void MyDesk::ClearAll()
{
    for (auto & pFigure : m_Figures)
        delete pFigure;

    m_Figures.clear();
}

MyDesk::~MyDesk()
{
    m_Figures.clear();
}
