#include "widget.h"
#include "logindialog.h"
#include <QDebug>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*

    Widget w("2012010526");
    w.show();
*/
    LoginDialog l;
    if(l.exec()==QDialog::Accepted)
    {
        qDebug()<<"wshow";
        QString name = l.getUsername();
        Widget w(name);
        qDebug()<<"wshow";
        w.show();
        qDebug()<<"wshow";
        return a.exec();
    }

    else
        return 0;
}
