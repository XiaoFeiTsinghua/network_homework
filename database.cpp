#include "database.h"

void newHistroy()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");    //添加数据库驱动

    db.setDatabaseName("history.db");  //在工程目录新建一个mytest.db的文件
    if(!db.open())
    {
        qDebug()<<"cannot open database";
    }
    QSqlQuery query;//以下执行相关QSL语句
    query.exec("create table loghistory(id varchar, studentnum varchar)");
    query.exec("create table remember(id varchar, checked varvhar)");
    query.exec("insert into remember values(1, 0)");
    query.exec("insert into remember values(2, 0)");
    query.exec("create table auto(id varchar, checked varvhar)");
    query.exec("insert into auto values(1, 0)");

}

int getRemember()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");    //添加数据库驱动

    db.setDatabaseName("history.db");  //在工程目录新建一个mytest.db的文件
    if(!db.open())
    {
        qDebug()<<"cannot open database";
    }
    QSqlQuery query;//以下执行相关QSL语句
    query.exec("select checked from remember where id == 1");
    query.next();
    int remember = query.value(0).toInt();
    qDebug()<<remember;
    return remember;
}

QString getKey()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");    //添加数据库驱动

    db.setDatabaseName("history.db");  //在工程目录新建一个mytest.db的文件
    if(!db.open())
    {
        qDebug()<<"cannot open database";
    }
    QSqlQuery query;//以下执行相关QSL语句
    query.exec("select checked from remember where id == 2");
    query.next();
    QString key = query.value(0).toString();
    qDebug()<<key;
    return key;
}

int getAuto()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");    //添加数据库驱动

    db.setDatabaseName("history.db");  //在工程目录新建一个mytest.db的文件
    if(!db.open())
    {
        qDebug()<<"cannot open database";
    }
    QSqlQuery query;//以下执行相关QSL语句
    query.exec("select checked from auto where id == 1");
    query.next();
    int autopass = query.value(0).toInt();
    qDebug()<<autopass;
    return autopass;
}

void setRemember(int flag)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");    //添加数据库驱动

    db.setDatabaseName("history.db");  //在工程目录新建一个mytest.db的文件
    if(!db.open())
    {
        qDebug()<<"cannot open database";
    }
    QSqlQuery query;//以下执行相关QSL语句
    query.exec("update remember set checked = " + QString::number(flag, 10) + " where id = 1");
}

void setKey(QString key)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");    //添加数据库驱动

    db.setDatabaseName("history.db");  //在工程目录新建一个mytest.db的文件
    if(!db.open())
    {
        qDebug()<<"cannot open database";
    }
    QSqlQuery query;//以下执行相关QSL语句
    query.exec("update remember set checked = '" + key + "' where id = 2");
}

void setAuto(int flag)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");    //添加数据库驱动

    db.setDatabaseName("history.db");  //在工程目录新建一个mytest.db的文件
    if(!db.open())
    {
        qDebug()<<"cannot open database";
    }
    QSqlQuery query;//以下执行相关QSL语句
    query.exec("update auto set checked = " + QString::number(flag, 10) + " where id = 1");
}

void addUser(QString username)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");    //添加数据库驱动

    db.setDatabaseName("history.db");  //在工程目录新建一个mytest.db的文件
    if(!db.open())
    {
        qDebug()<<"cannot open database";
    }
    QSqlQuery query;//以下执行相关QSL语句
    query.exec("select id from loghistory where studentnum == " + username);
    int flag = query.next();
    if(flag == false)
    {
        query.exec("select id from loghistory where id >= 1");
        query.last();
        int temp = query.value(0).toInt();
        temp++;
        query.exec("insert into loghistory values(" + QString::number(temp, 10) + ", '" + username + "')");
        //qDebug()<<"insert into loghistory values(" + QString::number(temp, 10) + ", '" + username + "')";
    }
}

