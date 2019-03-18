#ifndef PERSONALWIDGET_H
#define PERSONALWIDGET_H

#include <QWidget>
#include <QFrame>
#include <imageButton.h>
#include <QLabel>

#include "variable.h"
#include "displayArea.h"

class PersonalWidget : public QFrame
{
    Q_OBJECT
public:
    explicit PersonalWidget(QWidget *parent = 0);
    ~PersonalWidget();

signals:
    void realDisplay(Goods *goods,bool isClicked=true);
public slots:
    void dispayDetailOfGoods(Goods *goods,bool isClicked=true);

private:
    QWidget topColor;

    ImageButton *headPortrait;
    QWidget headPortraitWidget;
    QLabel nickname;
    ImageButton *vip;
    ImageButton *vipIma;
    ImageButton *setting;
    QWidget order;
    QLabel *orderLabel;
    ImageButton *lookMoreOrder;
    QLabel dividLine;
    ImageButton *forRecive;
    ImageButton *forPay;
    ImageButton *forSend;
    ImageButton *froComment;
    ImageButton *refund;

    QWidget mayYouLike;
    ImageButton *mayYouLikeTitleLabel;

    void init();
    void init1();

    QLabel dividLine1;
    DisplayArea *display;
};

#endif // PERSONALWIDGET_H
