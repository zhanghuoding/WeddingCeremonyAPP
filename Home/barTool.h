#ifndef BARTOOL_H
#define BARTOOL_H

#include <QWidget>

#include "type.h"

class BarTool : public QWidget
{
    Q_OBJECT
public:
    explicit BarTool(QWidget *parent = 0);
    ~BarTool();
    /*void setText(QString text);
    void setText(charPtr text);
    void setStyShe(QString sheet);
    ClickLabel *getLabelAt(int index);*/
private:
   //ClickLabel *labels[4];
signals:
    //void clickedNum(int flag=-1);
public slots:
    void sendSignal(QString name,bool click=true);
};
#endif // BARTOOL_H
