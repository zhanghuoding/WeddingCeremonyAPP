#include "goods.h"

Goods::Goods()
{
    no="---";
    price=0.0;
    number=0;
    isSelect=false;
}
Goods::Goods(QString no, QString title, float price, QString picPath, QString samplePicName, QString introducePic, int number)
{
    setInfo(no,title,price,picPath,samplePicName,introducePic,number);
}
Goods::Goods(QString str)
{
    setInfo(str);
}
/*Goods::Goods(const Goods& goods)
{
    setInfo(goods.toString());
}*/
Goods::~Goods()
{
    no="---";
    price=0.0;
    number=0;
}
Goods* Goods::setInfo(QString no, QString title, float price, QString picPath, QString samplePicName, QString introducePic, int number)
{
    this->no=no.toStdString().c_str();
    this->title=title.toStdString().c_str();
    this->price=price;
    this->picPath=picPath.toStdString().c_str();
    this->samplePicName=samplePicName.toStdString().c_str();
    this->introducePic=introducePic.toStdString().c_str();
    this->number=number;

    setSamplePic(this->samplePicName);
    setDisPic(this->introducePic);

    return this;
}
Goods* Goods::setInfo(QString str)
{
    if(str.length()<=10)
    {
        qDebug()<<"Sorry! This parameter is illegal!";
        return this;
    }
    int start=0;
    int trail=0;
    trail=str.indexOf(Symb1,start);
    QString TEMno=str.mid(start,trail-start).toStdString().c_str();

    if(trail==-1)
    {
        qDebug()<<"Sorry! This parameter is illegal!";
        return this;
    }
    start=trail+1;
    trail=str.indexOf(Symb1,start);
    QString TEMtitle=str.mid(start,trail-start).toStdString().c_str();

    if(trail==-1)
    {
        qDebug()<<"Sorry! This parameter is illegal!";
        return this;
    }
    start=trail+1;
    trail=str.indexOf(Symb1,start);
    float TEMprice=str.mid(start,trail-start).toFloat();

    if(trail==-1)
    {
        qDebug()<<"Sorry! This parameter is illegal!";
        return this;
    }
    start=trail+1;
    trail=str.indexOf(Symb1,start);
    QString TEMpicPath=str.mid(start,trail-start).toStdString().c_str();

    if(trail==-1)
    {
        qDebug()<<"Sorry! This parameter is illegal!";
        return this;
    }
    start=trail+1;
    trail=str.indexOf(Symb1,start);
    QString TEMsamplePicName=str.mid(start,trail-start).toStdString().c_str();

    if(trail==-1)
    {
        qDebug()<<"Sorry! This parameter is illegal!";
        return this;
    }
    start=trail+1;
    trail=str.indexOf(Symb1,start);
    QString TEMintroducePic;
    if(trail==-1)
    {
        TEMintroducePic=str.mid(start,str.length()-start).toStdString().c_str();
        return setInfo(TEMno,TEMtitle,TEMprice,TEMpicPath,TEMsamplePicName,TEMintroducePic);
    }else
    {
        TEMintroducePic=str.mid(start,trail-start).toStdString().c_str();
    }

    start=trail+1;
    trail=str.indexOf(Symb1,start);
    int TEMnumber=str.mid(start,str.length()-start).toInt();

    return setInfo(TEMno,TEMtitle,TEMprice,TEMpicPath,TEMsamplePicName,TEMintroducePic,TEMnumber);
}

Goods* Goods::setIntroducePic(QString introducePic)
{
    this->introducePic=introducePic.toStdString().c_str();
    setDisPic(this->introducePic);
    return this;
}
Goods* Goods::setNo(QString no)
{
    this->no=no.toStdString().c_str();
    return this;
}
Goods* Goods::setNumber(int number)
{
    this->number=number;
    return this;
}
Goods* Goods::setPicPath(QString picPath)
{
    this->picPath=picPath.toStdString().c_str();
    return this;
}
Goods* Goods::setPrice(float price)
{
    this->price=price;
    return this;
}
Goods* Goods::setSamplePicName(QString samplePicName)
{
    this->samplePicName=samplePicName.toStdString().c_str();
    setSamplePic(samplePicName);
    return this;
}
Goods* Goods::setTitle(QString title)
{
    this->title=title.toStdString().c_str();
    return this;
}
QString Goods::toString()
{
    QString str="";
    str.append(no+"#").append(title+"#").append(QString::number(price)+"#").append(picPath+"#").append(samplePicName+"#").append(introducePic+"#").append(QString::number(number));
    return str;
}
QString Goods::toString(Goods goods)
{
    return goods.toString();
}
void Goods::setDisPic(QString str)
{
    int start=0;
    int trail=-1;
    while(str.length()-start>4)
    {
        start=trail+1;
        trail=str.indexOf(Symb2,start);
        if(trail!=-1)
        {
            disPic.append(picPath+"/"+str.mid(start,trail-start));
        }else
        {
            disPic.append(picPath+"/"+str.mid(start,str.length()-start));
            break;
        }
    }
}
void Goods::setSamplePic(QString str)
{
    samplePic=picRootPath+picPath+"/"+str;
}
QVector<QString> *Goods::getdisPic()
{
    return &disPic;
}
bool Goods::whetherSelected()
{
    return isSelect;
}








