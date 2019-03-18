#include "mainwindow.h"

#include <QLineEdit>
#include <QPushButton>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    rootWidget=new QWidget(this);

    this->setMinimumSize(windowSize->width(),windowSize->height());
    this->setMaximumSize(windowSize->width(),windowSize->height());
    this->resize(windowSize->width(),windowSize->height());
    //this->setCentralWidget(rootWidget);
    this->setStyleSheet("background-color:#ff0000;");

    rootWidget->setGeometry(2,2,this->width()-4,this->height()-54);
    rootWidget->setMinimumSize(this->width()-4,this->height()-54);
    rootWidget->setMaximumSize(this->width()-4,this->height()-54);
    rootWidget->resize(this->width()-4,this->height()-54);
    rootWidget->setStyleSheet("background-color:#FFCCCC;");

    bottom=new QWidget(this);
    perWidget=new PersonalWidget(rootWidget);
    shopWidget=new ShoppingCarWidget(rootWidget);
    topWidget=new QWidget(rootWidget);

    topWidget->setGeometry(0,0,topWidget->parentWidget()->width(),topWidget->parentWidget()->height());
    /*topWidget->setMinimumSize(topWidget->parentWidget()->width(),topWidget->parentWidget()->height());
    topWidget->setMaximumSize(topWidget->parentWidget()->width(),topWidget->parentWidget()->height());
    topWidget->resize(topWidget->parentWidget()->width(),topWidget->parentWidget()->height());*/
    topWidget->setStyleSheet("background-color:#af28dc;");

    bottom->setGeometry(2,this->height()-50,this->width()-4,48);
    bottom->setStyleSheet("background-color:#d4137c;");

    connect(perWidget,SIGNAL(realDisplay(Goods*,bool)),SLOT(realDisplayDetail(Goods*,bool)));
    connect(shopWidget,SIGNAL(realDisplay(Goods*,bool)),this,SLOT(realDisplayDetail(Goods*,bool)));
    connect(shopWidget,SIGNAL(reload()),this,SLOT(reloadShoppingCar()));
    connect(shopWidget,SIGNAL(countGoodsSuccessed()),this,SLOT(countGoodsSuccessed()));

    init();
}

MainWindow::~MainWindow()
{

}
void MainWindow::init()
{
    locateButton=new ImageButton(locateIma,-1,topWidget);
    locateButton->setGeometry(0,0,50,50);

    creatSearchBox();

    scanButton=new ImageButton(scanIma,-1,topWidget);
    scanButton->setGeometry(306,0,50,50);

    homeButton=new ImageButton(homeIma,1,bottom);
    homeButton->setGeometry(28,0,80,48);
    connect(homeButton,SIGNAL(clicked(int,bool)),this,SLOT(changeHome(int,bool)));

    shopping_carButton=new ImageButton(shopping_carIma,2,bottom);
    shopping_carButton->setGeometry(140,0,80,48);
    connect(shopping_carButton,SIGNAL(clicked(int,bool)),this,SLOT(changeHome(int,bool)));

    personalButton=new ImageButton(personalIma,3,bottom);
    personalButton->setGeometry(250,0,80,48);
    connect(personalButton,SIGNAL(clicked(int,bool)),this,SLOT(changeHome(int,bool)));

    displayArea=new DisplayArea(topWidget);
    displayArea->setGeometry(4,52,displayArea->parentWidget()->width()-8,displayArea->parentWidget()->height()-50-6);
    displayArea->setStyleSheet("background-color:#FFCCCC;border-radius:8px;");
    connect(displayArea,SIGNAL(realDisplay(Goods*,bool)),this,SLOT(realDisplayDetail(Goods*,bool)));
    connect(displayArea,SIGNAL(addUserGoodsArea(Goods*)),this,SLOT(addGoods(Goods*)));
    connect(this,SIGNAL(addUsersGoods(Goods*)),shopWidget,SLOT(addGoods(Goods*)));
}
void MainWindow::creatSearchBox()
{
    m_pSearchLineEdit = new QLineEdit(topWidget);
    m_pSearchLineEdit->setGeometry(50,5,256,40);
    QPushButton *pSearchButton = new QPushButton();

    pSearchButton->setCursor(Qt::PointingHandCursor);
    pSearchButton->setFixedSize(22, 22);
    pSearchButton->setToolTip(QStringLiteral("搜索"));
    pSearchButton->setStyleSheet("QPushButton{border-image:url("+researchIma+"); background:transparent;} \
                                         QPushButton:hover{border-image:url("+""+")} \
                                         QPushButton:pressed{border-image:url("+""+")}");

    //防止文本框输入内容位于按钮之下
    QMargins margins = m_pSearchLineEdit->textMargins();
    m_pSearchLineEdit->setTextMargins(margins.left(), margins.top(), pSearchButton->width(), margins.bottom());
    m_pSearchLineEdit->setPlaceholderText(QStringLiteral("寻找宝贝 策划"));
    m_pSearchLineEdit->setStyleSheet("QLineEdit{background-color:#FFCCCC;\
                                            selection-color:#663366;selection-background-color:#FFFFFF;\
                                            border:2px groove gray;border-radius:8px;padding:2px 4px;}");

    QHBoxLayout *pSearchLayout = new QHBoxLayout();
    pSearchLayout->addStretch();
    pSearchLayout->addWidget(pSearchButton);
    pSearchLayout->setSpacing(0);
    pSearchLayout->setContentsMargins(0, 0, 0, 0);
    m_pSearchLineEdit->setLayout(pSearchLayout);
}

