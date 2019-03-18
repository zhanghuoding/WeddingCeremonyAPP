#include "bottomBar.h"

BottomBar::BottomBar(QWidget *parent) : QWidget(parent)
{
    this->setGeometry(2,parent->height()-50,parent->width()-4,48);
    this->resize(parent->width()-4,48);
    this->setStyleSheet("background-color:#d4137c;");
}
