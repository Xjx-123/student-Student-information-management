#include "page_login.h"
#include "ui_page_login.h"
#include"stusql.h"
// #include"mainwindow.h"
#include <QMessageBox>

page_login::page_login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::page_login)
{
    ui->setupUi(this);
    m_ptrStuSqllojin =StuSql::getinstance();
}

page_login::~page_login()
{
    delete ui;
}
// 登录
void page_login::on_btn_login_clicked()
{
    //数据库查找用户名和密码
    UserInfo info;
    info.username=ui->le_UesrName->text();
    info.password=ui->le_Password->text();
    qDebug()<<info.username;
    qDebug()<<info.password;
    bool pan =m_ptrStuSqllojin->isExist(info);
    qDebug()<<pan;
    if(pan==1)
    {
        emit SendLoginSeccess();
        // m_.setType(false,info);
        this->hide();
    }
    //失败提示
    else
    {
        QMessageBox::information(nullptr,"信息","用户名或密码错误");
    }
    // 成功进入主界面
    // emit 发射一个信号
            // // 测试用
            // emit SendLoginSeccess();
            // this->hide();

}

//退出
void page_login::on_btn_exit_clicked()
{
    //退出窗口
    exit(0);
}

