#include "headbutton.h"

HeadButton::HeadButton(QWidget *parent) :
    QPushButton(parent)
{
}

HeadButton::HeadButton(QString filename, QWidget *parent) :
    QPushButton(parent)
{
    this->setFlat(true);
    QString s = "QPushButton{border:none;}";
    QString s1 = "QPushButton{background-image: url(:/qq/resource_image/" + filename + "_normal.png);background-repeat: repeat-none; background-position:center;}";
    QString s2 = "QPushButton:hover{background-image: url(:/qq/resource_image/" + filename + "_hover.png);background-repeat: repeat-none; background-position:center;}";
    QString s3 = "QPushButton:checked{background-image: url(:/qq/resource_image/" + filename + "_selected.png);background-repeat: repeat-none; background-position:center;}";
    this->setStyleSheet(s + s1 + s2 + s3);
    this->setCheckable(true);

    this->resize(50, 30);

}


