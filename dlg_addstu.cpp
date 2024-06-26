#include "dlg_addstu.h"
#include "ui_dlg_addstu.h"
#include"stusql.h"
#include<QMessageBox>
Dlg_AddStu::Dlg_AddStu(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dlg_AddStu)
{
    ui->setupUi(this);
}

Dlg_AddStu::~Dlg_AddStu()
{
    delete ui;
}

void Dlg_AddStu::setType(bool isAdd,StuInfo info)
{
    m_isAdd=isAdd;


    //setText 和 setValue有什么不同?
    // ui->
    ui->le_name->setText(info.name);
    ui->sb_age->setValue(info.age);
    ui->le_grade->setText(QString::number(info.grade));
    ui->le_class->setText(QString::number(info.uid_class));
    ui->le_seq->setText(QString::number(info.student_id));
    ui->le_phone->setText(info.phone);
    ui->le_wechat->setText(info.wechat);
    // ui->le_grade->setText(QString::number(info.uid_class));

    //注意
    m_info=info;
}



void Dlg_AddStu::on_btn_cancel_clicked()
{
    this->hide();
}


void Dlg_AddStu::on_btn_save_clicked()
{
    StuInfo info;
    //显示信息
    auto ptr=StuSql::getinstance();
    info.name=ui->le_name->text();
    info.age=ui->sb_age->text().toUInt();
    info.grade=ui->le_grade->text().toUInt();
    info.uid_class=ui->le_class->text().toUInt();
    info.student_id=ui->le_seq->text().toUInt();
    info.phone=ui->le_phone->text();
    info.wechat=ui->le_wechat->text();

    if(m_isAdd)
    {
        ptr->addStu(info);
        QMessageBox::information(nullptr,"信息","存储成功");
    }
    else
    {
        info.id=m_info.id;
        // ptr->UpdateStuInfo(info);
        bool l= ptr->UpdateStuInfo(info);
        qDebug()<<l;
        if(l)
        {
            QMessageBox::information(nullptr,"信息","修改成功");

        }
        else
        {
            QMessageBox::information(nullptr,"信息","修改失败");
        }
        // info.id=info.id;
        // ptr->UpdateStuInfo(info);
    }
    // ptr->addStu(info);
    // bool judge=ptr->addStu(info);
    //注意要小写information
    // QMessageBox::information(nullptr,"信息","存储成功");
    this->hide();
}

