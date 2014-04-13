#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPoint>
#include <QMouseEvent>
#include <QPixmap>
#include <QPainter>
#include <QKeyEvent>
#include <QIcon>

struct QPoint3
{
    QPoint  point1;
    QPoint  point2;
    QPoint  point3;
    QPoint3():point1(QPoint(-1,-1)),point2(point1),point3(point1){}

};
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
public:

    void paintEvent(QPaintEvent* e);   //重写 Qwidget 重绘处理

    void keyPressEvent(QKeyEvent* e);

    void readConfig();                 // 获取配置文件
    void initvar() ;                  //初始化变量
    void initLeft() ;                //初始化左边背景栏
    void initRight(bool firstTime) ;               // 初始化右边背景
    void saveConfig()  ;                           // 更新配置文件

    void hookKeyBoard() ;                        // 勾住键盘
    void mousePressEvent(QMouseEvent* e) ;       //重写鼠标按键处理
    void setPass(QPoint* pass);
    void settingPassProcess(QPoint p);
    void reStartSetPass();

    void reStart();
    void resetPass();
    void reSetingPassProcess(QPoint p);
    void changeBg();
    void changeBgProcess(QPoint p);
    void unlockingProcess(QPoint p);
    bool isPassEqual(QPoint* pass1,QPoint* pass2);
    void paintPoint(QPoint p,bool instantClean = true);//画圈 , 立刻清除

private slots:
    void on_photo_btn_clicked();

    void on_setpass_btn_clicked();

    void on_resetbg_btn_clicked();

    void on_restart_btn_clicked();

    void on_resetpass_btn_clicked();

    void on_ok_btn_clicked();

private:


    QPoint  password[3];        // 储存密码
    QPoint  tmp_password[3];    //
    QPoint  tmp_password2[3];
    QRect   m_winRect;          // 屏幕大小
    bool    firstTimeRender;    // 第一次渲染
    int     m_leftWidth;        // 左边栏的宽度
    int     m_btnWidth;         // 按钮长度
    int     m_btnHeight;
    int     m_beginX;           // 按钮起始x坐标
    bool    hasChangePhoto;     // 更换过头像
    bool    hasChangeBg;        // 更换过背景

    bool    hasSetPass;         // 是否设置过密码
    bool    hasButtonToClick;   // 应答完按钮才可以继续操作

    int     isInputingPassX;    // 正在输入第X个密码

    bool    isSettingPass;      // 正在设置密码
    bool    isRepeatingPass;    // 第二次检验密码
    bool    isUnlocking;        // 正在解锁
    bool    isResettingPass;    // 正在重设密码
    bool    isChangingBg;       // 正在重设背景






    QPixmap* left_bg;
    QPixmap* right_bg;
    QPixmap* photo;
    QPoint   m_point;
    QWidget* right_widget;

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
