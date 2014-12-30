#include "friendwidget.h"

FriendWidget::FriendWidget(QWidget *parent) :
    QWidget(parent)
{
    this->resize(275, 30);
    photo = new QLabel(this);
    numLabel = new QLabel(this);
    name = new QLabel(this);
    sign = new QLabel(this);
    qDebug()<<"1"<<endl;
}

FriendWidget::FriendWidget(int id, int bt, QString num, QPixmap p, QString n, QString s, int b, QWidget *parent) :
    QWidget(parent),
    id(id)
{
    this->resize(275, 30);
    photo = new QLabel(this);
    numLabel = new QLabel(this);
    name = new QLabel(this);
    sign = new QLabel(this);
    belongto = bt;
    studentnum = num;
    photopix = p;
    showphoto = p;
    namestr = n;
    signstr = s;
    big = b;
    init();
}

void FriendWidget::init()
{
    this->resize(275, 30);
    photo->resize(20,20);
    photo->move(5, 5);
    photo->setScaledContents(true);
    photo->setPixmap(showphoto);

    numLabel->resize(100, 20);
    numLabel->move(100, 5);
    numLabel->setText(studentnum);

    name->resize(100, 20);
    name->move(30, 5);
    name->setText(namestr);

    sign->resize(100, 20);
    sign->move(150, 5);
    sign->setText(signstr);
}

void FriendWidget::choose()
{
    this->resize(275, 50);
    photo->resize(40, 40);
    photo->move(5, 5);
    photo->setScaledContents(true);
    photo->setPixmap(showphoto);

    numLabel->resize(100, 20);
    numLabel->move(60, 5);
    numLabel->setText(studentnum);

    name->resize(100, 20);
    name->move(150, 5);
    name->setText(namestr);

    sign->resize(100, 20);
    sign->move(50, 25);
    sign->setText(signstr);
}

void FriendWidget::cancel_choose()
{
    init();
}

int FriendWidget::isBig()
{
    return big;
}

void FriendWidget::setBig(int b)
{
    big = b;
}

void FriendWidget::online()
{
    showphoto = photopix;
}

void FriendWidget::offline()
{
    QImage qimage = photopix.toImage();
    cv::Mat mat = cv::Mat(qimage.height(), qimage.width(), CV_8UC4, (uchar*)qimage.bits(), qimage.bytesPerLine());
    cv::Mat mat2 = cv::Mat(mat.rows, mat.cols, CV_8UC3 );
    int from_to[] = { 0,0, 1,1, 2,2 };
    cv::mixChannels( &mat, 1, &mat2, 1, from_to, 3 );
    cvtColor(mat2, mat2, CV_RGB2GRAY);
    cvtColor(mat2, mat2, CV_GRAY2BGR);
    QImage* qimg = new QImage((unsigned char*)mat2.data, // uchar* data
            mat2.cols, mat2.rows, // width height
            mat2.step, //bytesPerLine
            QImage::Format_RGB888);
    //qimg->save("1.png");
    QPixmap pix = QPixmap::fromImage(*qimg);
    showphoto = pix;
}
