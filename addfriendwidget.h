#ifndef ADDFRIENDWIDGET_H
#define ADDFRIENDWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QString>
#include <QComboBox>
#include <QMessageBox>
#include <QBitmap>
#include <QPainter>
#include <QPoint>
#include <QMouseEvent>
#include <QButtonGroup>
#include <QVector>
#include "database.h"
class AddfriendWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AddfriendWidget(QWidget *parent = 0);
    AddfriendWidget(QString name, QWidget *parent = 0);
    void init();
private:
    //QLabel *nameLabel, *studentnumLabel, *groupLabel, *signLabel;
    QLabel *blueLabel, *logoLabel, *textLabel;
    QLineEdit *nameEdit, *studentnumEdit, *signEdit;
    QComboBox *groupBox, *photoBox;
    QPushButton *configButton, *cancelButton, *exitButton, *minButton, *findpeopleButton, *findgroupchatButton;
    QVector<QPushButton*> photos;
    QButtonGroup *photoGroup;
    QString username;
    QPoint dPos;
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void on_findpeopleButton_clicked();
    void on_findgroupchatButton_clicked();
    void choose_photo_x();

signals:
    void infoSend(friendinfo fi);
public slots:
    void emit_signal_infosend();

};

#endif // ADDFRIENDWIDGET_H
