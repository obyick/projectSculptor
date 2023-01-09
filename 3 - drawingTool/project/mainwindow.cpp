#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <sculptor.h>
#include <cstdlib>
#include <dialog.h>
#include <QDebug>
#include <QString>
#include <QFileDialog>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::MainWindow) {
    ui -> setupUi(this);

    dx = 46, dy = 104, dz = 46;
    r = 0, g = 0, b = 0;

    currentObject = VOXEL;

    s = new Sculptor(dx, dy, dz);

    ui -> horizontalSliderDX -> setMaximum(dx - 1);
    ui -> horizontalSliderDY -> setMaximum(dy - 1);
    ui -> horizontalSliderDZ -> setMaximum(dz - 1);

    ui -> horizontalSliderBoxX -> setMaximum(dx - 1);
    ui -> horizontalSliderBoxY -> setMaximum(dy - 1);
    ui -> horizontalSliderBoxZ -> setMaximum(dz - 1);

    if(dx < dy && dx <dz) ui -> horizontalSliderRaio -> setMaximum((dx - 1) / 2);
    else if (dy < dx && dy < dz) ui -> horizontalSliderRaio -> setMaximum((dy - 1) / 2);
    else ui -> horizontalSliderRaio -> setMaximum((dz - 1) / 2);

    ui -> horizontalSliderEllipseRx -> setMaximum((dx - 1) / 2);
    ui -> horizontalSliderEllipseRy -> setMaximum((dy - 1) / 2);
    ui -> horizontalSliderEllipseRz -> setMaximum((dz - 1) / 2);
    ui -> widgetDraw -> loadMatriz(s -> getPlano(ui -> horizontalSliderDZ -> value(), XY));

    actionGroup = new QActionGroup(this);
    actionGroup -> addAction(ui -> action_putVoxel);
    actionGroup -> addAction(ui -> action_cutVoxel);
    actionGroup -> addAction(ui -> action_putBox);
    actionGroup -> addAction(ui -> action_cutBox);
    actionGroup -> addAction(ui -> action_putSphere);
    actionGroup -> addAction(ui -> action_cutSphere);
    actionGroup -> addAction(ui -> action_putEllipsoid);
    actionGroup -> addAction(ui -> action_cutEllipsoid);

    ui -> action_putVoxel -> setChecked(true);

    connect(ui -> action_putVoxel, SIGNAL(triggered()), this, SLOT(addVoxel()));
    connect(ui -> action_cutVoxel, SIGNAL(triggered()), this, SLOT(removeVoxel()));
    connect(ui -> action_putBox, SIGNAL(triggered()), this, SLOT(addBox()));
    connect(ui -> action_cutBox, SIGNAL(triggered()), this, SLOT(removeBox()));
    connect(ui -> action_putSphere, SIGNAL(triggered()), this, SLOT(addSphere()));
    connect(ui -> action_cutSphere, SIGNAL(triggered()), this, SLOT(removeSphere()));
    connect(ui -> action_putEllipsoid, SIGNAL(triggered()), this, SLOT(addEllipsoid()));
    connect(ui -> action_cutEllipsoid, SIGNAL(triggered()), this, SLOT(removeEllipsoid()));
    connect(ui -> actionSave, SIGNAL(triggered()), this, SLOT(save()));
    connect(ui -> horizontalSliderDZ, SIGNAL(valueChanged(int)), this, SLOT(slider_axix_z(int)));
    connect(ui -> actionQuit, SIGNAL(triggered()), this, SLOT(quit()));
    connect(ui -> action_newSculptor, SIGNAL(triggered(bool)), this, SLOT(newSculptor()));
    connect(ui -> horizontalSliderRed, SIGNAL(valueChanged(int)), this, SLOT(setRed(int)));
    connect(ui -> horizontalSliderBlue, SIGNAL(valueChanged(int)), this, SLOT(setGreen(int)));
    connect(ui -> horizontalSliderGreen, SIGNAL(valueChanged(int)), this, SLOT(setBlue(int)));
    connect(ui -> widgetDraw, SIGNAL(updatePosition(int, int)), this, SLOT(drawShape(int, int)));
    connect(ui -> widgetDraw, SIGNAL(updatePosition(int, int)), this, SLOT(updateCoords(int, int)));

}

MainWindow::~MainWindow() {delete ui;}

void MainWindow::updateColor() {
    QString color;
    color = "QPushButton { background-color: rgb(" + QString().setNum(r) + ", " + QString().setNum(b) + ", " + QString().setNum(g) + ");}";
    ui -> pushButtonShowColor -> setStyleSheet(color);
    s -> setColor(r, b, g);
}

void MainWindow::quit() {exit(0);}

void MainWindow::setRed(int r_) {
    r = r_;
    updateColor();
}

void MainWindow::setGreen(int g_) {
    g = g_;
    updateColor();
}

void MainWindow::setBlue(int b_) {
    b = b_;
    updateColor();
}

