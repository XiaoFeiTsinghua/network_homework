#include "functionwidget.h"

FunctionWidget::FunctionWidget(QWidget *parent) :
    QWidget(parent)
{
}

FunctionWidget::FunctionWidget(QString name, QWidget *parent) :
    QWidget(parent)
{
    username = name;
    addfriendButton = new QPushButton(this);
    addgroupButton = new QPushButton(this);
    addfriendw = new AddfriendWidget(username);
    addgroupw = new AddgroupWidget(username);
    cancelautoButton = new QPushButton(this);

    addfriendButton->resize(50, 30);
    addfriendButton->move(20, 0);
    addfriendButton->setText("查找");

    addgroupButton->resize(50, 30);
    addgroupButton->move(80, 0);
    addgroupButton->setText("添加分组");

    cancelautoButton->resize(50, 30);
    cancelautoButton->move(130, 0);
    cancelautoButton->setText("取消自动登录");


    connect(addfriendButton, &QPushButton::clicked, this, &FunctionWidget::addfriend);
    connect(addfriendw, &AddfriendWidget::infoSend, this, &FunctionWidget::friendinfoRecv);
    connect(addgroupButton, &QPushButton::clicked, this, &FunctionWidget::addgroup);
    connect(addgroupw, &AddgroupWidget::infoSend, this, &FunctionWidget::groupinfoRecv);
    connect(cancelautoButton, &QPushButton::clicked, this, &FunctionWidget::on_cancelautoButton_clicked);

}

void FunctionWidget::addfriend()
{
    emit preparingadd();
    qDebug()<<"add";
    if(addfriendw != NULL)
    {
        delete addfriendw;
        addfriendw = NULL;
        addfriendw = new AddfriendWidget(username);
        //connect(addfriendButton, &QPushButton::clicked, this, &FunctionWidget::addfriend);
        connect(addfriendw, &AddfriendWidget::infoSend, this, &FunctionWidget::friendinfoRecv);
    }
    addfriendw->show();

}

void FunctionWidget::friendinfoRecv(friendinfo fi)
{
    emit added();
    qDebug() << fi.id;
}

void FunctionWidget::addgroup()
{
    emit preparingadd();
    qDebug()<<"addgroup";
    if(addgroupw != NULL)
    {
        delete addgroupw;
        addgroupw = NULL;
        addgroupw = new AddgroupWidget(username);
        //connect(addgroupButton, &QPushButton::clicked, this, &FunctionWidget::addgroup);
        connect(addgroupw, &AddgroupWidget::infoSend, this, &FunctionWidget::groupinfoRecv);
    }
    addgroupw->show();

}

void FunctionWidget::groupinfoRecv(groupinfo gi)
{
    emit added();
    qDebug() << gi.id << "miao";
}

void FunctionWidget::on_cancelautoButton_clicked()
{
    setAuto(0);
}
