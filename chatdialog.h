#ifndef CHATDIALOG_H
#define CHATDIALOG_H
#include <QTextEdit>
#include <QKeyEvent>
#include<QMessageBox>
#include <QMainWindow>
#include "mtextedit.h"
#include <QtNetwork>
#include <QPushButton>
#include <QBitmap>

namespace Ui {
class ChatDialog;
}

class ChatDialog : public QMainWindow
{
    Q_OBJECT

public:
    explicit ChatDialog(QString id, QWidget *parent = 0);
    ~ChatDialog();
    void init();
    //void msgTxtEdit::keyPressEvent ( QKeyEvent * ev );
    //bool eventFilter(QObject *obj, QKeyEvent * ev);
private slots:
    void on_fontCbx_currentFontChanged(const QFont &f);

    void on_sizeCbx_currentIndexChanged(const QString &arg1);

    void on_sendBtn_clicked();

    void rec_msg(QString id, QString msg);

    void on_msgTxtEdit_currentCharFormatChanged(const QTextCharFormat &format);

    void on_fontCbx_currentTextChanged(const QString &arg1);

    void on_pushButton_clicked();

 //  void on_ChatRecord_clicked();

    void on_ChatRe_clicked();

signals:
    void send_msg(QString id, QString msg);


private:
    Ui::ChatDialog *ui;
    QString msg_tobesent;
    QString id;
    int Recflag;
    QPushButton *exitButton, *minButton;
};


#endif // CHATDIALOG_H
