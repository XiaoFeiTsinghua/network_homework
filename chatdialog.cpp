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
#include<QTextStream>
#include<chatrecord.h>
#include <QPainter>
//#include<stdio.h>

ChatDialog::ChatDialog(QString id, QWidget *parent) :
    QMainWindow(parent),
    id(id),
    ui(new Ui::ChatDialog)
{
    ui->setupUi(this);
    Recflag=0;
    exitButton = new QPushButton(this);
    minButton = new QPushButton(this);
    //QKeyEvent *ev;
    connect(ui->msgTxtEdit, SIGNAL(send_text()), this, SLOT(on_sendBtn_clicked()));
    connect(exitButton, &QPushButton::clicked, this, &ChatDialog::close);
        connect(minButton, &QPushButton::clicked, this, &ChatDialog::showMinimized);
    //this->eventFilter(ui->msgTxtEdit,ev);
     //this->msgTxtEdit::keyPressEvent ( ev );
        init();
}

ChatDialog::~ChatDialog()
{
    delete ui;
}
void ChatDialog::init()
{
    this->resize(700, 500);
    //圆角
        this->setWindowFlags(Qt::FramelessWindowHint);
        QBitmap bmp(this->size());
        bmp.fill();
        QPainter p(&bmp);
        p.setPen(Qt::NoPen);
        p.setBrush(Qt::black);
        p.drawRoundedRect(bmp.rect(), 3, 3);
        this->setMask(bmp);//设置窗体遮罩

        //背景颜色
        this->setAutoFillBackground(true);
        QPalette palette;
        palette.setColor(QPalette::Background, QColor(235,242,249));
        this->setPalette(palette);


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
        {
        QString fileName = id+".txt";
        QFile file(fileName);
          if(!file.open(QIODevice::WriteOnly  | QIODevice::Text|QIODevice::Append))
          {
             QMessageBox::warning(this,"sdf","can't open",QMessageBox::Yes);
          }
          QTextStream in(&file);
          in<<id+time2<<"\n";
          in<<msg<<"\n";
          file.close();
        }
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
   QString fileName = id+".txt";
   QFile file(fileName);
     if(!file.open(QIODevice::WriteOnly  | QIODevice::Text|QIODevice::Append))
     {
        QMessageBox::warning(this,"sdf","can't open",QMessageBox::Yes);
     }
     QTextStream in(&file);
     in<<"Me:"+time1<<"\n";
     in<<msg_tobesent<<"\n";
     file.close();

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
{
        QString time1 =QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")  ;
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

/*void ChatDialog::on_ChatRecord_clicked()
{
   QString fileName = id+".txt";
   QFile f(fileName);
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
         QMessageBox::warning(this,"sdf","can't open",QMessageBox::Yes);
        return;
    }
    ChatRecord * a;
    a = new ChatRecord(this);
    a->show();
    a->ui->textBrowser->setCurrentFont(QFont("宋体",12));
    QTextStream txtInput(&f);
    QString lineStr;
    while(!txtInput.atEnd())
    {
        lineStr = txtInput.readLine();
        //a->textBrowser->append(lineStr);
    }

    f.close();
}*/

void ChatDialog::on_ChatRe_clicked()
{
    if(Recflag==0) {this->setFixedSize(740,450); Recflag=1;}
    else {this->setFixedSize(472,450); Recflag=0;}
    QString fileName = id+".txt";
    QFile f(fileName);
    //ui->label->setText("对象："+id);
    qDebug() << "ChatRecord id--"<<id;
     if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
     {
          QMessageBox::warning(this,"sdf","can't open",QMessageBox::Yes);

     }
     else{
     ui->textBrowser->setCurrentFont(QFont("宋体",12));
     QTextStream txtInput(&f);
     QString lineStr;
    ui->textBrowser->clear();
     while(!txtInput.atEnd())
     {
         lineStr = txtInput.readLine();
         ui->textBrowser->append(lineStr);
     }
     }
     f.close();

}