void MainWindow::drawShape(int hClick, int vClick) {
    switch(currentObject) {
    case(VOXEL):
        s -> putVoxel(vClick, hClick, ui -> horizontalSliderDZ -> value());
        ui -> widgetDraw -> loadMatriz(s -> getPlano(ui -> horizontalSliderDZ -> value(), XY));
        break;
    case(NOVOXEL):
        s -> cutVoxel(vClick, hClick, ui -> horizontalSliderDZ -> value());
        ui -> widgetDraw -> loadMatriz(s -> getPlano(ui -> horizontalSliderDZ -> value(), XY));
        break;
    case(BOX):
        s -> putBox(vClick - ui -> horizontalSliderBoxY -> value()/2,
                    vClick + ui -> horizontalSliderBoxY -> value()/2,
                    hClick - ui -> horizontalSliderBoxX -> value()/2,
                    hClick + ui -> horizontalSliderBoxX -> value()/2,
                    ui -> horizontalSliderDZ -> value() - ui -> horizontalSliderBoxZ -> value()/2,
                    ui -> horizontalSliderDZ -> value() + ui -> horizontalSliderBoxZ -> value() / 2);
        ui -> widgetDraw -> loadMatriz(s -> getPlano(ui -> horizontalSliderDZ -> value(), XY));
        break;
    case(NOBOX):
        s -> cutBox(vClick - ui -> horizontalSliderBoxY -> value()/2,
                    vClick + ui -> horizontalSliderBoxY -> value()/2,
                    hClick - ui -> horizontalSliderBoxX -> value()/2,
                    hClick + ui -> horizontalSliderBoxX -> value()/2,
                    ui -> horizontalSliderDZ -> value() - ui -> horizontalSliderBoxZ -> value()/2,
                    ui -> horizontalSliderDZ -> value() + ui -> horizontalSliderBoxZ -> value() / 2);
        ui -> widgetDraw -> loadMatriz(s -> getPlano(ui -> horizontalSliderDZ -> value(), XY));
        break;
    case(SPHERE):
        s -> putSphere(vClick, hClick, ui -> horizontalSliderDZ -> value(), ui -> horizontalSliderRaio -> value());
        ui -> widgetDraw -> loadMatriz(s -> getPlano(ui -> horizontalSliderDZ -> value(), XY));
        break;
    case(NOSPHERE):
        s -> cutSphere(vClick, hClick, ui -> horizontalSliderDZ -> value(), ui -> horizontalSliderRaio -> value());
        ui -> widgetDraw -> loadMatriz(s -> getPlano(ui -> horizontalSliderDZ -> value(), XY));
        break;
    case(ELLIPSOID):
        s -> putEllipsoid(vClick, hClick, ui -> horizontalSliderDZ -> value(),
                          ui -> horizontalSliderEllipseRx -> value(),
                          ui -> horizontalSliderEllipseRy -> value(),
                          ui -> horizontalSliderEllipseRz -> value());
        ui -> widgetDraw -> loadMatriz(s -> getPlano(ui -> horizontalSliderDZ -> value(), XY));
        break;
    case(NOELLIPSOID):
        s -> cutEllipsoid(vClick, hClick, ui -> horizontalSliderDZ -> value(),
                          ui -> horizontalSliderEllipseRx -> value(),
                          ui -> horizontalSliderEllipseRy -> value(),
                          ui -> horizontalSliderEllipseRz -> value());
        ui -> widgetDraw -> loadMatriz(s -> getPlano(ui -> horizontalSliderDZ -> value(), XY));
        break;
    }
}

void MainWindow::updateCoords(int vClick, int hClick) {
    ui -> horizontalSliderDX -> setValue(vClick);
    ui -> horizontalSliderDY -> setValue(hClick);
}

void MainWindow::newSculptor() {
    Dialog *D;
    D = new Dialog();
    D -> exec();
    if(D -> result() == QDialog::Accepted) {
        dx = D -> dXDialog().toInt();
        dy = D -> dYDialog().toInt();
        dz = D -> dZDialog().toInt();
        if(s != NULL) delete s;
        s = new Sculptor(dx, dy, dz);

        ui -> horizontalSliderDX -> setMaximum(dx - 1);
        ui -> horizontalSliderDY -> setMaximum(dy - 1);
        ui -> horizontalSliderDZ -> setMaximum(dz - 1);
        ui -> horizontalSliderBoxX -> setMaximum(dx - 1);
        ui -> horizontalSliderBoxY -> setMaximum(dy - 1);
        ui -> horizontalSliderBoxZ -> setMaximum(dz - 1);

        if(dx < dy && dx <dz) ui -> horizontalSliderRaio -> setMaximum((dx - 1) / 2);
        else if(dy < dx && dy < dz) ui -> horizontalSliderRaio -> setMaximum((dy - 1) / 2);
        else ui -> horizontalSliderRaio -> setMaximum((dz - 1) / 2);

        ui -> horizontalSliderEllipseRx -> setMaximum((dx - 1) / 2);
        ui -> horizontalSliderEllipseRy -> setMaximum((dy - 1) / 2);
        ui -> horizontalSliderEllipseRz -> setMaximum((dz - 1) / 2);
    }

    ui -> widgetDraw -> loadMatriz(s -> getPlano(ui -> horizontalSliderDZ -> value(), XY));
    ui -> horizontalSliderRed -> setValue(0);
    ui -> horizontalSliderGreen -> setValue(0);
    ui -> horizontalSliderBlue -> setValue(0);
}

void MainWindow::save() {
    QFileDialog D;
    QString selectedFilter;
    QString filename = D.getSaveFileName(this, tr("Save"), QDir::currentPath(), tr("Arquivo OFF(*.off)"), &selectedFilter);
    if(filename.isNull()) return;
    s -> writeOFF(filename.toStdString());
}

void MainWindow::addVoxel() {currentObject = VOXEL;}

void MainWindow::removeVoxel() {currentObject = NOVOXEL;}

void MainWindow::addBox() {currentObject = BOX;}

void MainWindow::removeBox() {currentObject = NOBOX;}

void MainWindow::addSphere() {currentObject = SPHERE;}

void MainWindow::removeSphere() {currentObject = NOSPHERE;}

void MainWindow::addEllipsoid() {currentObject = ELLIPSOID;}

void MainWindow::removeEllipsoid() {currentObject = NOELLIPSOID;}

void MainWindow::slider_axis_z(int value) {ui -> widgetDraw -> loadMatriz(s -> getPlano(value, XY));}

