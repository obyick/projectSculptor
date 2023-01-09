#ifndef PLOTTER_H
#define PLOTTER_H

#include <QWidget>
#include <sculptor.h>
#include <vector>
#include <QVector>

class Plotter:public QWidget {
    Q_OBJECT

public:
    explicit Plotter(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void setTam(int nl_, int nc_);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void loadMatriz(vector <vector <Voxel>> matriz);

signals:
    void updatePosition(int, int);

private:
    int nl, nc;
    bool pressed;
    vector <vector <Voxel>> v;
    int bv, bh;
    int dCel;
    int widthTela, heightTela;
    int widthCel, heightCel;
};

#endif // PLOTTER_H
