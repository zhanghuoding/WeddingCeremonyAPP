#include "goodsBar.h"

GoodsBar::GoodsBar(Goods goods,int flag,QWidget *parent) : QFrame(parent)
{
    this->flag=flag;
    isSelect=false;

    this->setStyleSheet("background-color:#FF99CC;border-radius:8px;");
    this->resize(346,134);

    pic=new ImageButton("",0,this);
    pic->setStyleSheet("border-image:url("+resourceRootPath+goods.samplePic+");background-color:#FFCCCC;border-radius:8px;");
    pic->setGeometry(7,7,138,120);

    title=new ImageButton("",0,this);
    title->setStyleSheet("background-color:transparent;border-radius:8px;");
    title->setText(goods.title);
    title->setFont(QFont("Timers" , 12 ,  QFont::Bold));
    title->setGeometry(154,5,188,50);
    title->setWordWrap(true);

    price=new ImageButton("",0,this);
    price->setStyleSheet("background-color:transparent;border-radius:8px;color:#e81818;");
    price->setText("￥ "+QString::number(goods.price));
    price->setFont(QFont("Timers" , 14 ,  QFont::Bold));
    price->setGeometry(154,90,100,40);
    price->setWordWrap(true);

    add=new ImageButton_1("",-2,0);
    if(!flag)
    {
        add=new ImageButton_1("",-2,this);
        add->setStyleSheet("background-color:transparent;border-radius:0px;border:0px solid #000000;color:#000000;");
        add->setText("+");
        add->setFont(QFont("Timers" , 10 ,  QFont::Bold));
        add->setGeometry(325,70,20,30);
        add->setWordWrap(true);
        connect(add,SIGNAL(clicked(int,bool)),this,SLOT(addUserGoods(int,bool)));
    }

    if(!flag)
        goto finish;

    number=new ImageButton_1("",0,this);
    number->setStyleSheet("background-color:transparent;border-radius:0px;border:1px solid #000000;color:#000000;");
    number->setText(QString::number(goods.number));
    number->setFont(QFont("Timers" , 10 ,  QFont::Bold));
    number->setAlignment(Qt::AlignCenter);
    number->setGeometry(284,90,30,30);
    number->setWordWrap(true);

    increase=new ImageButton_1("",-2,this);
    increase->setStyleSheet("background-color:transparent;border-radius:0px;border:1px solid #000000;color:#000000;");
    increase->setText(" + ");
    increase->setFont(QFont("Timers" , 10 ,  QFont::Bold));
    increase->setGeometry(314,90,20,30);
    increase->setWordWrap(true);

    decrease=new ImageButton_1("",-1,this);
    decrease->setStyleSheet("background-color:transparent;border-radius:0px;border:1px solid #000000;color:#000000;");
    decrease->setText(" - ");
    decrease->setFont(QFont("Timers" , 10 ,  QFont::Bold));
    decrease->setGeometry(264,90,20,30);
    decrease->setWordWrap(true);

    select=new ImageButton_1(resourceRootPath+picRootPath+"unSelect.png",-3,this);
    select->setGeometry(296,58,30,30);

    connect(increase,SIGNAL(clicked(int,bool)),this,SLOT(changeGoodsInfo(int,bool)));
    connect(decrease,SIGNAL(clicked(int,bool)),this,SLOT(changeGoodsInfo(int,bool)));
    connect(select,SIGNAL(clicked(int,bool)),this,SLOT(changeGoodsInfo(int,bool)));

    finish:

    this->goods=new Goods(goods.toString());
}
GoodsBar::~GoodsBar()
{
    ;
}
QString GoodsBar::getGoodsInfo()
{
    return goods->toString();
}
void GoodsBar::mousePressEvent(QMouseEvent *event)
{
    // 如果单击了就触发clicked信号
    if ( event->button() == Qt::LeftButton )
    {
        emit clicked(goods,true);
    }
    // 将该事件传给父类处理
    QWidget::mousePressEvent(event);
}
void GoodsBar::changeGoodsInfo(int flag, bool isClicked)
{
    if(!isClicked)
        goto others;

    switch (flag)
    {
    case -1:
        if(goods->number>1)
        {
            emit sigPrice(goods->price,-goods->number);
            goods->number-=1;
            number->setText(QString::number(goods->number));
            emit goodsInfoChanged(goods);
            emit sigPrice(goods->price,goods->number);
        }
        else
            networkStateWarning(QObject::tr("温馨提示："),QObject::tr("该商品已经不能再少啦！"));
        break;
    case -2:
        emit sigPrice(goods->price,-goods->number);
        goods->number+=1;
        number->setText(QString::number(goods->number));
        emit goodsInfoChanged(goods);
        emit sigPrice(goods->price,goods->number);
        break;
    case -3:
        if(isSelect=!isSelect)
        {
            select->setStyleSheet("QLabel{border-image: url("+resourceRootPath+picRootPath+"selected.png)};");
            goods->isSelect=true;
            emit sigPrice(goods->price,goods->number);
        }
        else
        {
            select->setStyleSheet("QLabel{border-image: url("+resourceRootPath+picRootPath+"unSelect.png)};");
            goods->isSelect=false;
            emit sigPrice(goods->price,-goods->number);
        }
        break;
    default:
        break;
    }

    others:
    ;
}
bool GoodsBar::whetherSelect()
{
    return goods->whetherSelected();
}
void GoodsBar::impleSelectAll(bool select1)
{
    if(isSelect=select1)
    {
        select->setStyleSheet("QLabel{border-image: url("+resourceRootPath+picRootPath+"selected.png)};");
        goods->isSelect=true;
        emit sigPrice(goods->price,goods->number);
    }
    else
    {
        select->setStyleSheet("QLabel{border-image: url("+resourceRootPath+picRootPath+"unSelect.png)};");
        goods->isSelect=false;
        emit sigPrice(goods->price,-goods->number);
    }
}
void GoodsBar::addUserGoods(int flag,bool isClicked)
{
    emit addGoodsSignal(goods);
}
