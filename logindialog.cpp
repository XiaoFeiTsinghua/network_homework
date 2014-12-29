#include "logindialog.h"

LoginDialog::LoginDialog(QDialog *parent) :
    QDialog(parent)
{
    logoLabel = new QLabel(this);
    photoLabel = new QLabel(this);
    nameLabel = new QLabel(this);
    tipsLabel = new QLabel(this);
    warnLabel = new QLabel(this);
    autologCheck = new QCheckBox(this);
    rememberCheck = new QCheckBox(this);
    userCombo = new QComboBox(this);
    keyEdit = new QLineEdit(this);
    loginButton = new QPushButton(this);
    exitButton = new QPushButton(this);
    minButton = new QPushButton(this);
    clearuserButton = new QPushButton(this);
    findkeyButton = new QPushButton(this);
    shrinkButton = new QPushButton(this);

    connect(loginButton, &QPushButton::clicked, this, &LoginDialog::on_loginButton_clicked);
    connect(exitButton, &QPushButton::clicked, this, &LoginDialog::close);
    connect(minButton, &QPushButton::clicked, this, &LoginDialog::showMinimized);
    connect(clearuserButton, &QPushButton::clicked, this, &LoginDialog::on_clearuserButton_clicked);
    connect(findkeyButton, &QPushButton::clicked, this, &LoginDialog::on_findkeyButton_clicked);
    connect(shrinkButton, &QPushButton::clicked, this, &LoginDialog::on_shrinkButton_clicked);

    this->setMouseTracking(true);
    logoLabel->setMouseTracking(true);
    exitButton->setMouseTracking(true);
    minButton->setMouseTracking(true);
    clearuserButton->setMouseTracking(true);
    findkeyButton->setMouseTracking(true);

    beautify();
    //判断数据库是否存在
    QDir *temp = new QDir;
    bool exist = temp->exists("history.db");

    if(exist)
        ;
        //qDebug() << "exist";
    else
        newHistroy();

    //初始化输入框内容
    init_userCombo();
    init_keyEdit();
    //建立TCPSocket对象
    log = new QTcpSocket(this);
    con();
    ismousepressed = false;
}

QString LoginDialog::getUsername()
{
    return username;
}


