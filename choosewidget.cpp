#include "choosewidget.h"
#include <QMessageBox>
#include <QDebug>
#include <QtNetwork>
#include "chatdialog.h"

ChooseWidget::ChooseWidget(QWidget *parent) :
    QWidget(parent)
{

}

ChooseWidget::ChooseWidget(QString name, QWidget *parent) :
    QWidget(parent)
{
    username = name;
    chats = new HeadButton("icon_last", this);
    friends = new HeadButton("icon_contacts", this);
    groups = new HeadButton("icon_group", this);
    zone = new HeadButton("qzone", this);
    mobile = new HeadButton("main_panel_tab_inco", this);
    choice = new QButtonGroup(this);
    friendstree = new QTreeWidget(this);
    friendstree->setContextMenuPolicy(Qt::CustomContextMenu);

    deletefriendAction = new QAction(tr("删除好友"), this);
    deletegroupAction = new QAction(tr("删除分组"), this);
    connect(deletefriendAction, &QAction::triggered, this, &ChooseWidget::delete_friend);
    connect(deletegroupAction, &QAction::triggered, this, &ChooseWidget::delete_group);

    connect(chats, &HeadButton::clicked, this, &ChooseWidget::x_chosen);
    connect(friends, &HeadButton::clicked, this, &ChooseWidget::x_chosen);
    connect(groups, &HeadButton::clicked, this, &ChooseWidget::x_chosen);
    connect(zone, &HeadButton::clicked, this, &ChooseWidget::x_chosen);
    connect(mobile, &HeadButton::clicked, this, &ChooseWidget::x_chosen);
    connect(friendstree, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(double_clicked(QTreeWidgetItem*,int)));
    connect(friendstree, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(clicked(QTreeWidgetItem*,int)));
    connect(friendstree, &QTreeWidget::customContextMenuRequested, this, &ChooseWidget::show_deletefriend_menu);

    init();
    init_friends();
}


void ChooseWidget::init()
{
    this->resize(300, 530);
    chats->move(0, 0);
    friends->move(60, 0);
    groups->move(120, 0);
    zone->move(180, 0);
    mobile->move(240, 0);
    choice->addButton(chats, 0);
    choice->addButton(friends, 1);
    choice->addButton(groups, 2);
    choice->addButton(zone, 3);
    choice->addButton(mobile, 4);

    friendstree->move(0, 30);
    friendstree->resize(300, 500);
    friendstree->setHeaderHidden(true);
    friendstree->setFrameStyle(QFrame::NoFrame);
    friendstree->setStyleSheet("QTreeWidget::branch:has-children:!has-siblings:closed, QTreeWidget::branch:closed:has-children:has-siblings {border-image: none; image: url(:/qq/resource_image/MainPanel_FolderNode_collapseTexture.png);}"
                              "QTreeWidget::branch:hover:has-children:!has-siblings:closed, QTreeWidget::branch:hover:closed:has-children:has-siblings::hover {border-image: none; image: url(:/qq/resource_image/MainPanel_FolderNode_collapseTextureHighlight.png);}"
                               "QTreeWidget::branch:has-children:!has-siblings:open, QTreeWidget::branch:open:has-children:has-siblings {border-image: none; image: url(:/qq/resource_image/MainPanel_FolderNode_expandTexture.png);}"
                               "QTreeWidget::branch:hover:has-children:!has-siblings:open, QTreeWidget::branch:hover:open:has-children:has-siblings::hover {border-image: none; image: url(:/qq/resource_image/MainPanel_FolderNode_expandTextureHighlight.png);}"
                               );
}

