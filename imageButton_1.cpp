#include "imageButton_1.h"

ImageButton_1::ImageButton_1(QString imagePath,int flag,QWidget *parent) : QLabel(parent)
{
    this->flag=flag;
    //this->setStyleSheet(QString("QLabel{border-radius:60px}"));
    this->setStyleSheet("QLabel{border-image: url("+imagePath+")};");
}
ImageButton_1::~ImageButton_1()
{
    ;
}
void ImageButton_1::mousePressEvent(QMouseEvent *event)
{
    // 如果单击了就触发clicked信号
    if ( event->button() == Qt::LeftButton )
    {
        emit clicked(flag,true);
    }
}