//美化界面
void LoginDialog::beautify()
{
    //装饰，无边框
    this->resize(430, 330);

    //圆角
    setWindowFlags(Qt::FramelessWindowHint);
    QBitmap bmp(this->size());
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(), 3, 3);
    setMask(bmp);//设置窗体遮罩

    //背景颜色
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(235,242,249));
    this->setPalette(palette);

    //各种控件的装饰
    logoLabel->resize(430, 180);
    logoLabel->move(0, 0);
    QMovie *movie = new QMovie(":gif/resource_image/logbackground3.gif");
    logoLabel->setMovie(movie);
    movie->start();

    photoLabel->resize(80,80);
    photoLabel->move(40, 195);
    //photoLabel->setPixmap(QPixmap(":/image/resource_image/photo"));
    photoLabel->setStyleSheet("QLabel{border-image: url(:/image/resource_image/photo)}"
                              "QLabel{ border-radius: 5px;}"
                              );


    nameLabel->resize(260, 113);
    nameLabel->move(75, 35);
    nameLabel->setStyleSheet("QLabel{border-image: url(:/image/resource_image/dada.png)}");

    warnLabel->resize(30, 30);
    warnLabel->move(0, 330);
    warnLabel->setStyleSheet("QLabel{background-color:rgb(248, 243, 210)}"
                             "QLabel{background-image: url(:/qq/resource_image/comment_send_warn.png); background-repeat: repeat-none; background-position:center;}"
                             );

    tipsLabel->resize(430, 30);
    tipsLabel->move(30, 330);
    tipsLabel->setStyleSheet("QLabel{background-color:rgb(248, 243, 210)}"
                             "QLabel{font: 12px Microsoft YaHei;}");

    userCombo->resize(190, 30);
    userCombo->move(135, 195);
    userCombo->setEditable(true);
    userCombo->setStyleSheet("QComboBox{ border: 1px solid rgb(173,173,173);}"
                             "QComboBox{ border-radius: 3px;}"
                             "QComboBox QAbstractItemView::item{height:25px;}"
                             "QComboBox::down-arrow{image:url(:/qq/resource_image/arrow_normal);}"
                             "QComboBox::drop-down{border:0px;}"
                             "QComboBox::hover{border-color: rgb(9, 163, 220);}"
                             "QComboBox::down-arrow:hover{image:url(:/qq/resource_image/arrow_hover);}"
                             "QComboBox{font: 12px Microsoft YaHei;}"
                             );

    keyEdit->resize(190, 30);
    keyEdit->move(135, 225);
    keyEdit->setEchoMode(QLineEdit::Password);
    keyEdit->setStyleSheet("QLineEdit{ border: 1px solid rgb(173,173,173);}"
                           "QLineEdit{ border-radius: 3px;}"
                           "QLineEdit::hover{border-color: rgb(9, 163, 220);}");

    autologCheck->resize(100, 20);
    autologCheck->move(260, 260);
    autologCheck->setText("自动登录");
    autologCheck->setStyleSheet("QCheckBox::indicator:unchecked{image: url(:/qq/resource_image/checkbox_uncheck_normal.png);}"
                                "QCheckBox::indicator:unchecked:hover {image: url(:/qq/resource_image/checkbox_uncheck_hightlight.png)}"
                                "QCheckBox::indicator:unchecked:pressed {image: url(:/qq/resource_image/checkbox_uncheck_hightlight.png);}"
                                "QCheckBox::indicator:checked {image: url(:/qq/resource_image/checkbox_check_normal.png);}"
                                "QCheckBox::indicator:checked:hover {image: url(:/qq/resource_image/checkbox_check_hightlight.png);}"
                                "QCheckBox::indicator:checked:pressed {image: url(:/qq/resource_image/checkbox_check_hightlight.png);}"
                                "QCheckBox{font: 12px Microsoft YaHei;}"
                                "QCheckBox{color: gray;}"
                                );


    rememberCheck->resize(100,20);
    rememberCheck->move(135 ,260);
    rememberCheck->setText("记住密码");
    rememberCheck->setStyleSheet("QCheckBox::indicator:unchecked{image: url(:/qq/resource_image/checkbox_uncheck_normal.png);}"
                                 "QCheckBox::indicator:unchecked:hover {image: url(:/qq/resource_image/checkbox_uncheck_hightlight.png)}"
                                 "QCheckBox::indicator:unchecked:pressed {image: url(:/qq/resource_image/checkbox_uncheck_hightlight.png);}"
                                 "QCheckBox::indicator:checked {image: url(:/qq/resource_image/checkbox_check_normal.png);}"
                                 "QCheckBox::indicator:checked:hover {image: url(:/qq/resource_image/checkbox_check_hightlight.png);}"
                                 "QCheckBox::indicator:checked:pressed {image: url(:/qq/resource_image/checkbox_check_hightlight.png);}"
                                 "QCheckBox{font: 12px Microsoft YaHei;}"
                                 "QCheckBox{color: gray;}"
                                 );

    loginButton->resize(190, 30);
    loginButton->move(135, 290);
    loginButton->setText("登    录");
    loginButton->setFlat(true);
    loginButton->setStyleSheet("QPushButton{border:none;border-radius:3px;}"
                               "QPushButton{background:rgb(9, 163, 220);}"
                               "QPushButton:hover{background:rgb(60, 195, 245);}"
                               "QPushButton:pressed{background:rgb(9, 140, 188);}"
                               "QPushButton{font: 12px Microsoft YaHei;}"
                               "QPushButton{color: white;}"
                               );

    exitButton->resize(30, 30);
    exitButton->move(400, 0);
    exitButton->setStyleSheet("QPushButton{border:none;}"
                              "QPushButton{border-image: url(:/qq/resource_image/tips_close_n.png);background-repeat: repeat-none; background-position:center;}"
                              "QPushButton:hover{border-image: url(:/qq/resource_image/tips_close_h.png);background-repeat: repeat-none; background-position:center;}"
                              "QPushButton:pressed{border-image: url(:/qq/resource_image/tips_close_p.png);background-repeat: repeat-none; background-position:center;}"
                              );

    minButton->resize(30, 30);
    minButton->move(370, 0);
    minButton->setStyleSheet("QPushButton{border:none;}"
                             "QPushButton{border-image: url(:/qq/resource_image/btn_mini_normal.png);background-repeat: repeat-none; background-position:center;}"
                             "QPushButton:hover{border-image: url(:/qq/resource_image/btn_mini_down.png);background-repeat: repeat-none; background-position:center;}"
                             "QPushButton:pressed{border-image: url(:/qq/resource_image/btn_mini_down.png);background-repeat: repeat-none; background-position:center;}"
                             );

    clearuserButton->resize(50, 30);
    clearuserButton->move(335, 195);
    clearuserButton->setText("清空历史");
    clearuserButton->setStyleSheet("QPushButton{border:none;}"
                                 "QPushButton{background-color:transparent;}"
                                  "QPushButton{font: 12px Microsoft YaHei;}"
                                  "QPushButton{color: rgb(65,149,231);}"
                                  "QPushButton:hover{color:rgb(98,180,247);}"
                                  "QPushButton:pressed{color:rgb(63,145,196);}"
                                  );


    findkeyButton->resize(50, 30);
    findkeyButton->move(335, 225);
    findkeyButton->setText("找回密码");
    findkeyButton->setStyleSheet("QPushButton{border:none;}"
                                 "QPushButton{background-color:transparent;}"
                                  "QPushButton{font: 12px Microsoft YaHei;}"
                                  "QPushButton{color: rgb(65,149,231);}"
                                  "QPushButton:hover{color:rgb(98,180,247);}"
                                  "QPushButton:pressed{color:rgb(63,145,196);}"
                                  );

    shrinkButton->resize(30, 30);
    shrinkButton->move(400, 330);
    shrinkButton->setStyleSheet("QPushButton{border:none;}"
                             "QPushButton{background-color:rgb(248, 243, 210)}"
                             "QPushButton{background-image: url(:/qq/resource_image/nextbtn_normal.png); background-repeat: repeat-none; background-position:center;}"
                             "QPushButton:hover{background-image: url(:/qq/resource_image/nextbtn_highlight.png);background-repeat: repeat-none; background-position:center;}"
                             "QPushButton:pressed{background-image: url(:/qq/resource_image/nextbtn_highlight.png);background-repeat: repeat-none; background-position:center;}"
                             );

}

