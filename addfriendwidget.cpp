#include "addfriendwidget.h"

AddfriendWidget::AddfriendWidget(QWidget *parent) :
    QWidget(parent)
{
}

AddfriendWidget::AddfriendWidget(QString name, QWidget *parent) :
    QWidget(parent)
{
    //nameLabel = new QLabel(this);
    //studentnumLabel = new QLabel(this);
    //groupLabel = new QLabel(this);
    //signLabel = new QLabel(this);
    blueLabel = new QLabel(this);
    logoLabel = new QLabel(this);
    textLabel = new QLabel(this);
    nameEdit = new QLineEdit(this);
    signEdit = new QLineEdit(this);
    studentnumEdit = new QLineEdit(this);
    groupBox = new QComboBox(this);
    photoBox = new QComboBox(this);
    configButton = new QPushButton(this);
    cancelButton = new QPushButton(this);
    exitButton = new QPushButton(this);
    minButton = new QPushButton(this);
    findpeopleButton = new QPushButton(this);
    findgroupchatButton = new QPushButton(this);
    photos.resize(20);
    photoGroup = new QButtonGroup(this);
    for(int i = 0; i < 20; i++)
    {
        photos[i] = new QPushButton(this);
        photos[i]->setCheckable(true);
        photoGroup->addButton(photos[i], i);
    }

    this->setMouseTracking(true);
    findpeopleButton->setCheckable(true);
    findgroupchatButton->setCheckable(true);

    username = name;

    connect(configButton, &QPushButton::clicked, this, &AddfriendWidget::emit_signal_infosend);
    connect(exitButton, &QPushButton::clicked, this, &AddfriendWidget::close);
    connect(minButton, &QPushButton::clicked, this, &AddfriendWidget::showMinimized);
    connect(findpeopleButton, &QPushButton::clicked, this, &AddfriendWidget::on_findpeopleButton_clicked);
    connect(findgroupchatButton, &QPushButton::clicked, this, &AddfriendWidget::on_findgroupchatButton_clicked);
    connect(cancelButton, &QPushButton::clicked, this, &AddfriendWidget::close);
    for(int i = 0; i < 20; i++)
        connect(photos[i], &QPushButton::clicked, this, &AddfriendWidget::choose_photo_x);
    init();
}

