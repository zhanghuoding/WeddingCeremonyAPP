#include "mainwindow.h"
#include "variable.h"
#include "tool.h"
#include "type.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDir>
#include <QCoreApplication>
#include <QTextStream>

QString appWorkPath("/mnt/Work/Programs/WeddingCeremonyAPP/WeddingCeremonyAPP/");
QChar Symb1='#';
QChar Symb2=';';

QStackedWidget *stackedWidget;

QString picRootPath("ico/");
QString resourceRootPath("../WeddingCeremonyAPP/resource/");
QString goodsRecordFilePath(resourceRootPath+"goods.txt");
QString userListTxt(resourceRootPath+"user.txt");
QFile userListFile(userListTxt);
QMap<QString,QString> users;
QFile outFile("log.log");//log file
QFile goodsRecordFile(goodsRecordFilePath);

QString currentUser("zhanghuoding");

QSize *screenSize;
QSize *windowSize;

QString locateIma=resourceRootPath+picRootPath+"locate.ico";
QString scanIma=resourceRootPath+picRootPath+"scan.ico";
QString homeIma=resourceRootPath+picRootPath+"home.ico";
QString personalIma=resourceRootPath+picRootPath+"personal.ico";
QString shopping_carIma=resourceRootPath+picRootPath+"shopping_car.ico";
QString informationima=resourceRootPath+picRootPath+"information.ico";
QString friendsIma=resourceRootPath+picRootPath+"friends.ico";
QString dateIma=resourceRootPath+picRootPath+"date.ico";
QString settingIma=resourceRootPath+picRootPath+"setting.ico";
QString researchIma=resourceRootPath+picRootPath+"research.ico";

QLineEdit* m_pSearchLineEdit;

QWidget *countSuccessed=NULL;

QVector<Goods> goodsList;

DetailOfGoods *detailOfGoods=NULL;

QWidget *warningWidget;
QLabel *warningWidgetTitle;
QLabel *dividLine;
QLabel *warningContent;
ImageButton *ok;

void init();
void initWarningBox();
void loadResource();
void networkStateWarning(QString title,QString content);
void customMessageHandler(QtMsgType type, const QMessageLogContext& Context, const QString &sMsg);

int main(int argc, char *argv[])
{
    //QApplication::addLibraryPath("./plugins");
    QDir::setCurrent(appWorkPath);
    QApplication a(argc, argv);
    init();
    MainWindow w;
    w.show();
    initWarningBox();
    w.connectWithWarningBox(ok);

    return a.exec();
}
void init()
{
    stackedWidget=new QStackedWidget;

    if(outFile.exists())
        outFile.remove();
    /////////////////////////qInstallMessageHandler(customMessageHandler);//注册日志处理回调函数
    //qDebug()<<"当前的图片资源路径是 "<<picRootPath<<"\t现在是void init()";
    //qDebug()<<"当前的数据资源路径是 "<<resourceRootPath<<"\t现在是void init()";
    //idiom=new Idiom;//初始化成语链表的对象
    int width=QApplication::desktop()->width();
    int height=QApplication::desktop()->height();

    loadResource();

    windowSize=new QSize(360,640);
    screenSize=new QSize(windowSize->width(),windowSize->height());//初始化屏幕尺寸记录变量
}
void customMessageHandler(QtMsgType type, const QMessageLogContext& Context, const QString &sMsg)
{
    QString txt;
    switch (type)
    {//调试信息提示
    case QtDebugMsg:
        txt = QString("Debug: %1").arg(sMsg);
        break;
        //一般的warning提示
    case QtWarningMsg:
        txt = QString("Warning: %1").arg(sMsg);
        break;
        //严重错误提示
    case QtCriticalMsg:
        txt = QString("Critical: %1").arg(sMsg);
        break;
        //致命错误提示
    case QtFatalMsg:
        txt = QString("Fatal: %1").arg(sMsg);
        abort();
    }
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << "\r\n" << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd") <<'\t' << txt << endl;
}
void loadResource()
{
    if(!goodsRecordFile.exists())
    {
        networkStateWarning(QObject::tr("网络连接提示："),QObject::tr("对不起，服务器跑丢啦！"));
    }
    if(!goodsRecordFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"警告：goods.txt文件打开失败！";
    }
    QString temp;
    QTextStream in(&goodsRecordFile);

    while(!in.atEnd())
    {
        temp=in.readLine();
        goodsList.append(Goods(temp));
    }

    goodsRecordFile.close();

    if(!userListFile.exists())
    {
        networkStateWarning(QObject::tr("网络连接提示："),QObject::tr("对不起，服务器跑丢啦！"));
    }
    if(!userListFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"警告：user.txt文件打开失败！";
    }
    QString temp1;
    QString temp2;
    QTextStream in1(&userListFile);
    int start=-1,trail=-1;

    while(!in1.atEnd())
    {
        temp=in1.readLine();
        trail=temp.indexOf('#',0);
        start=temp.lastIndexOf('#',temp.length()-1);
        temp1.clear();
        temp2.clear();
        temp1=temp.mid(0,trail).toStdString().c_str();
        temp2=temp.mid(start+1,temp.length()-start-1).toStdString().c_str();
        users.insert(temp1,temp2);
    }

    userListFile.close();

}
void networkStateWarning(QString title,QString content)
{
    //QMessageBox::warning(0,QObject::tr(title.toStdString().c_str()),QObject::tr(content.toStdString().c_str()),QMessageBox::Ok);
    warningWidgetTitle->setText(title);
    warningContent->setText(content);
    warningWidget->setVisible(true);
}
void initWarningBox()
{
    //mayYouLike.setParent(this);
    warningWidget=new QWidget();
    //warningWidget->setStyleSheet("background-color:#f8bebe;border-radius:5px;border:1px solid #000000;");
    warningWidget->setStyleSheet("background-color:#35f3ec;border-radius:5px;");
    warningWidget->setGeometry(30,180,300,170);
    warningWidgetTitle=new QLabel(warningWidget);
    //warningWidgetTitle->setText("猜你喜欢");
    warningWidgetTitle->setFont(QFont("Timers" , 16 ,  QFont::Bold));
    warningWidgetTitle->setStyleSheet("background-color:transparent;color:#ff0000");
    warningWidgetTitle->setGeometry(10,2,200,40);
    warningWidgetTitle->setWordWrap(true);
    dividLine=new QLabel(warningWidget);
    dividLine->setText("---------------------------------------------------------------------------------------------");
    dividLine->setFont(QFont("Timers" , 10 ,  QFont::DemiBold));
    dividLine->setStyleSheet("background-color:transparent;color:#a49898");
    dividLine->setGeometry(0,40,dividLine->parentWidget()->width(),3);
    warningContent=new QLabel(warningWidget);
    warningContent->setFont(QFont("Timers" , 14 ,  QFont::Bold));
    warningContent->setStyleSheet("background-color:transparent;color:#000000");
    warningContent->setGeometry(10,30,270,80);
    warningContent->setWordWrap(true);

    ok=new ImageButton("",0,warningWidget);
    ok->setStyleSheet("QLabel{background-color:#f41c96;color:#000000;border-radius:8px;}");
    ok->setFont(QFont("Timers" , 14 ,  QFont::Bold));
    ok->setGeometry(200,115,75,40);
    ok->setText("知道了");
    ok->setAlignment(Qt::AlignCenter);
}
