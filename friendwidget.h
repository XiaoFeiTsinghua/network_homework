#ifndef FRIENDWIDGET_H
#define FRIENDWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QString>
#include <QDebug>
#include <QImage>
#include <opencv.hpp>
#include <cv.h>

class FriendWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FriendWidget(QWidget *parent = 0);
    FriendWidget(int id, int bt, QString num, QPixmap p, QString n, QString s, int b, QWidget *parent = 0);
    void init();
    void choose();
    void cancel_choose();
    void setBig(int b);
    int isBig();
    void online();
    void offline();

    int id;
    int belongto;
    QString studentnum;
    QPixmap photopix, showphoto;
    QString namestr;
    QString signstr;
    int big;
signals:

public slots:
private:
    QLabel *photo;
    QLabel *name;
    QLabel *sign;
};

#endif // FRIENDWIDGET_H