void AddfriendWidget::init()
{
    this->resize(600, 500);
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
    exitButton->resize(25, 25);
    exitButton->move(575, 0);
    exitButton->setStyleSheet("QPushButton{border:none;}"
                              "QPushButton{border-image: url(:/qq/resource_image/tips_close_n.png);background-repeat: repeat-none; background-position:center;}"
                              "QPushButton:hover{border-image: url(:/qq/resource_image/tips_close_h.png);background-repeat: repeat-none; background-position:center;}"
                              "QPushButton:pressed{border-image: url(:/qq/resource_image/tips_close_p.png);background-repeat: repeat-none; background-position:center;}"
                              );

    minButton->resize(25, 25);
    minButton->move(550, 0);
    minButton->setStyleSheet("QPushButton{border:none;}"
                             "QPushButton{border-image: url(:/qq/resource_image/btn_mini_normal.png);background-repeat: repeat-none; background-position:center;}"
                             "QPushButton:hover{border-image: url(:/qq/resource_image/btn_mini_down.png);background-repeat: repeat-none; background-position:center;}"
                             "QPushButton:pressed{border-image: url(:/qq/resource_image/btn_mini_down.png);background-repeat: repeat-none; background-position:center;}"
                             );

    findpeopleButton->resize(100, 40);
    findpeopleButton->move(200, 20);
    findpeopleButton->setText("找人");
    findpeopleButton->setStyleSheet("QPushButton{border:none;}"
                                    "QPushButton{background-color :transparent}"
                                    "QPushButton{font: 18px Microsoft YaHei;}"
                                    "QPushButton{color: rgb(223, 235, 249);}"
                                    "QPushButton:checked{color:rgb(223, 235, 249); font: bold}"
                                    );

    findgroupchatButton->resize(100, 40);
    findgroupchatButton->move(300, 20);
    findgroupchatButton->setText("找群");
    findgroupchatButton->setStyleSheet("QPushButton{border:none;}"
                                    "QPushButton{background-color :transparent}"
                                    "QPushButton{font: 18px Microsoft YaHei;}"
                                    "QPushButton{color: rgb(223, 235, 249);}"
                                    "QPushButton:checked{color:rgb(223, 235, 249); font: bold}"
                                    );
    int x_start = 50;
    int y_start = 280;
    for(int i = 0; i < 20; i++)
    {
        photos[i]->resize(40, 40);

         photos[i]->setStyleSheet("QPushButton{border:none;}"
                                  "QPushButton{ border-radius: 3px;}"
                                 "QPushButton{background-color :transparent}"
                                  "QPushButton{background-image: url(:/photo/resource_image/" + QString::number(i + 1, 10) + ".png)}"
                                 "QPushButton:hover{border: 2px solid rgb(174, 207, 230)}"
                                  "QPushButton:checked{border: 2px solid rgb(174, 207, 230)}"
                             );

        int x = i % 10;
        int y = i / 10;
        photos[i]->move(x_start + x * 50 + 5, y_start + y * 50 + 5);
    }

    blueLabel->resize(600, 60);
    blueLabel->move(0, 0);
    blueLabel->setStyleSheet("QLabel{background-color:rgb(39, 140, 222)}");

    logoLabel->resize(30, 30);
    logoLabel->move(0, 0);
    logoLabel->setStyleSheet("QLabel{background-image: url(:/qq/resource_image/QQlogo.png); background-repeat: repeat-none; background-position:center;}");

    textLabel->move(30, 0);
    textLabel->resize(50, 30);
    textLabel->setText("查找");
    textLabel->setStyleSheet("QLabel{font: 12px Microsoft YaHei;}"
                             "QLabel{color: white;}"

                             );
/*
    studentnumLabel->setText("学号");
    studentnumLabel->move(50, 50);

    nameLabel->setText("备注名");
    nameLabel->move(50, 100);

    groupLabel->setText("好友分组");
    groupLabel->move(50, 150);

    signLabel->setText("备注");
    signLabel->move(50, 200);
*/
    studentnumEdit->resize(225, 30);
    studentnumEdit->move(50, 100);
    studentnumEdit->setPlaceholderText(QString("学号")); //qt5
    studentnumEdit->setStyleSheet("QLineEdit{ border: 1px solid rgb(173,173,173);}"
                                  "QLineEdit{ border-radius: 3px;}"
                                  "QLineEdit::hover{border-color: rgb(9, 163, 220);}"
                                  );

    nameEdit->resize(225, 30);
    nameEdit->move(325, 100);
    nameEdit->setPlaceholderText(QString("备注名"));
    nameEdit->setStyleSheet("QLineEdit{ border: 1px solid rgb(173,173,173);}"
                                  "QLineEdit{ border-radius: 3px;}"
                                  "QLineEdit::hover{border-color: rgb(9, 163, 220);}"
                                  );


    signEdit->resize(500, 30);
    signEdit->move(50, 160);
    signEdit->setPlaceholderText(QString("给他一个评价吧"));
    signEdit->setStyleSheet("QLineEdit{ border: 1px solid rgb(173,173,173);}"
                                  "QLineEdit{ border-radius: 3px;}"
                                  "QLineEdit::hover{border-color: rgb(9, 163, 220);}"
                                  );

    groupBox->resize(225, 30);
    groupBox->move(50, 220);
    groupBox->setStyleSheet("QComboBox{ border: 1px solid rgb(173,173,173);}"
                                 "QComboBox{ border-radius: 3px;}"
                                 "QComboBox QAbstractItemView::item{height:25px;}"
                                 "QComboBox::down-arrow{image:url(:/qq/resource_image/arrow_normal);}"
                                 "QComboBox::drop-down{border:0px;}"
                                 "QComboBox::hover{border-color: rgb(9, 163, 220);}"
                                 "QComboBox::down-arrow:hover{image:url(:/qq/resource_image/arrow_hover);}"
                                 "QComboBox{font: 12px Microsoft YaHei;}"
                                 );
    //groupBox->setPlaceholderText(QString("分组"));
    int num_of_groups = getGroupsnum(username);
    for(int i = 0; i < num_of_groups; i++)
    {
        groupinfo gi = getGroupinfo(username, i + 1);
        groupBox->insertItem(i, gi.name);
    }

    photoBox->resize(225, 30);
    photoBox->move(325, 220);
    photoBox->setStyleSheet("QComboBox{ border: 1px solid rgb(173,173,173);}"
                                 "QComboBox{ border-radius: 3px;}"
                                 "QComboBox QAbstractItemView::item{height:25px;}"
                                 "QComboBox::down-arrow{image:url(:/qq/resource_image/arrow_normal);}"
                                 "QComboBox::drop-down{border:0px;}"
                                 "QComboBox::hover{border-color: rgb(9, 163, 220);}"
                                 "QComboBox::down-arrow:hover{image:url(:/qq/resource_image/arrow_hover);}"
                                 "QComboBox{font: 12px Microsoft YaHei;}"
                                 );
    //photoBox->setPlaceholderText(QString("头像"));
    for(int i = 0; i < 3; i++)
    {
        QString photopath = ":/photo/resource_image/" + QString::number(i + 1, 10);
        QString photoname = "系统头像" + QString::number(i + 1, 10);
        photoBox->addItem(QIcon(photopath), photoname);
    }

    configButton->resize(225, 30);
    configButton->move(50, 410);
    configButton->setText("添  加  好  友");
    configButton->setFlat(true);
    configButton->setStyleSheet("QPushButton{border:none;border-radius:3px;}"
                                "QPushButton{background:rgb(9, 163, 220);}"
                                "QPushButton:hover{background:rgb(60, 195, 245);}"
                                "QPushButton:pressed{background:rgb(9, 140, 188);}"
                                "QPushButton{font: 12px Microsoft YaHei;}"
                                "QPushButton{color: white;}"
                                );

    cancelButton->resize(225, 30);
    cancelButton->move(325, 410);
    cancelButton->setText("取     消");
    cancelButton->setFlat(true);
    cancelButton->setStyleSheet("QPushButton{border:none;border-radius:3px;}"
                                "QPushButton{background:rgb(9, 163, 220);}"
                                "QPushButton:hover{background:rgb(60, 195, 245);}"
                                "QPushButton:pressed{background:rgb(9, 140, 188);}"
                                "QPushButton{font: 12px Microsoft YaHei;}"
                                "QPushButton{color: white;}"
                                );
}

