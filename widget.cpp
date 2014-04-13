#include "widget.h"
#include "ui_widget.h"
#include "QDesktopWidget"
#include <QMessageBox>
#include <QPixmap>
#include <QPalette>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //读取配置文件
    readConfig();


}

Widget::~Widget()
{
    delete ui;
}


void Widget::readConfig()
{
    // 初始化变量
    initvar();
    /* 读取配置文件 */



}

void Widget::initvar()
{
    firstTimeRender  = 1;
    hasSetPass       = 0;
    isSettingPass    = 0;
    isResettingPass  = 0;
    isUnlocking      = 0;
    isChangingBg     = 0;
    isInputingPassX  = 0;
    hasButtonToClick = 0;
    hasChangePhoto   = 0;
    hasChangeBg      = 0;


    // 获取屏幕大小
    QDesktopWidget* desktopWidget = QApplication::desktop();
    m_winRect = desktopWidget->screenGeometry();
    m_leftWidth = m_winRect.width() * 0.25;
    m_btnWidth  = m_leftWidth * 0.55;
    m_btnHeight  = 30;
    m_beginX    = m_leftWidth * 0.20;

    left_bg = new QPixmap(":/res/left_bg_default.bmp");
    right_bg = new QPixmap(":/res/right_bg_default.jpg");
    photo    = new QPixmap(":/res/photo_default.bmp");
    if(left_bg->isNull())
        QMessageBox::about(this,"warning","left_bg is NULL");

    this->resize(m_winRect.size());
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    //right_widget->resize(m_winRect.width()-m_leftWidth,m_winRect.height());
    //right_widget->setGeometry(m_winRect.width(),0,m_winRect.width(),m_winRect.height());
   // right_widget->show();

}

void Widget::initLeft()
{

    static bool isFirstTime = true;
    if(isFirstTime)
    {
        isFirstTime = false;
        /*  初始化按钮位置 */

        // 设置头像
        ui->photo_btn->setFixedSize(m_btnWidth,m_btnWidth);
        ui->photo_btn->setIconSize(QSize(ui->photo_btn->width(),ui->photo_btn->height()));
        ui->photo_btn->move(m_beginX,60);
        QIcon ico = QIcon(photo->scaled(m_btnWidth,m_btnWidth,Qt::IgnoreAspectRatio));
        ui->photo_btn->setIcon(ico);

        //
        ui->setpass_btn->setFixedSize(m_btnWidth,m_btnHeight);
        ui->setpass_btn->move(m_beginX,60 + ui->photo_btn->height() + 60);

        ui->restart_btn->setFixedSize(m_btnWidth,m_btnHeight);
        ui->restart_btn->move(m_beginX,60 + ui->photo_btn->height() + 60);
        ui->restart_btn->hide();

        //
        ui->ok_btn->setFixedSize(m_btnWidth,m_btnHeight);
        ui->ok_btn->move(m_beginX,60 + ui->photo_btn->height() + 60);
        ui->ok_btn->hide();

        //
        ui->resetpass_btn->move(m_beginX,m_winRect.height() - 60);
        ui->resetbg_btn->move(m_leftWidth - m_beginX - m_btnWidth - ui->resetpass_btn->width()
                              , m_winRect.height() - 60);

        ui->warning_label->move(m_beginX + m_btnWidth/4 ,60 + m_btnWidth + 10 );
        ui->warning_label->hide();


    }

    /* 绘制背景     */


    QPainter painter(this);

    painter.drawPixmap(0,0,m_leftWidth,m_winRect.height(),*left_bg);


}

void Widget::initRight(bool firstTime = true)
{
    static bool isFirstTime = true;
    if(isFirstTime)
    {
        isFirstTime = false;

        QPainter painter(this);
        painter.drawPixmap(m_leftWidth,0,m_winRect.width(),m_winRect.height(),*right_bg);
        return ;
    }
    if(firstTime == false)
    {
        QPainter painter(this);
        painter.drawPixmap(m_leftWidth,0,m_winRect.width(),m_winRect.height(),*right_bg);

        return ;
    }
}

