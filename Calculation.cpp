#include "Calculation.h"

QPointF calculations::CalcLengthOfVector(const double &x1, const double &y1, const double &x2, const double &y2)
{
    double x_lenght = std::fabs(x2 - x1);
    double y_length = std::fabs(y2 - y1);
    QPointF Point(x_lenght, y_length);

    return  Point;
}

QPointF calculations::Normalize(const QPointF &Vec)
{
    double VecSize = std::sqrt((std::pow(Vec.x(), 2) + std::pow(Vec.y(), 2)));
    QPointF NormailisedVec(Vec.x()/VecSize, Vec.y()/VecSize);

    return NormailisedVec;
}

double calculations::GetHypotinuse(const QPointF &Vec)
{
    double VecSize = std::sqrt((std::pow(Vec.x(), 2) + std::pow(Vec.y(), 2)));
    return  VecSize;
}

QPointF calculations::CalcNormal(const QPointF &Vec)
{
    QPointF Normal(-Vec.y(), Vec.x());
    return Normal;
}

void calculations::ScaleX(double & x)
{
    x -= 200;
}

QLineF calculations::DrawReflection(QPainter * painter)
{
    double Ax1, Ay1, Ax2, Ay2, Bx1, By1, Bx2, By2;
    double X_AxisBegin = 20;
    double Y_AxisBeginKoaf = 700;
    double X_Scale = 50;

    Ax1 = 600.0; Ay1 = 100.0;
    Ax2 = 900.0; Ay2 = 500.0;

    QPointF Line(CalcLengthOfVector(Ax1, Ay1, Ax2, Ay2));

    Bx1 = 700.0; By1 = 600.0;
    Bx2 = 700.0; By2 = 250.0;

    painter->setPen({Qt::yellow, 20});
    painter->drawLine(Ax1, Y_AxisBeginKoaf - Ay1, Ax2, Y_AxisBeginKoaf - Ay2);
    painter->setPen({Qt::green, 20});
    painter->drawLine(Bx1, Y_AxisBeginKoaf - By1, Bx2, Y_AxisBeginKoaf - By2);

    QPointF Beam(CalcLengthOfVector(Bx1, By1, Bx2, By2));

    double HypoA = GetHypotinuse(Line);
    double HypoB = GetHypotinuse(Beam);

    painter->setPen({Qt::yellow, 20});
    painter->drawLine(X_AxisBegin + X_Scale, Y_AxisBeginKoaf, Line.rx(), Y_AxisBeginKoaf - Line.ry());
    painter->setPen({Qt::blue, 20});

    double k =  Beam.rx() + X_Scale;
    painter->drawLine(X_AxisBegin + X_Scale, Y_AxisBeginKoaf, k + X_AxisBegin, Y_AxisBeginKoaf - std::fabs(Beam.ry()));

    double sinA = Line.y() / HypoA;
    double radA = std::asin(sinA);

    double sinB = Beam.y() / HypoB;
    double radB = std::fabs(std::asin(sinB));


    double NormalRad = radA + radB;
    double sinNormal = std::sin(NormalRad);
    double NormalVec = sinNormal * HypoB;

    painter->setPen({Qt::red, 20});
    QPointF Normal(-HypoB, NormalVec);
    painter->drawLine(X_AxisBegin + X_Scale, Y_AxisBeginKoaf, Normal.x(), Y_AxisBeginKoaf - Normal.y());

    double beamRad = radA + 2 * radB; //radA + radB + radB;
    double beamSin = std::sin(beamRad);
    double BeamY = beamSin * HypoA;

    painter->setPen({Qt::black, 20});
    QPointF reflected_beam(-HypoA, BeamY);
    painter->drawLine(Bx2, Y_AxisBeginKoaf - By2, reflected_beam.x(), Y_AxisBeginKoaf - reflected_beam.y());
    QLineF ReflectedBeam(Bx2, Y_AxisBeginKoaf - By2, reflected_beam.x(), Y_AxisBeginKoaf - reflected_beam.y());
    return ReflectedBeam;
}

void calculations::DrawReflection2(QPainter * painter)
{

    double Ax1, Ay1, Ax2, Ay2, Bx1, By1, Bx2, By2;
    double X_AxisBegin = 20;
    double Y_AxisBeginKoaf = 700;
    double X_Scale = 1000;

    Ax1 = 100.0; Ay1 = 400.0;
    Ax2 = 400.0; Ay2 = 100.0;

    QPointF line(CalcLengthOfVector(Ax1, Ay1, Ax2, Ay2));

    Bx1 = 600.0; By1 = 300.0;
    Bx2 = 300.0; By2 = 200.0;

    QPointF beam(CalcLengthOfVector(Bx1, By1, Bx2, By2));

    painter->setPen({Qt::yellow, 20});
    painter->drawLine(Ax1, Y_AxisBeginKoaf - Ay1, Ax2, Y_AxisBeginKoaf - Ay2);
    painter->setPen({Qt::green, 20});
    painter->drawLine(Bx1, Y_AxisBeginKoaf - By1, Bx2, Y_AxisBeginKoaf - By2);

    QPointF a(0, 0);
    QPointF b(line.x(), line.ry());

    painter->setPen({Qt::yellow, 20});
    painter->drawLine(a, b);

    painter->setPen({Qt::green, 20});
    painter->drawLine(0, 0, beam.x(), std::fabs(beam.ry()));

    double HypoA = GetHypotinuse(line);
    double HypoB = GetHypotinuse(beam);
    QPointF NormalisedLine(line.rx() / HypoA, line.ry() / HypoA);
    QPointF NormalisedBeam(beam.rx() / HypoB, line.ry() / HypoB);

    double radA = std::asin(NormalisedLine.y());
    double radB = std::fabs(std::asin(NormalisedBeam.y()));

    double NormalRad = radA + radB;
    double sinNormal = std::sin(NormalRad);
    double NormalVec = sinNormal * HypoB;

    double scale_for_normal = 400;
    painter->setPen({Qt::red, 20});
    QPointF Normal(-HypoB * scale_for_normal, NormalVec * scale_for_normal);
    painter->drawLine(scale_for_normal, scale_for_normal, Normal.x(), Normal.y());

    double beamRad = radA + 2 * radB; //radA + radB + radB;
    double beamSin = std::asin(beamRad);
    double BeamY = beamSin * HypoA;

    // обратный перенос на начальную поврехность.
    painter->setPen({Qt::black, 20});
    QPointF reflected_beam(-HypoA, BeamY);
    painter->drawLine(Bx2, Y_AxisBeginKoaf - By2, reflected_beam.x(), Y_AxisBeginKoaf - reflected_beam.y());
    QLineF ReflectedBeam(Bx2, Y_AxisBeginKoaf - By2, reflected_beam.x(), Y_AxisBeginKoaf - reflected_beam.y());
}

int calculations::calcFirstReflection(int beam_angle_, int edge_angle_)
{
    int beta_angle = 90 - beam_angle_;
    int edge_angle_to_90 = 90 - edge_angle_;
    int translated_angle = beta_angle - edge_angle_to_90;
    translated_angle += edge_angle_;
    if(translated_angle > 360)
    {
        translated_angle = beam_angle_ - 180;
    }
    return translated_angle;
}
