#ifndef DDA_H
#define DDA_H

#include <QMainWindow>
#include <vector>
QT_BEGIN_NAMESPACE
namespace Ui { class DDA; }
QT_END_NAMESPACE
struct Pix{
    QColor col;
    int x, y;
};

class DDA : public QMainWindow
{
    Q_OBJECT

public:
    DDA(QWidget *parent = nullptr);
    ~DDA();

public:
    Ui::DDA *ui;


    std::vector<Pix> pix;
    int gap, shiftx,shifty;
    void drawGrid(QPainter *qp);
    void drawHGrid(QPainter *qp);
    void drawVGrid(QPainter *qp);
    void zoomin();
    void zoomout();
    void plot(QPainter *qp, int x1, int y1);
    void plot(QPainter *qp, int x1, int y1, QColor col);
    int x(int x);
    int y(int y);
    void paintEvent(QPaintEvent *);
    void ddaLine(QPainter *g, int x1, int y1, int x2, int y2);
    void bresenham(QPainter *g, int x1, int y1, int x2, int y2);
    void midpoint(QPainter *g, int x0, int y0, int x1, int y1, QColor col);
    void drawPoly(QPainter *g, int n, int *x, int *y, QColor col);
    void boundaryFill(QPainter *g, int x1, int y1,QColor col);
    QColor getPixel(int x1,int y1);
    void drawTree(QPainter *g, int x1, int y1);
    void virtual paint(QPainter *g);
    bool eventFilter(QObject *object, QEvent *ev);

private slots:
    void on_zoomOut_clicked();
    void on_zoomIn_clicked();
    virtual void on_pushButton_clicked();
    virtual void on_bird_button_pressed();
    virtual void on_tree_button_pressed();
    virtual void on_birdSize_textChanged(const QString &s);
    virtual void on_birdTilt_textChanged(const QString &s);
    virtual void on_birdHead_textChanged(const QString &s);
    virtual void on_birdSpeed_textChanged(const QString &s);
    virtual void on_birdFlock_textChanged(const QString &s);
    virtual void on_birdWing_textChanged(const QString &s);
    virtual void on_birdTail_textChanged(const QString &s);
};
#endif // DDA_H
