#include "shoppingCarWidget.h"

ShoppingCarWidget::ShoppingCarWidget(QWidget *parent) : QFrame(parent)
{
    worth=0.0;
    goodsNumber=0;
    isSelectAll=false;

    this->setStyleSheet("background-color:#FFCCCC");
    this->setGeometry(0,0,this->parentWidget()->width(),this->parentWidget()->height());

    title.setParent(this);
    title.setStyleSheet("background-color:#d4137c;border-radius:0px;color:#FFCC00");
    title.setText(QString("                购 物 车"));
    title.setFont(QFont("Timers" , 18 ,  QFont::Bold));
    title.setGeometry(0,0,title.parentWidget()->width(),50);
    title.setWordWrap(true);

    centerWidget.setParent(this);
    centerWidget.setGeometry(0,50,this->parentWidget()->width(),this->parentWidget()->height()-50);
    centerWidget.resize(this->parentWidget()->width(),this->parentWidget()->height()-50);

    scrollArea.setParent(&centerWidget);
    scrollArea.setGeometry(4,0,centerWidget.parentWidget()->width(),centerWidget.parentWidget()->height());
    scrollArea.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    init();

}
ShoppingCarWidget::~ShoppingCarWidget()
{
    ;
}
void ShoppingCarWidget::init()
{
    if(currentUser.length()<=0)
    {
        empt.setParent(&scrollArea);
        empt.setStyleSheet("background-color:transparent;border-radius:0px;color:#000000");
        empt.setText(QString("您的购物车还没有商品哦！\n      赶快去添加吧！"));
        empt.setFont(QFont("Timers" , 14 ,  QFont::DemiBold));
        empt.setGeometry(60,180,title.parentWidget()->width(),50);
        empt.setWordWrap(true);
    }else
    {
        QFile userCar(resourceRootPath+currentUser+".txt");
        if(!userCar.exists())
        {
            networkStateWarning(QObject::tr("网络连接提示："),QObject::tr("对不起，服务器跑丢啦！"));
        }
        if(!userCar.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug()<<"警告：goods.txt文件打开失败！";
        }
        QString temp;
        QTextStream in(&userCar);
        GoodsBar *temp1;
        int j=0;

        while(!in.atEnd())
        {
            temp1=NULL;
            temp.clear();
            temp=in.readLine();
            temp1=new GoodsBar(Goods(temp),1,&scrollArea);
            temp1->move(0,4+142*j++);
            userGoods.append(temp1);

            connect(temp1,SIGNAL(clicked(Goods*,bool)),this,SLOT(realDisplayDetailInfo(Goods*,bool)));
            connect(temp1,SIGNAL(goodsInfoChanged(Goods*)),this,SLOT(changeUsersGoods(Goods*)));
            connect(this,SIGNAL(selectAllSignal(bool)),temp1,SLOT(impleSelectAll(bool)));
            connect(temp1,SIGNAL(sigPrice(float,int)),this,SLOT(computPrice_Number(float,int)));
        }
        userCar.close();
    }

    if(userGoods.length()<=0)
    {
        empt.setParent(&scrollArea);
        empt.setStyleSheet("background-color:transparent;border-radius:0px;color:#000000");
        empt.setText(QString("您的购物车还没有商品哦！\n      赶快去添加吧！"));
        empt.setFont(QFont("Timers" , 14 ,  QFont::DemiBold));
        empt.setGeometry(60,180,title.parentWidget()->width(),50);
        empt.setWordWrap(true);
    }else
    {

        processBar.setParent(this);
        processBar.setStyleSheet("background-color:#e569be");
        processBar.setGeometry(0,processBar.parentWidget()->height()-60,processBar.parentWidget()->width(),60);

        selectALLIm=new ImageButton(resourceRootPath+picRootPath+"unSelect.png",0,&processBar);
        selectALLIm->setGeometry(5,15,30,30);
        connect(selectALLIm,SIGNAL(clicked(int,bool)),this,SLOT(sendSelectSignal(int,bool)));
        selectALL=new ImageButton("",0,&processBar);
        selectALL->setText("全选");
        selectALL->setStyleSheet("QLabel{background-color:transparent;color:#362424;}\
                                 QLabel:hover{background-color:transparent;color:#362424;}\
                                 QLabel:pressed{background-color:transparent;color:#362424;}");
        selectALL->setFont(QFont("Timers" , 12 ,  QFont::DemiBold));
        selectALL->setGeometry(35,12,35,40);
        connect(selectALL,SIGNAL(clicked(int,bool)),this,SLOT(sendSelectSignal(int,bool)));

        deleteAll=new ImageButton("",0,&processBar);
        deleteAll->setText("删除");
        deleteAll->setStyleSheet("QLabel{background-color:transparent;color:#362424;}\
                                    QLabel:hover{background-color:transparent;color:#ffd800;}\
                                    QLabel:pressed{background-color:transparent;color:#ff3000;}");
        deleteAll->setFont(QFont("Timers" , 12 ,  QFont::DemiBold));
        deleteAll->setGeometry(72,12,35,40);
        connect(deleteAll,SIGNAL(clicked(int,bool)),this,SLOT(deleteUserGoods(int,bool)));

        total=new ImageButton("",0,&processBar);
        total->setText("合计:");
        total->setStyleSheet("QLabel{background-color:transparent;color:#362424;}");
        total->setFont(QFont("Timers" , 12 ,  QFont::DemiBold));
        total->setGeometry(120,10,40,40);

        totalWorth=new ImageButton("",0,&processBar);
        totalWorth->setText("￥"+QString::number(worth));
        totalWorth->setStyleSheet("QLabel{background-color:transparent;color:#e81818;}");
        //totalWorth->setStyleSheet("<h1><font color=#362424>合计:</font><font color=#e81818>￥</font>\
                                    <font color=#e81818>"+QString::number(worth)+"</font></h1>");
        totalWorth->setFont(QFont("Timers" , 14 ,  QFont::DemiBold));
        totalWorth->setGeometry(155,10,90,40);

        settlement=new ImageButton("",0,&processBar);
        settlement->setText("结算("+QString::number(goodsNumber)+")");
        settlement->setStyleSheet("QLabel{background-color:#ff003c;border-radius:20px;color:#ffffff;}");
        settlement->setFont(QFont("Timers" , 12 ,  QFont::DemiBold));
        settlement->setAlignment(Qt::AlignCenter);
        settlement->setGeometry(250,10,100,40);
        connect(settlement,SIGNAL(clicked(int,bool)),this,SLOT(countGoods(int,bool)));
    }
}
void ShoppingCarWidget::realDisplayDetailInfo(Goods *goods, bool isClicked)
{
    if(!isClicked)
        goto others;

    emit realDisplay(goods,true);

    others:
    ;
}
void ShoppingCarWidget::changeUsersGoods(Goods *goods)
{
    QFile userCar(resourceRootPath+currentUser+".txt");
    if(userCar.exists())
        userCar.remove();
    if(!userCar.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug()<<"警告：goods.txt文件打开失败！";
    }
    QTextStream out(&userCar);

    int i=userGoods.length();
    while (--i>=0)
    {
        out<<userGoods.at(i)->getGoodsInfo()<<endl;
    }
}
void ShoppingCarWidget::deleteUserGoods(int flag, bool isClicked)
{
    QFile userCar(resourceRootPath+currentUser+".txt");
    if(userCar.exists())
        userCar.remove();
    if(!userCar.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug()<<"警告：goods.txt文件打开失败！";
    }
    QTextStream out(&userCar);

    QVector<GoodsBar*> temp1;
    int i=userGoods.length();
    int j=i;
    while (--i>=0)
    {
        if(!userGoods.at(i)->whetherSelect())
        {
            out<<userGoods.at(i)->getGoodsInfo()<<endl;
            temp1.append(userGoods.at(i));
        }
    }
    userGoods.clear();
    i=temp1.length();
    int k=i;
    while(--i>=0)
    {
        userGoods.append(temp1.at(i));
    }

    emit reload();
}
void ShoppingCarWidget::sendSelectSignal(int random, bool isClicked)
{
    if(isSelectAll=!isSelectAll)
    {
        selectALLIm->setStyleSheet("QLabel{border-image: url("+resourceRootPath+picRootPath+"selected.png)};");
        emit selectAllSignal(isSelectAll);
    }
    else
    {
        selectALLIm->setStyleSheet("QLabel{border-image: url("+resourceRootPath+picRootPath+"unSelect.png)};");
        emit selectAllSignal(isSelectAll);
    }
}
void ShoppingCarWidget::computPrice_Number(float price,int number)
{
    if(number>0)
    {
        worth+=price*number;
        goodsNumber+=number;
        totalWorth->setText("￥"+QString::number(worth));
        settlement->setText("结算("+QString::number(goodsNumber)+")");
    }
    else if(number<0)
    {
        worth+=price*number;
        goodsNumber+=number;
        totalWorth->setText("￥"+QString::number(worth));
        settlement->setText("结算("+QString::number(goodsNumber)+")");
    }
}
void ShoppingCarWidget::countGoods(int random, bool isClicked)
{
    if(goodsNumber<=0)
        networkStateWarning(QObject::tr("温馨提示："),QObject::tr("您还没有选中任何商品哦！"));
    else
    {
        afterCount();
        emit countGoodsSuccessed();
    }
}
void ShoppingCarWidget::displayCountSuccessed()
{
    //deleteUserGoods(0,true);
    //afterCount();

    countSuccessed->setGeometry(0,0,countSuccessed->parentWidget()->width(),
                                countSuccessed->parentWidget()->height());
    QWidget *tell=new QWidget(countSuccessed);
    tell->setStyleSheet("background-color:#CC3399");
    tell->setGeometry(0,0,tell->parentWidget()->width(),150);
    QLabel *tell1=new QLabel(tell);
    tell1->setText("您的商品已经结算完成！\n再看看其他商品吧！");
    tell1->setStyleSheet("QLabel{background-color:transparent;color:#000000;}");
    tell1->setFont(QFont("Timers" , 14 ,  QFont::Bold));
    tell1->setGeometry(60,30,220,100);
    tell1->setAlignment(Qt::AlignCenter);

    mayYouLike.setParent(countSuccessed);
    mayYouLike.setStyleSheet("background-color:#f8bebe;border-radius:10px;");
    mayYouLike.setGeometry(10,127,336,1000);
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

    seeAgain=new DisplayArea(&mayYouLike);
    seeAgain->setGeometry(4,28,seeAgain->parentWidget()->width()-8,1000);
}
void ShoppingCarWidget::afterCount()
{
    QFile userCar(resourceRootPath+currentUser+".txt");
    if(userCar.exists())
        userCar.remove();
    if(!userCar.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug()<<"警告：goods.txt文件打开失败！";
    }
    QTextStream out(&userCar);

    QVector<GoodsBar*> temp1;
    int i=userGoods.length();
    int j=i;
    while (--i>=0)
    {
        if(!userGoods.at(i)->whetherSelect())
        {
            out<<userGoods.at(i)->getGoodsInfo()<<endl;
            temp1.append(userGoods.at(i));
        }
    }
    userGoods.clear();
    i=temp1.length();
    int k=i;
    while(--i>=0)
    {
        userGoods.append(temp1.at(i));
    }
}
void ShoppingCarWidget::addGoods(Goods *goods)
{
    Goods *temp=new Goods(goods->toString());
    temp->setNumber(1);
    int j=userGoods.length();
    GoodsBar *temp1=new GoodsBar(Goods(temp->toString()),1,&scrollArea);
    temp1->move(0,4+142*j++);
    userGoods.append(temp1);

    deleteUserGoods(0,true);
}


