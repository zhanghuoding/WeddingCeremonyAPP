#ifndef GOODSBAR_H
#define GOODSBAR_H

#include <QWidget>
#include <QFrame>
#include "goods.h"
#include "imageButton.h"
#include "imageButton_1.h"

class GoodsBar : public QFrame
{
    Q_OBJECT
public:
    explicit GoodsBar(Goods goods,int flag=0,QWidget *parent = 0);
    ~GoodsBar();

    QString getGoodsInfo();
    bool whetherSelect();

signals:
    void clicked(Goods *goods,bool isClicked=true);
    void goodsInfoChanged(Goods* goods);
    void sigPrice(float price=0.0,int number=0);
    void addGoodsSignal(Goods *goods);
public slots:
    void changeGoodsInfo(int flag,bool isClicked=true);
    void impleSelectAll(bool select1=false);
    virtual void mousePressEvent ( QMouseEvent * event )Q_DECL_OVERRIDE;
    void addUserGoods(int flag,bool isClicked=true);

private:
    int flag;
    bool isSelect;

    ImageButton* pic;
    ImageButton* title;
    ImageButton* price;
    ImageButton_1* number;
    ImageButton_1* increase;
    ImageButton_1* decrease;
    ImageButton_1* select;

    ImageButton_1* add;

    Goods *goods;
};

#endif // GOODSBAR_H
