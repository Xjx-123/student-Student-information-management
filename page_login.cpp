#include "page_login.h"
#include "ui_page_login.h"

#include <QMessageBox>

page_login::page_login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::page_login)
{
    ui->setupUi(this);
}

page_login::~page_login()
{
    delete ui;
}
// 登录
void page_login::on_btn_login_clicked()
{
    //数据库查找用户名和密码
//     //应付版本
//     QString l1=ui->le_UesrName->text();
//     QString l2=ui->le_Password->text();
//     // if(ui->le_UesrName->text()=="admin"&&ui->le_Password->text()=="123")
//     if(l1=="admin"&&l2=="123")
//     {
//         emit SendLoginSeccess();
//         this->hide();
//     }
//     //失败提示
// else
//     {
//         QMessageBox::information(nullptr,"信息","用户名或密码错误");
//     }
//     //成功进入主界面
//     //emit 发射一个信号
            emit SendLoginSeccess();
            this->hide();

}

//退出
void page_login::on_btn_exit_clicked()
{
    //退出窗口
    exit(0);
}

