#ifndef HEADBUTTON_H
#define HEADBUTTON_H

#include <QPushButton>
#include <QPixmap>
#include <QSize>

class HeadButton : public QPushButton
{
    Q_OBJECT
public:
    explicit HeadButton(QWidget *parent = 0);
    HeadButton(QString filename, QWidget *parent = 0);

private:

signals:

public slots:

};

#endif // HEADBUTTON_H