void ChooseWidget::init_friends()
{
    qDebug()<<"init_friends"<<username;
    num_of_friends = getFriendsnum(username);
    num_of_groups = getGroupsnum(username);
    roots.resize(num_of_groups);
    rootscontent.resize(num_of_groups);
    childs.resize(num_of_friends);
    childscontent.resize(num_of_friends);
    for(int i = 0; i < num_of_groups; i++)
    {
        groupinfo gi = getGroupinfo(username, i + 1);
        rootscontent[i] = new GroupWidget(gi.id, gi.name, gi.friendsingroup, gi.expand, this);
        roots[i] = new QTreeWidgetItem(friendstree);
        roots[i]->setSizeHint(0, QSize(200, 20));
        friendstree->setItemWidget(roots[i], 0, rootscontent[i]);
    }

    for(int i = 0; i < num_of_friends; i++)
    {
        friendinfo fi = getFriendinfo(username, i + 1);
        QString photofile = "./" + username + "/friendsphoto/" + fi.photo;
        childscontent[i] = new FriendWidget(fi.id, fi.belongto, fi.studentnum, QPixmap(photofile), fi.name, fi.sign, fi.big, this);
        if(isOnline(fi) == 0)
            childscontent[i]->offline();
        else
            childscontent[i]->online();
        childs[i] = new QTreeWidgetItem(roots[fi.belongto - 1]);
        childs[i]->setSizeHint(0, QSize(200, 30));
        friendstree->setItemWidget(childs[i], 0, childscontent[i]);
    }

    for(int i = 0; i < num_of_groups; i++)
    {
        if(rootscontent[i]->expand == 1)
        {
            roots[i]->setExpanded(false);
            roots[i]->setExpanded(true);
        }
        else
        {
            roots[i]->setExpanded(true);
            roots[i]->setExpanded(false);
        }
    }

    for(int i = 0; i < num_of_friends; i++)
    {
        if(childscontent[i]->isBig() == 1)
        {
            childscontent[i]->choose();
            childs[i]->setSizeHint(0, childscontent[i]->size());
        }
        else
        {
            childscontent[i]->cancel_choose();
            childs[i]->setSizeHint(0, childscontent[i]->size());
        }
    }

    for(int i = 0; i < num_of_groups; i++)
    {
        bool state = roots[i]->isExpanded();
        if(state == true)
        {
            roots[i]->setExpanded(false);
            roots[i]->setExpanded(true);
        }
    }
}

void ChooseWidget::x_chosen()
{
    int id = choice->checkedId();
    if(choice->button(id)->isChecked() == false)
        choice->button(id)->setChecked(true);
    for(int i = 0; ((i < 5) && (i != id)); i++)
        choice->button(i)->setChecked(false);
    refresh();
}


void ChooseWidget::refresh()
{
    int id = choice->checkedId();
    switch (id)
    {
    case 0:
        friendstree->setVisible(false);
        break;
    case 1:
        friendstree->setVisible(true);
        break;
    case 2:
        friendstree->setVisible(false);
        break;
    case 3:
        friendstree->setVisible(false);
        break;
    case 4:
        friendstree->setVisible(false);
        break;
    }
    qDebug()<< "in chooseWidget::refresh() " << choice->checkedId();
}

void ChooseWidget::refresh_friends()
{
    qDebug()<<"refresh";
    for(int i = 0; i < childs.size(); i++)
    {
        //qDebug()<<i;
        delete childs[i];
        childs[i] = NULL;
    }
    childs.clear();

    for(int i = 0; i < childscontent.size(); i++)
    {
        //qDebug()<<i;
        delete childscontent[i];
        childscontent[i] = NULL;
    }
    childscontent.clear();

    for(int i = 0; i < roots.size(); i++)
    {
        //qDebug()<<i;
        delete roots[i];
        roots[i] = NULL;
    }
    roots.clear();

    for(int i = 0; i < roots.size(); i++)
    {
        //qDebug()<<i;
        delete rootscontent[i];
        rootscontent[i] = NULL;
    }
    rootscontent.clear();

    init_friends();
}

void ChooseWidget::clicked(QTreeWidgetItem *item, int column)
{
    QTreeWidgetItem *parent = item->parent();
    if(NULL==parent)
        return;
   qDebug() << "clicked";
   for(int i = 0; i < num_of_friends; i++)
   {
       childscontent[i]->cancel_choose();
       childscontent[i]->setBig(0);
       childs[i]->setSizeHint(0, childscontent[i]->size());
   }
   FriendWidget* f = (FriendWidget*)friendstree->itemWidget(item, column);
   f->choose();
   f->setBig(1);
   item->setSizeHint(0, f->size());

   for(int i = 0; i < num_of_groups; i++)
   {
       bool state = roots[i]->isExpanded();
       if(state == true)
       {
           roots[i]->setExpanded(false);
           roots[i]->setExpanded(true);
       }
   }
}