void LoginDialog::on_loginButton_clicked()
{
    QString id = userCombo->currentText();
    //qDebug()<<"id"<<id<<endl;
    QString pw = keyEdit->text();
    QString st = id + '_' + pw;
    QByteArray bt;
    bt.append(st);

    if (log == NULL)
    {
        con();
        //qDebug()<<"NULL"<<endl;
    }

    log->write(bt);

    if (!log->waitForReadyRead(300))
    {

    }
    bt = log->readAll();

    username = userCombo->currentText();
    int flag = rememberCheck->isChecked();
    int autoflag = autologCheck->isChecked();

    setRemember(flag);
    setKey(pw);
    setAuto(autoflag);
    addUser(username);

    if (bt == "lol")
    {
        //QMessageBox::information(this, tr("登录信息"),tr("成功！"));
        qDebug() << "lol";
        QDialog::accept();
        //qDebug()<<"accept";
    }
    else
    {
        //QMessageBox::information(this, tr("登录信息"),tr("失败！"));
        show_tips("用户名或密码错误");
        if(autologCheck->isChecked())
        {
            autologCheck->setChecked(false);
            setAuto(false);
        }
        qDebug() << "false";
    }

}

void LoginDialog::on_clearuserButton_clicked()
{
    clearUser();
    userCombo->clear();
    keyEdit->clear();
}

void LoginDialog::on_findkeyButton_clicked()
{
    show_tips("傻孩子，密码是net2014呀~");
}


void LoginDialog::init_userCombo()
{
    int num_of_users = getUsernum();
    //qDebug()<<"user"<<num_of_users;
    for(int i = 0; i < num_of_users; i++)
    {
        //qDebug()<<"jinrule";
        QString studentnum = getUser(i + 1);
        userCombo->addItem(studentnum);
    }
}

void LoginDialog::init_keyEdit()
{
    int autoflag = getAuto();
    if(autoflag == 1)   //自动登录
    {
        autologCheck->setChecked(true);
        QString key = getKey();
        keyEdit->setText(key);
    }
    else
    {
        autologCheck->setChecked(false);
    }

    int flag = getRemember();
    if(flag == 1)//上次勾选了"记住密码"
    {
        rememberCheck->setChecked(true);
        QString key = getKey();
        keyEdit->setText(key);
    }
    else
    {
        rememberCheck->setChecked(false);
    }
}

void LoginDialog::con()
{
    if (log != NULL)
    {
        delete log;
        log = NULL;
    }
    log = new QTcpSocket(this);
    log->connectToHost("166.111.180.60", 8000);
}

void LoginDialog::mouseMoveEvent(QMouseEvent *e)
{
    QPoint pos = e->pos();
    if(inButton(clearuserButton, pos) || (inButton(findkeyButton, pos)))
    {
        setCursor(Qt::PointingHandCursor);
    }
    else
        setCursor(Qt::ArrowCursor);

    if (e->buttons() == Qt::LeftButton)
        move(e->globalPos() - dPos);
    judgeAuto();

}

void LoginDialog::mousePressEvent(QMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::LeftButton)
        dPos = mouseEvent->pos();
}


bool LoginDialog::inButton(QPushButton *push, QPoint p)
{
    int height = push->height();
    int width = push->width();
    QPoint left_up = push->pos();
    QPoint right_down;
    right_down.setX(push->pos().x() + width);
    right_down.setY(push->pos().y() + height);
    if((p.x() >= left_up.x()) && (p.x() <= right_down.x()) && (p.y() >= left_up.y()) && (p.y() <= right_down.y()))
        return true;
    else
        return false;
}

void LoginDialog::judgeAuto()
{
    if(getAuto() == 1)
    {
        on_loginButton_clicked();
    }
}


void LoginDialog::show_tips(QString message)
{
    qDebug()<<"tip";
    this->resize(430, 360);
    //圆角
    QBitmap bmp(this->size());
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(), 3, 3);
    setMask(bmp);//设置窗体遮罩
    tipsLabel->setText(message);

}

void LoginDialog::on_shrinkButton_clicked()
{
    this->resize(430, 330);
    //圆角
    QBitmap bmp(this->size());
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(), 3, 3);
    setMask(bmp);//设置窗体遮罩
}
