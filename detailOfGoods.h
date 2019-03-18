#ifndef DETAILOFGOODS_H
#define DETAILOFGOODS_H

#include <QFrame>
#include <QScrollArea>
#include <QLabel>
#include <QPixmap>
#include "goods.h"

class DetailOfGoods : public QFrame
{
    Q_OBJECT
public:
    explicit DetailOfGoods(QWidget *parent = nullptr);
    ~DetailOfGoods();
    void newSetParent(QWidget *parent=0);
    Goods* getGoods();
    void setGoods(Goods *goods);

signals:

public slots:

private:
    QScrollArea dis;
    Goods *goods;

    void init();
};

#endif // DETAILOFGOODS_H
