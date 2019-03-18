#include "displayArea.h"

DisplayArea::DisplayArea(QWidget *parent) : QFrame(parent)
{
    scrollArea.setParent(this);
    scrollArea.setGeometry(0,0,this->parentWidget()->width(),this->parentWidget()->height());
    scrollArea.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    init();
}
DisplayArea::~DisplayArea()
{
    ;
}
void DisplayArea::init()
{
    int i=goodsList.length();
    GoodsBar* temp;
    int j=0;

    while(i>0)
    {
        temp=new GoodsBar(goodsList.at(--i),0,&scrollArea);
        temp->move(0,4+142*j++);
        connect(temp,SIGNAL(clicked(Goods*,bool)),this,SLOT(dispayDetailOfGoods(Goods*,bool)));
        connect(temp,SIGNAL(addGoodsSignal(Goods*)),this,SLOT(addGoods(Goods*)));

        allGoods.append(temp);
    }
}
void DisplayArea::dispayDetailOfGoods(Goods *goods, bool isClicked)
{
    if(!isClicked)
        goto others;

    emit realDisplay(goods,true);

    others:
    ;
}
void DisplayArea::addGoods(Goods *goods)
{
    emit addUserGoodsArea(goods);
}
