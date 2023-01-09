#include "plotter.h"
#include <sculptor.h>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QPoint>
#include <QMouseEvent>
#include <QGradient>
#include <QSize>
#include <cmath>
#include <iostream>
#include <qdebug.h>

Plotter::Plotter(QWidget *parent):QWidget(parent) {
    nl = 10;
    nc = 10;

    pressed = false;

    widthTela = rect().width();
    heightTela = rect().height();
    widthCel = widthTela/nc;
    heightCel = heightCel/nl;

    if(heightCel > widthCel)dCel = widthCel;
    else dCel = heightCel;

    setTam(nl, nc);
}

void Plotter::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QBrush brush;
    QPen pen;
    QColor color;
    QRadialGradient gradient(QPointF(1, 1), 20);
    gradient.setColorAt(0, Qt::black);
    gradient.setColorAt(1, Qt::white);
    painter.setRenderHint(QPainter::Antialiasing, true);
    pen.setWidth(1);
    widthTela = rect().width();
    heightTela = rect().height();
    widthCel = widthTela/nc;
    heightCel = heightTela/nl;

    if (heightCel > widthCel) dCel = widthCel;
    else dCel = heightCel;

    bh = (widthTela - nc * dCel) / 2;
    bv = (heightTela - nl * dCel) / 2;
    gradient.setRadius(dCel);
    gradient.setFocalPoint(-0.15 * dCel, -0.15 * dCel);
    gradient.setCenter(-0.15 * dCel, -0.15 * dCel);
    painter.setPen(pen);
    painter.drawRect(rect());
    qDebug() << nl << nc << v.size() << v[0].size();

    for(int i = 0; i < nl; i++) {
        for(int j = 0; j < nc; j++) {
            if(v[i][j].isOn == true) {
                painter.save();
                painter.translate(j * dCel + bh + dCel / 2, i * dCel + bv + dCel / 2);
                painter.setPen(Qt::NoPen);
                color.setRgb(qRgb(v[i][j].r, v[i][j].g, v[i][j].b));
                gradient.setColorAt(0, Qt::white);
                gradient.setColorAt(0.0000001, color);
                gradient.setColorAt(1, color.darker());
                painter.setBrush(gradient);
                painter.drawRect(-dCel / 2, -dCel / 2, dCel, dCel);
                painter.restore();
            }else{
                brush.setColor(QColor(255, 255, 255, 0));
                painter.setBrush(brush);
                painter.drawRect(j * dCel + bh, i * dCel + bv, dCel, dCel);
            }
        }
    }
}

void Plotter::setTam(int nl_, int nc_) {
    nl = nl_;
    nc = nc_;
    repaint();
}

void Plotter::mousePressEvent(QMouseEvent *e) {
    int posHorizontal, posVertical;
    QRect ret;
    ret = rect();
    pressed = true;
    ret.adjust(bh, bv, -bh, -bv);

    if(ret.contains(e -> pos())) {
        posHorizontal = (e -> pos().x() - bh) * nc / ret.width();
        posVertical = (e -> pos().y() - bv) * nc / ret.width();
        emit updatePosition(posHorizontal, posVertical);
    }
}

void Plotter::mouseMoveEvent(QMouseEvent *e) {
    int posHorizontal, posVertical;
    QRect ret;
    ret = rect();
    ret.adjust(bh, bv, -bh, -bv);

    if(ret.contains(e -> pos()) && pressed == true) {
        posHorizontal = (e -> pos().x()-bh) * nc / ret.width();
        posVertical = (e -> pos().y() - bv) * nc / ret.width();
        emit updatePosition(posHorizontal, posVertical);
    }
}

void Plotter::mouseReleaseEvent(QMouseEvent *e) {pressed = false;}

void Plotter::loadMatriz(vector<vector<Voxel> > matriz) {
    nl = matriz.size();
    nc = matriz[0].size();
    v = matriz;
    repaint();
}
