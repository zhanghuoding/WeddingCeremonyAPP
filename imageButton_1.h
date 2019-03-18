#ifndef IMAGEBUTTON_1_H
#define IMAGEBUTTON_1_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include "variable.h"
#include "type.h"

class ImageButton_1 : public QLabel
{
    Q_OBJECT
public:
    explicit ImageButton_1(QString imagePath,int flag=0,QWidget *parent = 0);
    ~ImageButton_1();

signals:
    void clicked(int flag,bool isClicked=true);
public slots:
    virtual void mousePressEvent ( QMouseEvent * event )Q_DECL_OVERRIDE;
private:
    int flag;
};

#endif // IMAGEBUTTON_1_H
