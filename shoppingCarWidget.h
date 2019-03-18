#ifndef SHOPPINGCARWIDGET_H
#define SHOPPINGCARWIDGET_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QScrollArea>
#include "variable.h"
#include "goods.h"
#include "goodsBar.h"
#include "displayArea.h"

class ShoppingCarWidget : public QFrame
{
    Q_OBJECT
public:
    explicit ShoppingCarWidget(QWidget *parent = 0);
    ~ShoppingCarWidget();
    void displayCountSuccessed();

signals:
    void realDisplay(Goods *goods,bool isClicked=true);
    void reload();
    void selectAllSignal(bool select1=false,int number=0);
    void countGoodsSuccessed();
public slots:
    void realDisplayDetailInfo(Goods *goods,bool isClicked=true);
    void changeUsersGoods(Goods *goods);
    void deleteUserGoods(int flag,bool isClicked=true);
    void sendSelectSignal(int random=0,bool isClicked=true);
    void computPrice_Number(float price=0.0,int number=0);
    void countGoods(int random,bool isClicked=true);
    void addGoods(Goods *goods);
private:
    QLabel title;
    QLabel empt;
    void init();

    bool isSelectAll;

    QVector<GoodsBar*> userGoods;
    QScrollArea scrollArea;
    QWidget centerWidget;

    QWidget processBar;
    ImageButton *selectALLIm;
    ImageButton *selectALL;
    ImageButton *deleteAll;
    ImageButton *total;
    ImageButton *totalWorth;
    ImageButton *settlement;

    DisplayArea *seeAgain;

    QWidget mayYouLike;
    ImageButton *mayYouLikeTitleLabel;
    QLabel dividLine1;

    float worth;
    int goodsNumber;
    void afterCount();
};

#endif // SHOPPINGCARWIDGET_H
