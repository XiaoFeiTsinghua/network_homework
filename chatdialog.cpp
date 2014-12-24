#include "chatdialog.h"
#include "ui_chatdialog.h"
#include <QMessageBox>
#include "assert.h"
#include <QTextEdit>
#include <QKeyEvent>
#include <QDebug>
#include <QtNetwork>
#include <QDateTime>
#include "opencv.hpp"
#include <QFileDialog>

//#include<stdio.h>

ChatDialog::ChatDialog(QString id, QWidget *parent) :
    QMainWindow(parent),
    id(id),
    ui(new Ui::ChatDialog)
{
    ui->setupUi(this);
    //QKeyEvent *ev;
    connect(ui->msgTxtEdit, SIGNAL(send_text()), this, SLOT(on_sendBtn_clicked()));
    //this->eventFilter(ui->msgTxtEdit,ev);
     //this->msgTxtEdit::keyPressEvent ( ev );
}

ChatDialog::~ChatDialog()
{
    delete ui;
}

void ChatDialog::rec_msg(QString id, QString msg)
{
    if ( id == this->id )
    {
        QString time2 =QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")  ;
        //QMessageBox::information(this, "get msg!", "from" + id + " " + msg);
        ui->msgBrowser->setCurrentFont(QFont("宋体",12));
        ui->msgBrowser->append(id+" "+time2);
        //ui->msgBrowser->setCurrentFont(QFont("Times New Roman",12));
        ui->msgBrowser->append(msg);
    }
    qDebug() << "id" << id << "this->id" << this->id << "msg" << msg;
}

void ChatDialog::on_fontCbx_currentFontChanged(const QFont &f)
{
    ui->msgTxtEdit->setCurrentFont(f);
    ui->msgTxtEdit->setFocus();
}

void ChatDialog::on_sizeCbx_currentIndexChanged(const QString &arg1)
{
    ui->msgTxtEdit->setFontPointSize(arg1.toDouble());
    ui->msgTxtEdit->setFocus();
}

void ChatDialog::on_sendBtn_clicked()
{   QString time1 =QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")  ;
   if( ui->msgTxtEdit->toPlainText()== "") { QMessageBox::warning(0,tr("警告"),tr("发送内容不能为空"),QMessageBox::Ok); return;}
   msg_tobesent=ui->msgTxtEdit->toPlainText();
   ui->usrNumLbl->setText(msg_tobesent);
   ui->msgTxtEdit->clear();
   ui->msgBrowser->setCurrentFont(QFont("宋体",12));
   ui->msgBrowser->append("Me:"+time1);
   ui->msgBrowser->setCurrentFont(ui->msgTxtEdit->currentFont());
   ui->msgBrowser->append(msg_tobesent);
   emit send_msg(id, msg_tobesent);

  // QMessageBox::warning(0,tr("显示"),tr(msg_tobesent),QMessageBox::Ok);
  // printf("%s",msg_tobesent.toStdString());
}



void ChatDialog::on_msgTxtEdit_currentCharFormatChanged(const QTextCharFormat &format)
{

}

void ChatDialog::on_fontCbx_currentTextChanged(const QString &arg1)
{

}

void ChatDialog::on_pushButton_clicked()
{      QString time1 =QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")  ;
        QString filename = QFileDialog::getOpenFileName(this,tr("Open Image"),".",tr("Image Files(*.png *.jpg *.jepg *.bmg)"));
        cv::Mat image = cv::imread(filename.toLatin1().data());
        cv::Mat temp;

        cv::cvtColor(image,temp,CV_BGR2RGB);
        //QImage img = QImage((const unsigned char*)(temp.data),temp.cols,temp.rows,QImage::Format_RGB888);
        QString path = QString("<img src=\"%1\"/>").arg(filename);
        ui->msgBrowser->setCurrentFont(QFont("宋体",12));
        ui->msgBrowser->append("Me:"+time1);
        //if(image.rows>=100) image.rows=100;
        //if(image.cols>=100) image.cols=100;
        //ui->msgBrowser->setFixedHeight(image.rows);
        //ui->msgBrowser->setFixedWidth(image.cols);
       // ui->textBrowser->clear();
        ui->msgBrowser->append(path);
}