void clearUser()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");    //添加数据库驱动

    db.setDatabaseName("history.db");  //在工程目录新建一个mytest.db的文件
    if(!db.open())
    {
        qDebug()<<"cannot open database";
    }
    QSqlQuery query;//以下执行相关QSL语句
    query.exec("delete from loghistory where id >= 1");
}

int getUsernum()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");    //添加数据库驱动

    db.setDatabaseName("history.db");  //在工程目录新建一个mytest.db的文件
    if(!db.open())
    {
        qDebug()<<"cannot open database";
    }
    QSqlQuery query;//以下执行相关QSL语句
    query.exec("select id from loghistory where id >= 1");
    query.last();
    int usernum = query.value(0).toInt();
    //qDebug()<< "usernum" << usernum;
    return usernum;
}

QString getUser(int id)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");    //添加数据库驱动

    db.setDatabaseName("history.db");  //在工程目录新建一个mytest.db的文件
    if(!db.open())
    {
        qDebug()<<"cannot open database";
    }
    QSqlQuery query;//以下执行相关QSL语句
    query.exec("select studentnum from loghistory where id == " + QString::number(id, 10));
    qDebug()<<"select studentnum from loghistory where id == " + QString::number(id, 10);
    query.next();
    QString studentnum;
    studentnum = query.value(0).toString();
    qDebug()<<studentnum;
    return studentnum;
}

void newDatabase(QString username)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");    //添加数据库驱动

    db.setDatabaseName("./" + username + "/" + username + ".db");  //在工程目录新建一个mytest.db的文件
    if(!db.open())
    {
        qDebug()<<"cannot open database";
    }

    QSqlQuery query;//以下执行相关QSL语句
    query.exec("create table baseinfo(id varchar, name varchar, count varchar)");
    query.exec(QObject::tr("insert into baseinfo values(1,'好友分组数',1)"));
    query.exec(QObject::tr("insert into baseinfo values(2,'好友数',0)"));
    query.exec("create table friendsgroup(id varchar, name varchar, friendsingroup varchar, expand varchar)");
    query.exec("insert into friendsgroup values(1, '默认分组', 0, 0)");
    query.exec("create table friends(id varchar, belongto varchar, studentnum varchar, name varchar, photo varchar, sign varchar, big varchar)");

}

int getFriendsnum(QString username)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");    //添加数据库驱动

    db.setDatabaseName("./" + username + "/" + username + ".db");  //在工程目录新建一个mytest.db的文件
    if(!db.open())
    {
        qDebug()<<"cannot open database";
    }
    QSqlQuery query;//以下执行相关QSL语句
    query.exec("select id, name, count from baseinfo where id == 2");
    query.next();
    int friendsnum = query.value(2).toInt();
    return friendsnum;
}

int getGroupsnum(QString username)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");    //添加数据库驱动

    db.setDatabaseName("./" + username + "/" + username + ".db");  //在工程目录新建一个mytest.db的文件
    if(!db.open())
    {
        qDebug()<<"cannot open database";
    }
    QSqlQuery query;//以下执行相关QSL语句
    query.exec("select id, name, count from baseinfo where id == 1");
    query.next();
    int groupsnum = query.value(2).toInt();
    return groupsnum;
}


groupinfo getGroupinfo(QString username, int id)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");    //添加数据库驱动

    db.setDatabaseName("./" + username + "/" + username + ".db");
    if(!db.open())
    {
        qDebug()<<"cannot open database";
    }
    QSqlQuery query;//以下执行相关QSL语句
    query.exec("select id, name, friendsingroup, expand from friendsgroup where id == " + QString("%1").arg(id));
    query.next();
    groupinfo sth;
    sth.id = query.value(0).toInt();
    sth.name = query.value(1).toString();
    sth.friendsingroup = query.value(2).toInt();
    sth.expand = query.value(3).toInt();
    return sth;
}

