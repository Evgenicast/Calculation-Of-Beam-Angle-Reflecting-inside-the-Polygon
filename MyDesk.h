#ifndef MYDESK_H
#define MYDESK_H

#include "MyPolygon.h"
#include "MyFigure.h"

class MyDesk
{    
private:

    std::vector<MyFigure*> m_Figures;
    MyPolygon m_Polygon;
    std::vector<double> m_anglesVec;
    std::vector<QLineF> m_Edges;
    QList<QLineF> m_ReflectedBeams;
    QLineF m_Start_Vector;
    QRectF m_object;
    double m_angle = 90;

    int m_CurX = 0, m_CurY = 0;
    int m_OldX = 0, m_OldY = 0;

    bool m_isMousDown = false; // переделать в enum class
    bool m_isFreeMode = false;
    bool m_isFromInput = false;
    bool m_isClear = false;
    bool m_IsCalcExample_1 = false;
    bool m_IsCalcExample_2 = false;
    bool m_IsStartGame = false;

    double m_NormaliseAxisY = 0.0;
    double m_NormaliseAxisX = 0.0;

public:
    MyDesk() = default;

    void OnMousePress(int x, int y);
    void OnMouseRelease(int x, int y);
    void OnMouseMove(int x, int y);
    void ReStateLastCursorType(int x, int y);
    void AddPolygon(const QList<QPoint> & polygon_);

    //----------Set_Get_begin------------------------//
    void SetMode(bool mode) { m_isFreeMode = mode; }
    const bool & GetMode() const { return m_isFreeMode; }
    void SetModeInput(bool mode_) { m_isFromInput = mode_; }
    const bool & GetModeInput() const { return m_isFromInput; }
    void SetIsClear(bool is_clear) { m_isClear = is_clear; }
    const bool & GetIsClear() const { return m_isClear; }
    void SetIsCalcExampleTrue_1(bool mode) { m_IsCalcExample_1 = mode; }
    const bool & GetIsCalcExample_1() const { return m_IsCalcExample_1; }
    void SetIsCalcExampleTrue_2(bool mode) { m_IsCalcExample_2 = mode; }
    const bool & GetIsCalcExample_2() const { return m_IsCalcExample_2; }
    const double GetNormilizeAxisY() const { return m_NormaliseAxisY; }
    const double GetNormilizeAxisX() const { return m_NormaliseAxisX; }
    const std::pair<double, double> GetNormilisedAxis();
    const std::vector<MyFigure*> & getFigures() const {return m_Figures;}
    const QLineF & GetStartVector() const { return m_Start_Vector; }
    const bool & GetIsStartGame() const { return m_IsStartGame; }
    const QList<QLineF> & GetReflectedBeams() const { return m_ReflectedBeams; }
    const QRectF & GetObject() const { return m_object; }

    //------------Set_Get_end-----------------------//

    void SendSingalInterraction();
    void NormalizeAxis(const double & widget_width_, const double & widget_height_ ); // scaling axis to 1

    void SetEdges();
    void SetBeam(int val);
    void Start();
    void Shoot();
    void InitiateObject();

    void ClearAll();

    ~MyDesk();
};

#endif // MYDESK_H
