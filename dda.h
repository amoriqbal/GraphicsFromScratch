#ifndef DDA_H
#define DDA_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class DDA; }
QT_END_NAMESPACE

class DDA : public QMainWindow
{
    Q_OBJECT

public:
    DDA(QWidget *parent = nullptr);
    ~DDA();

private:
    Ui::DDA *ui;

protected:
    void paintEvent(QPaintEvent *);
    void dda(QPainter *qp);
    void bresenhams(QPainter *qp);
};
#endif // DDA_H
