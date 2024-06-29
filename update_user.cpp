#include "update_user.h"
#include "ui_update_user.h"
#include"stusql.h"
#include<QMessageBox>
Update_User::Update_User(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Update_User)
{
    ui->setupUi(this);
}

Update_User::~Update_User()
{
    delete ui;
}

void Update_User::pass(UserInfo info)
{
    ui->le_username->setText(info.username);
    ui->le_password->setText(info.password);
    m_info=info;
}

void Update_User::on_save_clicked()
{
    auto ptr=StuSql::getinstance_user();
    m_info.username=ui->le_username->text();
    m_info.password=ui->le_password->text();

    ptr->UpdateUserInfo(m_info);
    QMessageBox::information(nullptr,"信息","修改成功");

    this->hide();
}


void Update_User::on_cancel_clicked()
{
    this->hide();
}

