#ifndef VARIABLE
#define VARIABLE

#include <QString>
#include <QSize>
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QLineEdit>
#include <QStackedWidget>
#include <QMap>

extern QString appWorkPath;

extern QChar Symb1;
extern QChar Symb2;

extern QStackedWidget *stackedWidget;

extern QString picRootPath;//图片资源的根目录
extern QString resourceRootPath;//资源文件的根目录

extern QString goodsRecordFilePath;
extern QFile goodsRecordFile;

extern QSize *screenSize;//设备的屏幕尺寸
extern QSize *windowSize;//窗口尺寸

extern QString locateIma;
extern QString scanIma;
extern QString homeIma;
extern QString personalIma;
extern QString shopping_carIma;
extern QString informationima;
extern QString friendsIma;
extern QString dateIma;
extern QString settingIma;
extern QString researchIma;

extern QLineEdit* m_pSearchLineEdit;

extern QString userListTxt;
extern QFile userListFile;
extern QMap<QString,QString> users;

extern QString currentUser;

extern void networkStateWarning(QString title,QString content);
extern QWidget *countSuccessed;

extern QWidget *warningWidget;

#endif // VARIABLE