void MainWindow::changeHome(int flag, bool isClicked)
{
    if(!isClicked)
        goto others;

    switch(flag)
    {
    case 1:
        topWidget->setParent(rootWidget);
        shopWidget->setParent(0);
        perWidget->setParent(0);

        if(detailOfGoods)
            detailOfGoods->setParent(0);
        if(countSuccessed)
            countSuccessed->setParent(0);
        topWidget->show();
        break;
    case 2:
    /*{
        shopWidget=new ShoppingCarWidget(rootWidget);
        connect(shopWidget,SIGNAL(realDisplay(Goods*,bool)),this,SLOT(realDisplayDetail(Goods*,bool)));
        connect(shopWidget,SIGNAL(reload()),this,SLOT(reloadShoppingCar()));
    }*/
        topWidget->setParent(0);
        shopWidget->setParent(rootWidget);
        perWidget->setParent(0);

        if(detailOfGoods)
            detailOfGoods->setParent(0);
        shopWidget->show();
        break;
    case 3:
        topWidget->setParent(0);
        shopWidget->setParent(0);
        perWidget->setParent(rootWidget);

        if(detailOfGoods)
            detailOfGoods->setParent(0);
        if(countSuccessed)
            countSuccessed->setParent(0);
        perWidget->show();
        break;
    default:
        ;
    }

    others:
    ;
}
void MainWindow::realDisplayDetail(Goods *goods, bool isClicked)
{
    if(!isClicked)
        goto others;

    if(detailOfGoods)
    {
        detailOfGoods->~DetailOfGoods();
        detailOfGoods=NULL;
    }

    detailOfGoods=new DetailOfGoods(rootWidget);
    detailOfGoods->setGoods(goods);
    detailOfGoods->newSetParent(rootWidget);
    detailOfGoods->show();

    others:
    ;
}
void MainWindow::reloadShoppingCar()
{
    shopWidget=new ShoppingCarWidget(rootWidget);
    connect(shopWidget,SIGNAL(realDisplay(Goods*,bool)),this,SLOT(realDisplayDetail(Goods*,bool)));
    connect(shopWidget,SIGNAL(reload()),this,SLOT(reloadShoppingCar()));
    connect(this,SIGNAL(addUsersGoods(Goods*)),shopWidget,SLOT(addGoods(Goods*)));
    changeHome(2,true);
}
void MainWindow::countGoodsSuccessed()
{
    countSuccessed=new QWidget(rootWidget);
    shopWidget->displayCountSuccessed();
    countSuccessed->show();
}
void MainWindow::closeWarningWidgwt(int random,bool isClicked)
{
    warningWidget->setVisible(false);
}
void MainWindow::connectWithWarningBox(ImageButton *ok)
{
    warningWidget->setParent(this);
    connect(ok,SIGNAL(clicked(int,bool)),this,SLOT(closeWarningWidgwt(int,bool)));
}
void MainWindow::addGoods(Goods *goods)
{
    emit addUsersGoods(goods);
}