void Widget::saveConfig()
{

}

void Widget::hookKeyBoard()
{

}



void Widget::reStartSetPass()
{

}

void Widget::reStart()
{

}

void Widget::resetPass()
{

}




void Widget::on_photo_btn_clicked()
{

}

void Widget::on_setpass_btn_clicked()
{
    isSettingPass = true;

}

void Widget::on_resetbg_btn_clicked()
{

}

void Widget::on_restart_btn_clicked()
{

}

void Widget::on_resetpass_btn_clicked()
{

}

void Widget::on_ok_btn_clicked()
{

}
void Widget::keyPressEvent(QKeyEvent* e)
{
    if(e->key() == Qt::Key_Escape)
        this ->close();
}

void Widget::mousePressEvent(QMouseEvent* e)
{
    if(hasButtonToClick)    return;

    // 跳到设置密码处理函数
    if(isSettingPass)
    {
        settingPassProcess(e->pos());
        return ;
    }
    // 重设密码
    if(isResettingPass)
    {
        reSetingPassProcess(e->pos());
        return;
    }
    // 改背景
    if(isChangingBg)
    {
        changeBgProcess(e->pos());
        return ;
    }
    // 解锁
    if(isUnlocking)
    {
        unlockingProcess(e->pos());
        return;
    }


}

void Widget::setPass(QPoint *pass)
{
    hasSetPass = true;
}


void Widget::settingPassProcess(QPoint p)
{
    // 第一次输入密码
    if(!isRepeatingPass)
    {
        if(isInputingPassX < 2)
        {
            paintPoint(p);

            isInputingPassX++;
            tmp_password[isInputingPassX] = p;
        }
        else
        {
            paintPoint(p);

            // 第三次点击
            tmp_password[isInputingPassX] = p;
            isRepeatingPass = true;
            isInputingPassX = 0;
        }

    }
    // 第二次确认密码
    else
    {
        if(isInputingPassX < 2)
        {
            paintPoint(p);

            isInputingPassX++;
            tmp_password2[isInputingPassX] = p;
        }
        else
        {
           paintPoint(p);

            // 第三次点击
            tmp_password[isInputingPassX] = p ;
            if(isPassEqual(tmp_password,tmp_password2))
            {
                // 两次密码输入相同 成功设置密码
                setPass(tmp_password);
                // label提示
                hasButtonToClick = true;
                ui->ok_btn->show();
            }
            else
            {
                //两次校验不成功,重新开始
                //label 提示
                hasButtonToClick = true;

            }
            isRepeatingPass = false;
            isInputingPassX = 0;
            isSettingPass = false;
        }
    }

}
void Widget::reSetingPassProcess(QPoint p)
{

    if(isInputingPassX < 2)
    {
        paintPoint(p);
        isInputingPassX++;
        tmp_password[isInputingPassX] = p;
    }
    else
    {
        paintPoint(p);
        // 第三次点击
        tmp_password[isInputingPassX] = p;
        isResettingPass = false;
        isInputingPassX = 0;
        if(isPassEqual(tmp_password,password))
        {
            // 可以重设密码
        }
        else
        {
            // 提示错误
        }
    }
}

void Widget::changeBg()
{

}

void Widget::changeBgProcess(QPoint p)
{

    if(isInputingPassX < 2)
    {
        paintPoint(p);
        isInputingPassX++;
        tmp_password[isInputingPassX] = p;
    }
    else
    {
        paintPoint(p);
        // 第三次点击
        tmp_password[isInputingPassX] = p;
        isChangingBg = false;
        isInputingPassX = 0;
        if(isPassEqual(tmp_password,password))
        {
            // 可以修改图片
        }
        else
        {
            // 提示错误
        }
    }
}

void Widget::unlockingProcess(QPoint p)
{

}

bool Widget::isPassEqual(QPoint *pass1, QPoint *pass2)
{

}
void Widget::paintEvent(QPaintEvent* e)
{
        // 第一次渲染
        initLeft();
        initRight(true);



}
void Widget::paintPoint(QPoint p, bool instantClean)
{

}