friendinfo getFriendinfo(QString username, int id)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");    //添加数据库驱动

    db.setDatabaseName("./" + username + "/" + username + ".db");
    if(!db.open())
    {
        qDebug()<<"cannot open database";
    }
    QSqlQuery query;//以下执行相关QSL语句
    query.exec("select id, belongto, studentnum, name, photo, sign, big from friends where id == " + QString("%1").arg(id));
    query.next();
    friendinfo sb;
    sb.id = query.value(0).toInt();
    sb.belongto = query.value(1).toInt();
    sb.studentnum = query.value(2).toString();
    sb.name = query.value(3).toString();
    sb.photo = query.value(4).toString();
    sb.sign = query.value(5).toString();
    sb.big = query.value(6).toInt();
    qDebug() << sb.id;    qDebug() << sb.belongto;    qDebug() << sb.studentnum;    qDebug() << sb.name;    qDebug() << sb.photo;    qDebug() << sb.sign; qDebug()<<sb.big;
    return sb;
}

void newGroup(QString username, groupinfo newgi)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");    //添加数据库驱动
    qDebug()<<newgi.name;
    db.setDatabaseName("./" + username + "/" + username + ".db");
    if(!db.open())
    {
        qDebug()<<"cannot open database";
    }

    int temp = getGroupsnum(username);
    temp++;

    QSqlQuery query;//以下执行相关QSL语句
    query.exec("update baseinfo set count = " + QString::number(temp, 10) + " where id = 1");
    query.exec("insert into friendsgroup values(" + QString::number(newgi.id, 10) + ",'" + newgi.name + "'," + QString::number(newgi.friendsingroup, 10) + "," + QString::number(newgi.expand, 10) + ")");
    //qDebug()<<"insert into friendsgroup values(" + QString::number(newgi.id, 10) + ",'" + newgi.name + "'," + QString::number(newgi.friendsingroup, 10) + "," + QString::number(newgi.expand, 10) + ")";
}
int existFriend(QString username, friendinfo newfi)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");    //添加数据库驱动
    db.setDatabaseName("./" + username + "/" + username + ".db");
    if(!db.open())
    {
        qDebug()<<"cannot open database";
    }

    QSqlQuery query;//以下执行相关QSL语句
    query.exec("select id from friends where studentnum == " + newfi.studentnum);
    int exist = query.next();
    return exist;
}

void newFriend(QString username, friendinfo newfi)
{    
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");    //添加数据库驱动

        db.setDatabaseName("./" + username + "/" + username + ".db");
        if(!db.open())
        {
            qDebug()<<"cannot open database";
        }

        int temp = getFriendsnum(username);
        temp++;

        QSqlQuery query;//以下执行相关QSL语句
        query.exec("update baseinfo set count = " + QString::number(temp, 10) + " where id = 2");
        query.exec("insert into friends values(" + QString::number(newfi.id, 10) + "," + QString::number(newfi.belongto, 10)
                   + ",'" + newfi.studentnum + "','" + newfi.name + "','" + newfi.photo + "','" + newfi.sign + "'," + QString::number(newfi.big, 10) + ")");
        int bt = newfi.belongto;
        query.exec("select friendsingroup from friendsgroup where id == " + QString::number(bt, 10));
        query.next();
        temp = query.value(0).toInt();
        temp++;
        query.exec("update friendsgroup set friendsingroup = " + QString::number(temp, 10) + " where id = " + QString::number(bt, 10));
}

