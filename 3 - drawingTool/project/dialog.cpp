#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent):QDialog(parent), ui(new Ui::Dialog) {ui -> setupUi(this);}

Dialog::~Dialog() {delete ui;}

QString Dialog::dXDialog() {return ui -> lineEditDX -> text();}

QString Dialog::dYDialog() {return ui -> lineEditDY -> text();}

QString Dialog::dZDialog() {return ui -> lineEditDZ -> text();}


