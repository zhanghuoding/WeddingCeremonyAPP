#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include "variable.h"
#include "imageButton.h"
#include "displayArea.h"
#include "shoppingCarWidget.h"
#include "personalWidget.h"
#include "imageButton.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void connectWithWarningBox(ImageButton *ok);
private:
    QWidget *rootWidget;
    QWidget *topWidget;
    QWidget *bottom;

    ShoppingCarWidget *shopWidget;
    PersonalWidget *perWidget;

    ImageButton *locateButton;
    ImageButton *scanButton;
    ImageButton *homeButton;
    ImageButton *shopping_carButton;
    ImageButton *personalButton;

    DisplayArea *displayArea;

    void init();
    void creatSearchBox();

public slots:
    void changeHome(int flag,bool isClicked=true);
    void realDisplayDetail(Goods *goods,bool isClicked=true);
    void reloadShoppingCar();
    void countGoodsSuccessed();
    void closeWarningWidgwt(int random=0,bool isClicked=true);
    void addGoods(Goods* goods);
signals:
    void addUsersGoods(Goods* goods);
};

#endif // MAINWINDOW_H