void deleteGroup(QString username, int id)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");    //添加数据库驱动

    db.setDatabaseName("./" + username + "/" + username + ".db");
    if(!db.open())
    {
        qDebug()<<"cannot open database";
    }
    int temp = getGroupsnum(username);
    temp--;
    qDebug()<<temp;
    QSqlQuery query;//以下执行相关QSL语句
    //将分组中的好友移动到默认分组
    query.exec("select friendsingroup from friendsgroup where id == " + QString::number(id, 10));
    //qDebug()<<"select friendsingroup from friendsgroup where id == " + QString::number(id, 10);

    query.next();
    int num = query.value(0).toInt();
    //qDebug()<<num;
    query.exec("select friendsingroup from friendsgroup where id == 1");

    query.next();
    int defaultnum = query.value(0).toInt();
    //qDebug()<<defaultnum;
    defaultnum += num;
    //qDebug()<<defaultnum;
    query.exec("update friendsgroup set friendsingroup = " + QString::number(defaultnum, 10) + " where id = 1");
    //qDebug()<<"update friendsgroup set friendsingroup = " + QString::number(defaultnum, 10) + " where id = 1";
    query.exec("update friends set belongto = 1 where belongto = " + QString::number(id, 10));
    //qDebug()<<"update friends set belongto = 1 where belongto = " + QString::number(id, 10);
    //删除分组
    query.exec("delete from friendsgroup where id = " + QString::number(id, 10));
    //分组总数减1

    //qDebug()<<"update baseinfo set count = " + QString::number(temp, 10) + " where id = 1";
    query.exec("update baseinfo set count = " + QString::number(temp, 10) + " where id = 1");
    //qDebug()<<"update friendsgroup set id = id - 1 where id > " + QString::number(id, 10);
    query.exec("update friendsgroup set id = id - 1 where id > " + QString::number(id, 10));
    //qDebug()<<"update friends set belongto = belongto - 1 where belongto > "+ QString::number(id, 10);
    query.exec("update friends set belongto = belongto - 1 where belongto > "+ QString::number(id, 10));


}

void deleteFriend(QString username, int id)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");    //添加数据库驱动

    db.setDatabaseName("./" + username + "/" + username + ".db");
    if(!db.open())
    {
        qDebug()<<"cannot open database";
    }

    int temp = getFriendsnum(username);
    temp--;
   // qDebug()<<"deleting friend" << temp;
    QSqlQuery query;//以下执行相关QSL语句
    //所在分组好友数减1
    int bt;
    query.exec("select belongto from friends where id == " + QString::number(id, 10));
    query.next();
    bt = query.value(0).toInt();
    query.exec("update friendsgroup set friendsingroup = friendsingroup - 1 where id = " + QString::number(bt, 10));
    //从数据库中删除
    query.exec("delete from friends where id = " + QString::number(id, 10));
    query.exec("update baseinfo set count = " + QString::number(temp, 10) + " where id = 2");
    query.exec("update friends set id = id - 1 where id > " + QString::number(id, 10));
}

void setGroupexpand(QString username, int id, int expand)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");    //添加数据库驱动

    db.setDatabaseName("./" + username + "/" + username + ".db");
    if(!db.open())
    {
        qDebug()<<"cannot open database";
    }
    QSqlQuery query;//以下执行相关QSL语句
    query.exec("update friendsgroup set expand = " + QString::number(expand, 10) + " where id = " + QString::number(id, 10));
}

void setFriendbig(QString username, int id, int big)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");    //添加数据库驱动

    db.setDatabaseName("./" + username + "/" + username + ".db");
    if(!db.open())
    {
        qDebug()<<"cannot open database";
    }
    QSqlQuery query;//以下执行相关QSL语句
    query.exec("update friends set big = " + QString::number(big, 10) + " where id = " + QString::number(id, 10));
}

QString generateFilename()
{
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString str = time.toString("yyyyMMddhhmmss"); //设置显示格式
    return str;
}

void newFolder(QString username)
{
    QDir *temp = new QDir;
    temp->mkdir(username);
    temp->mkdir("./" + username + "/friendsphoto");
    temp->mkdir("./" + username + "/groupsphoto");
    newDatabase(username);
    for(int i = 0; i < 3; i++)
    {
        QPixmap system(":/image/resource_image/system_photo" + QString::number(i + 1, 10));
        system.save("./" + username + "/friendsphoto/system_photo" + QString::number(i + 1, 10) + ".jpg");
    }
    for(int i = 0; i < 20; i++)
    {
        QPixmap system(":/photo/resource_image/" + QString::number(i + 1, 10) + ".png");
        system.save("./" + username + "/friendsphoto/" + QString::number(i + 1, 10) + ".png");
    }
}


