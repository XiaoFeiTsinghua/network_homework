#ifndef GROUPWIDGET_H
#define GROUPWIDGET_H

#include <QWidget>
#include <QLabel>

class GroupWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GroupWidget(QWidget *parent = 0);
    GroupWidget(int id, QString n, int f, int e, QWidget *parent = 0);
    void init();
    int id;
    QString name;
    int friendsingroup;
    int expand;
    QLabel *nameLabel;
private:

signals:

public slots:

};

#endif // GROUPWIDGET_H
