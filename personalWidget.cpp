#include "personalWidget.h"

PersonalWidget::PersonalWidget(QWidget *parent) : QFrame(parent)
{    
    this->setStyleSheet("background-color:#FFCCCC");
    this->setGeometry(0,0,this->parentWidget()->width(),this->parentWidget()->height());

    if(currentUser.length()>0)
        init();
    else
        init1();

    connect(display,SIGNAL(realDisplay(Goods*,bool)),this,SLOT(dispayDetailOfGoods(Goods*,bool)));
}
PersonalWidget::~PersonalWidget()
{
    ;
}
void PersonalWidget::init()
{
    topColor.setParent(this);
    topColor.setStyleSheet("background-color:#CC3399");
    topColor.setGeometry(0,0,topColor.parentWidget()->width(),200);

    headPortraitWidget.setParent(&topColor);
    headPortraitWidget.setStyleSheet("background-color:transparent;border-radius:40px;");
    headPortraitWidget.setGeometry(25,50,80,80);
    headPortrait=new ImageButton(resourceRootPath+picRootPath+currentUser+".jpg",0,&headPortraitWidget);
    headPortrait->setGeometry(0,0,80,80);

    nickname.setParent(&topColor);
    nickname.setStyleSheet("background-color:transparent;border-radius:0px;color:#ffffff");
    nickname.setText(currentUser);
    nickname.setFont(QFont("Timers" , 16 ,  QFont::Bold));
    nickname.setGeometry(120,40,200,50);
    nickname.setWordWrap(true);

    vip=new ImageButton("",0,&topColor);
    vip->setText("会员");
    vip->setStyleSheet("background-color:transparent;border-radius:0px;color:#f1c603");
    vip->setFont(QFont("Timers" , 12 ,  QFont::Bold));
    vip->setGeometry(120,80,40,50);
    vip->setWordWrap(true);
    vipIma=new ImageButton(resourceRootPath+picRootPath+"vip.png",0,&topColor);
    vipIma->setGeometry(160,93,20,20);

    setting=new ImageButton(settingIma,0,&topColor);
    setting->setGeometry(315,50,35,35);

    order.setParent(this);
    order.setStyleSheet("background-color:#f8bebe;border-radius:10px;");
    order.setGeometry(10,175,336,100);
    orderLabel=new QLabel(&order);
    orderLabel->setText("我的订单");
    orderLabel->setFont(QFont("Timers" , 10 ,  QFont::Bold));
    orderLabel->setGeometry(10,2,80,23);
    lookMoreOrder=new ImageButton("",0,&order);
    lookMoreOrder->setText("查看更多订单 >");
    lookMoreOrder->setFont(QFont("Timers" , 10 ,  QFont::DemiBold));
    lookMoreOrder->setStyleSheet("background-color:transparent;color:#362424");
    lookMoreOrder->setGeometry(230,2,100,23);
    dividLine.setParent(&order);
    dividLine.setText("---------------------------------------------------------------------------------------------");
    dividLine.setFont(QFont("Timers" , 10 ,  QFont::DemiBold));
    dividLine.setStyleSheet("background-color:transparent;color:#a49898");
    dividLine.setGeometry(0,23,dividLine.parentWidget()->width(),3);

    forPay=new ImageButton("",0,&order);
    forPay->setText("待付款");
    forPay->setFont(QFont("Timers" , 10 ,  QFont::Bold));
    forPay->setStyleSheet("background-color:transparent;color:#362424");
    forPay->setGeometry(15,50,40,30);
    forSend=new ImageButton("",0,&order);
    forSend->setText("待发货");
    forSend->setFont(QFont("Timers" , 10 ,  QFont::Bold));
    forSend->setStyleSheet("background-color:transparent;color:#362424");
    forSend->setGeometry(75,50,40,30);
    forRecive=new ImageButton("",0,&order);
    forRecive->setText("待收货");
    forRecive->setFont(QFont("Timers" , 10 ,  QFont::Bold));
    forRecive->setStyleSheet("background-color:transparent;color:#362424");
    forRecive->setGeometry(135,50,40,30);
    froComment=new ImageButton("",0,&order);
    froComment->setText("待评价");
    froComment->setFont(QFont("Timers" , 10 ,  QFont::Bold));
    froComment->setStyleSheet("background-color:transparent;color:#362424");
    froComment->setGeometry(195,50,40,30);
    refund=new ImageButton("",0,&order);
    refund->setText("退款/售后");
    refund->setFont(QFont("Timers" , 10 ,  QFont::Bold));
    refund->setStyleSheet("background-color:transparent;color:#362424");
    refund->setGeometry(255,50,70,30);

    mayYouLike.setParent(this);
    mayYouLike.setStyleSheet("background-color:#f8bebe;border-radius:10px;");
    mayYouLike.setGeometry(10,280,336,1000);
    mayYouLikeTitleLabel=new ImageButton("",0,&mayYouLike);
    mayYouLikeTitleLabel->setText("猜你喜欢");
    mayYouLikeTitleLabel->setFont(QFont("Timers" , 10 ,  QFont::Bold));
    mayYouLikeTitleLabel->setStyleSheet("background-color:transparent;color:#000000");
    mayYouLikeTitleLabel->setGeometry(10,2,70,23);
    dividLine1.setParent(&mayYouLike);
    dividLine1.setText("---------------------------------------------------------------------------------------------");
    dividLine1.setFont(QFont("Timers" , 10 ,  QFont::DemiBold));
    dividLine1.setStyleSheet("background-color:transparent;color:#a49898");
    dividLine1.setGeometry(0,23,dividLine1.parentWidget()->width(),3);

    display=new DisplayArea(&mayYouLike);
    display->setGeometry(4,28,display->parentWidget()->width()-8,1000);
}
void PersonalWidget::init1()
{
    topColor.setParent(this);
    topColor.setStyleSheet("background-color:#CC3399");
    topColor.setGeometry(0,0,topColor.parentWidget()->width(),200);

    headPortraitWidget.setParent(&topColor);
    headPortraitWidget.setStyleSheet("background-color:transparent;border-radius:40px;");
    headPortraitWidget.setGeometry(25,50,80,80);
    headPortrait=new ImageButton(resourceRootPath+picRootPath+"emptyPortrait.jpg",0,&headPortraitWidget);
    headPortrait->setGeometry(0,0,80,80);

    nickname.setParent(&topColor);
    nickname.setStyleSheet("background-color:transparent;border-radius:0px;color:#ffffff");
    nickname.setText("注册/登陆");
    nickname.setFont(QFont("Timers" , 16 ,  QFont::Bold));
    nickname.setGeometry(120,40,200,50);
    nickname.setWordWrap(true);

    vip=new ImageButton("",0,&topColor);
    vip->setText("会员");
    vip->setStyleSheet("background-color:transparent;border-radius:0px;color:#f1c603");
    vip->setFont(QFont("Timers" , 12 ,  QFont::Bold));
    vip->setGeometry(120,80,40,50);
    vip->setWordWrap(true);
    vipIma=new ImageButton(resourceRootPath+picRootPath+"vip.png",0,&topColor);
    vipIma->setGeometry(160,93,20,20);

    setting=new ImageButton(settingIma,0,&topColor);
    setting->setGeometry(315,50,35,35);

    mayYouLike.setParent(this);
    mayYouLike.setStyleSheet("background-color:#f8bebe;border-radius:10px;");
    mayYouLike.setGeometry(10,175,336,1000);
    mayYouLikeTitleLabel=new ImageButton("",0,&mayYouLike);
    mayYouLikeTitleLabel->setText("猜你喜欢");
    mayYouLikeTitleLabel->setFont(QFont("Timers" , 10 ,  QFont::Bold));
    mayYouLikeTitleLabel->setStyleSheet("background-color:transparent;color:#000000");
    mayYouLikeTitleLabel->setGeometry(10,2,70,23);
    dividLine1.setParent(&mayYouLike);
    dividLine1.setText("---------------------------------------------------------------------------------------------");
    dividLine1.setFont(QFont("Timers" , 10 ,  QFont::DemiBold));
    dividLine1.setStyleSheet("background-color:transparent;color:#362424");
    dividLine1.setGeometry(0,23,dividLine1.parentWidget()->width(),3);

    display=new DisplayArea(&mayYouLike);
    display->setGeometry(4,28,display->parentWidget()->width()-8,1000);
}
void PersonalWidget::dispayDetailOfGoods(Goods *goods, bool isClicked)
{
    if(!isClicked)
        goto others;

    emit realDisplay(goods,true);

    others:
    ;
}
