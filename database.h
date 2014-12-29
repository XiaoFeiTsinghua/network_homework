#ifndef DATABASE_H
#define DATABASE_H

#include <QtCore/QCoreApplication>
#include <QtSql>
#include <QString>
#include <QDateTime>
#include <QDir>
#include <QPixmap>

struct groupinfo
{
    int id;
    QString name;
    int friendsingroup;
    int expand;
};

struct friendinfo
{
    int id;
    int belongto;
    QString studentnum;
    QString name;
    QString photo;
    QString sign;
    int big;
};

void newHistroy();
int getRemember();
QString getKey();
int getAuto();
void setRemember(int flag);
void setKey(QString key);
void setAuto(int flag);
void addUser(QString username);
void clearUser();
int getUsernum();
QString getUser(int id);

void newDatabase(QString username);
void newFolder(QString username);
int getFriendsnum(QString username);
int getGroupsnum(QString username);
groupinfo getGroupinfo(QString username, int id);
friendinfo getFriendinfo(QString username, int id);
void newGroup(QString username, groupinfo newgi);
int existFriend(QString username, friendinfo newfi);
void newFriend(QString username, friendinfo newfi);
void deleteGroup(QString username, int id);
void deleteFriend(QString username, int id);
void setGroupexpand(QString username, int id, int expand);
void setFriendbig(QString username, int id, int big);
QString generateFilename();

#endif // DATABASE_H