void ChooseWidget::double_clicked(QTreeWidgetItem *item, int column)
{
    QTreeWidgetItem *parent = item->parent();
    if(NULL==parent)
    {
        if(item->isExpanded() == false)
        {
            for(int i = 0; i < num_of_friends; i++)
            {
                if(childs[i]->parent() == item)
                childscontent[i]->cancel_choose();
                childs[i]->setSizeHint(0, childscontent[i]->size());
            }
        }
        return;
    }
    //QMessageBox::information(this, "check it out!", QString(column));
    FriendWidget* f = (FriendWidget*)friendstree->itemWidget(item, column);
    QTcpSocket* check = new QTcpSocket(this);
    check->connectToHost("166.111.180.60", 8000);
    QString st = "q" + f->id;
    QByteArray bt;
    bt.append(st);
    check->write(bt);
    if (!check->waitForReadyRead(300))
    {

    }
    bt = check->readAll();
    if (bt == "n")
    {
        QMessageBox::information(this, tr("登录信息"), tr("查无此人！"));
    }
    else
    {
        ChatDialog* chat = new ChatDialog(f->studentnum);
        chat->show();
        connect(chat, SIGNAL(send_msg(QString,QString)), this, SLOT(from_down_msg(QString, QString)));
        connect(this, SIGNAL(to_down_msg(QString,QString)), chat, SLOT(rec_msg(QString,QString)));
        emit(new_conn(f->studentnum, QString(bt)));
    }
}

void ChooseWidget::from_up_msg(QString id, QString msg)
{
    emit to_down_msg(id, msg);
}

void ChooseWidget::from_down_msg(QString id, QString msg)
{
    emit to_up_msg(id, msg);
}

void ChooseWidget::show_deletefriend_menu(QPoint pos)
{
    QTreeWidgetItem* curItem=friendstree->itemAt(pos);  //获取当前被点击的节点

    if(curItem==NULL)
        return;           //这种情况是右键的位置不在treeItem的范围内，即在空白位置右击
    QTreeWidgetItem *parent = curItem->parent();
    QMenu *menu=new QMenu(this);
    if(NULL==parent)        //右键是父节点
    {
        GroupWidget *g = (GroupWidget*)friendstree->itemWidget(curItem, 0);
        qDebug()<<g->id;
        group_to_delete = g->id;
        if(group_to_delete == 1)
            return;
        menu->addAction(deletegroupAction); //添加菜单项1
    }
    else
    {
        FriendWidget *f = (FriendWidget*)friendstree->itemWidget(curItem, 0);
        qDebug()<<f->id;
        friend_to_delete = f->id;
        menu->addAction(deletefriendAction); //添加菜单项1
    }
    QCursor cur=this->cursor();
    menu->exec(cur.pos()); //关联到光标
}


void ChooseWidget::delete_friend()
{
    set_group_expand();
    set_friend_big();
    qDebug()<<"deletefriend";
    deleteFriend(username, friend_to_delete);

    refresh_friends();
}

void ChooseWidget::delete_group()
{
    set_group_expand();
    set_friend_big();
    qDebug()<<"deletegroup";
    deleteGroup(username, group_to_delete);
    refresh_friends();
}

void ChooseWidget::set_group_expand()
{
    for(int i = 0; i < num_of_groups; i++)
    {
        if(roots[i]->isExpanded() == true)
            setGroupexpand(username, i + 1, 1);
        else
            setGroupexpand(username, i + 1, 0);
    }
}

void ChooseWidget::set_friend_big()
{
    for(int i = 0; i < num_of_friends; i++)
    {
        if(childscontent[i]->big == 1)
            setFriendbig(username, i + 1, 1);
        else
            setFriendbig(username, i + 1, 0);
    }
}

int ChooseWidget::isOnline(friendinfo f)
{
    QTcpSocket* check = new QTcpSocket(this);
    check->connectToHost("166.111.180.60", 8000);
    QString st = "q" + f.studentnum;
    QByteArray bt;
    bt.append(st);
    qDebug()<<"st"<<st;
    check->write(bt);
    if (!check->waitForReadyRead(300))
    {

    }
    bt = check->readAll();
    qDebug()<<"bt"<<bt;
    if (bt == "n")
    {
        //QMessageBox::information(this, tr("登录信息"), tr("查无此人！"));
        qDebug()<<"offline" << f.studentnum;
        return 0;
    }
    else
    {
        qDebug()<<"online" << f.studentnum;
        return 1;
    }
}
