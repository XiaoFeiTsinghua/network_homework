#ifndef CHATRECORD_H
#define CHATRECORD_H

#include <QDialog>

namespace Ui {
class ChatRecord;
}

class ChatRecord : public QDialog
{
    Q_OBJECT

public:
    explicit ChatRecord(QWidget *parent = 0);
    ~ChatRecord();
    QString  id;


     //f.close();

private slots:
    void on_show_clicked();

private:
    Ui::ChatRecord *ui;
};

#endif // CHATRECORD_H
