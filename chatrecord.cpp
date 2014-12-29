#include "chatrecord.h"
#include "ui_chatrecord.h"
#include<QFile>
#include<QmessageBox>
#include<QTextStream>
#include<QDebug>

ChatRecord::ChatRecord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatRecord)
{
    ui->setupUi(this);
    ui->textBrowser->setEnabled(true);


}

ChatRecord::~ChatRecord()
{
    delete ui;
}

void ChatRecord::on_show_clicked()
{
    QString fileName = id+".txt";
    QFile f(fileName);
    ui->label->setText("对象："+id);
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
