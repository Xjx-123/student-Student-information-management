#include "add_user.h"
#include "ui_add_user.h"
#include"stusql.h"
#include<QMessageBox>
add_User::add_User(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::add_User)
{
    ui->setupUi(this);
}

add_User::~add_User()
{
    delete ui;
}

void add_User::on_btn_save_clicked()
{
    UserInfo info;
    //显示信息
    auto ptr=StuSql::getinstance_user();
    info.username=ui->le_UserName->text();
    info.password=ui->le_Password->text();



    ptr->addUser(info);
        QMessageBox::information(nullptr,"信息","存储成功");



    // ptr->addUser(info);
    // bool judge=ptr->addStu(info);
    //注意要小写information
    // QMessageBox::information(nullptr,"信息","存储成功");
    this->hide();
}


void add_User::on_btn_cancel_clicked()
{
    this->hide();
}

