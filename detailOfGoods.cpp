#include "detailOfGoods.h"

DetailOfGoods::DetailOfGoods(QWidget *parent) : QFrame(parent)
{
    dis.setParent(this);
    dis.setGeometry(0,0,this->parentWidget()->width(),this->parentWidget()->height());
    dis.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}
DetailOfGoods::~DetailOfGoods()
{
    ;
}
void DetailOfGoods::newSetParent(QWidget *parent)
{
    this->setParent(parent);

    dis.setParent(this);
    dis.setGeometry(0,0,this->parentWidget()->width(),this->parentWidget()->height());
    dis.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    init();
}
void DetailOfGoods::init()
{
    QLabel *temp;
    int i=goods->getdisPic()->length();
    int j=0;
    while (--i>=0)
    {
        temp=new QLabel(&dis);
        temp->setStyleSheet("QLabel{border-image:url("+resourceRootPath+picRootPath+goods->getdisPic()->at(i)+");}");
        temp->setGeometry(10,j++*300,temp->parentWidget()->width()-20,300);
        /*
        QPixmap *pixmap = new QPixmap(resourceRootPath+picRootPath+goods->getdisPic()->at(i));
        pixmap->scaled(temp->size(), Qt::KeepAspectRatio);
        temp->setScaledContents(true);
        temp->setPixmap(*pixmap);
        */
    }
}
Goods* DetailOfGoods::getGoods()
{
    return goods;
}
void DetailOfGoods::setGoods(Goods *goods)
{
    this->goods=goods;
}
