#ifndef GOODS_H
#define GOODS_H

#include <QString>
#include "variable.h"

class GoodsBar;

class Goods
{
    friend GoodsBar;
public:
    Goods();
    Goods(QString no,QString title,float price,QString picPath,QString samplePicName,QString introducePic,int number=1);
    Goods(QString str);
    //Goods(const Goods& goods);
    ~Goods();

    QString toString();
    QString toString(Goods goods);

    Goods* setInfo(QString no,QString title,float price,QString picPath,QString samplePicName,QString introducePic,int number=1);
    Goods* setInfo(QString str);
    Goods* setNumber(int number);
    Goods* setNo(QString no);
    Goods* setTitle(QString);
    Goods* setPrice(float price);
    Goods* setPicPath(QString picPath);
    Goods* setSamplePicName(QString samplePicName);
    Goods* setIntroducePic(QString introducePic);

    QVector<QString> *getdisPic();
    bool whetherSelected();

private:
    int number;
    bool isSelect;
    QString no;
    QString title;
    float price;
    QString picPath;
    QString samplePicName;
    QString introducePic;

    QString samplePic;

    QVector<QString> disPic;
    void setDisPic(QString str);
    void setSamplePic(QString str);
};

#endif // GOODS_H