void AddfriendWidget::emit_signal_infosend()
{
    friendinfo fi;
    fi.id = getFriendsnum(username) + 1;
    fi.name = nameEdit->text();
    fi.studentnum = studentnumEdit->text();
    fi.belongto = groupBox->currentIndex() + 1;
    fi.photo = QString::number(photoGroup->checkedId() + 1, 10);
    //qDebug() << fi.photo;
    fi.sign = signEdit->text();
    fi.big = 0;
    int exist = existFriend(username, fi);
    if(exist == 1)
        QMessageBox::information(this, tr("登录信息"),tr("好友已存在"));
    else
    {
        newFriend(username, fi);
        emit infoSend(fi);
    }

    close();
}

void AddfriendWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons() == Qt::LeftButton)
        move(e->globalPos() - dPos);

}

void AddfriendWidget::mousePressEvent(QMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() == Qt::LeftButton)
        dPos = mouseEvent->pos();
}

void AddfriendWidget::on_findpeopleButton_clicked()
{
    findgroupchatButton->setChecked(false);
    nameEdit->setVisible(true);
    studentnumEdit->setVisible(true);
    signEdit->setVisible(true);
    groupBox->setVisible(true);
    photoBox->setVisible(true);
    configButton->setVisible(true);
    cancelButton->setVisible(true);

}

void AddfriendWidget::on_findgroupchatButton_clicked()
{
    findpeopleButton->setChecked(false);
    nameEdit->setVisible(false);
    studentnumEdit->setVisible(false);
    signEdit->setVisible(false);
    groupBox->setVisible(false);
    photoBox->setVisible(false);
    configButton->setVisible(false);
    cancelButton->setVisible(false);
}

void AddfriendWidget::choose_photo_x()
{
    int button_check = photoGroup->checkedId();
    if(photos[button_check]->isChecked() == false)
       photos[button_check]->setChecked(true);
    for(int i = 0; ((i < 20) && (i != button_check)); i++)
    {
        photos[i]->setChecked(false);
    }
}

