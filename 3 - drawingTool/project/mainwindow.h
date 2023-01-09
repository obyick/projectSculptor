#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <sculptor.h>
#include <dialog.h>
#include <QActionGroup>


enum {BOX, NOBOX, SPHERE, NOSPHERE, VOXEL, NOVOXEL, ELLIPSOID, NOELLIPSOID};

QT_BEGIN_NAMESPACE
namespace Ui {class MainWindow;}
QT_END_NAMESPACE

class MainWindow:public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int dx, dy, dz;
    float r, g, b;
    int currentObject;
    Sculptor *s;
    QActionGroup *actionGroup;
    void updateColor();

public slots:
    void quit();
    void setRed(int r_);
    void setGreen(int g_);
    void setBlue(int b_);
    void drawShape(int,int);
    void updateCoords(int, int);

private slots:
    void newSculptor();
    void save();
    void addVoxel();
    void removeVoxel();
    void addBox();
    void removeBox();
    void addSphere();
    void removeSphere();
    void addEllipsoid();
    void removeEllipsoid();
    void slider_axis_z(int);
};

#endif // MAINWINDOW_H
