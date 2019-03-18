#ifndef DISPLAYAREA_H
#define DISPLAYAREA_H

#include <QWidget>
#include <QFrame>
#include <QScrollArea>
#include "variable.h"
#include "goodsBar.h"
#include "type.h"

class DisplayArea : public QFrame
{
    Q_OBJECT
public:
    explicit DisplayArea(QWidget *parent = 0);
    ~DisplayArea();

signals:
    void realDisplay(Goods *goods,bool isClicked=true);
    void addUserGoodsArea(Goods *goods);
public slots:
    void dispayDetailOfGoods(Goods *goods,bool isClicked=true);
    void addGoods(Goods *goods);
private:
    QVector<GoodsBar*> allGoods;
    QVector<QLabel*> allImages;

    void init();
    QScrollArea scrollArea;
};

#endif // DISPLAYAREA_H
