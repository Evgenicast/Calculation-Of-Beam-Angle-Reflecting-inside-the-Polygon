#include "myline.h"

void MyLine::Translate(int dx, int dy)
{
    m_Point_A.x -= dx;
    m_Point_A.y -= dy;

    m_Point_B.x += dx;
    m_Point_B.y += dy;
}
