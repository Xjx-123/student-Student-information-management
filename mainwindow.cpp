#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include<QSqlDatabase>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,m_ptrStuSql(nullptr)
{
    ui->setupUi(this);

    //显示窗口
    m_dlglogin.show();


    // QSqlDatabase database;
    // database=QSqlDatabase::addDatabase("QSQLITE");
    // database.setDatabaseName("student");


    // if(!database.open())
    // {
    //     qDebug() << "连接失败";
    // }
    // else {
    //     qDebug()<<"连接成功";
    // }

    //????
    auto f=[&]
    {
        this->show();
    };

    //连接槽函数，登录成功后转入主界面
    //函数模板
    //connect(sender, &SenderClass::signalName, receiver, &ReceiverClass::slotName);
    connect(&m_dlglogin,&page_login::SendLoginSeccess,this,f);
    //错误，&传入函数本身，函数后面不可以+（）
    //connect(&m_dlglogin,&page_login::SendLoginSeccess(),this,f);


    //废弃
    // ---------------------------------------------------------------------------
    // ui->treeWidget->clear();
    // //列数
    // ui->treeWidget->setColumnCount(1);
    // // QTreeWidgetItem *tree1 = new QTreeWidgetItem(ui->treeWidget,QStringList(QStringLiteral("树1")));
    // // QTreeWidgetItem *tree1_1 = new QTreeWidgetItem(tree1,QStringList(QStringLiteral("树1_1"))); //子节点1
    // // tree1->addChild(tree1_1); //添加子节点
    // QStringList l;
    // l<<"学生信息管理系统";
    // QTreeWidgetItem *pf=new QTreeWidgetItem(ui->treeWidget,l);
    // // addTopLevelItem()： 添加一个顶层条目；
    // ui->treeWidget->addTopLevelItem(pf);
    // l.clear();
    // l<<"学生管理";
    // //创建子节点
    // QTreeWidgetItem *p1 =new QTreeWidgetItem(pf,l);
    // l.clear();
    // l<<"管理员管理";
    // QTreeWidgetItem *p2 =new QTreeWidgetItem(pf,l);
    // // QTreeWidgetItem *p1=new QTreeWidgetItem(pf,QStringList(QStringLiteral("学生管理")));
    // // QTreeWidgetItem *p1=new QTreeWidgetItem(pf,QStringList(QStringLiteral("管理员管理")));
    // pf->addChild(p1);
    // pf->addChild(p2);
    // ui->treeWidget->expandAll(); //结点全部展开

    // ui->lb_user->setText(use_name.username);

    //默认stackedWidget的page表显示第几页
    ui->stackedWidget->setCurrentIndex(0);
    m_ptrStuSql =StuSql::getinstance();
    // m_ptrStuSql->init();

    m_ptrUserSql =StuSql::getinstance_user();
    updateTab();

}

MainWindow::~MainWindow()
{
    delete ui;
}

// 选择显示的数据表
void MainWindow::switchPage(){
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if(button==ui->Student)
        ui->stackedWidget->setCurrentIndex(0);
    else if(button==ui->User)
        ui->stackedWidget->setCurrentIndex(1);
    // else if(button==ui->pushButton_3)
    //     ui->stackedWidget->setCurrentIndex(2);

    int i = 0;
    ui->stackedWidget->widget(i);
}



void MainWindow::on_btn_exit_clicked()
{
    exit(0);
}



//模拟一组数据
void MainWindow::on_bto_simulation_clicked()
{
    StuInfo info;
    //制作1000条数据
    for(int i=0;i<20;i++)
    {
        if(i%2==0)
        {
            info.name=QString("张%1").arg(i);
            info.age=15;
            info.grade=1;
            info.student_id=20190001+i;
            info.uid_class=248;
            info.phone="p2480000";
            info.wechat="wx2480000";
        }
        else if(i%2==1)
        {
            info.name=QString("李%1").arg(i);
            info.age=17;
            info.grade=5;
            info.student_id=20210001+i;
            info.uid_class=259;
            info.phone="p2590000";
            info.wechat="wx2590000";
        }

        m_ptrStuSql->addStu(info);
    }
    updateTab();

}

// 添加学生
void MainWindow::on_btn_add_clicked()
{
    StuInfo info;
    // m_dlgAddStu.show();
    //show是普通对话框
    //exec--模态对话框，必须有返回值才能结束
    m_dlgAddStu.setType(true, info);
    m_dlgAddStu.exec();
    updateTab();
}
//刷新学生表
void MainWindow::updateTab()
{
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(8);
    //设置列名称
    QStringList l;
    l<<"序号"<<"姓名"<<"年龄"<<"年级"<<"班级"<<"学号"<<"电话"<<"微信";
    ui->tableWidget->setHorizontalHeaderLabels(l);

    //只选中一行，并且不可以直接修改数据
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //显示数据表
    auto cnt=m_ptrStuSql->GetStuCnt();
    //分成一页，显示所有数据
    QList<StuInfo> lStudents=m_ptrStuSql->GetPageStu(0,cnt);
    ui->tableWidget->setRowCount(cnt);
    for(int i=0;i<lStudents.size();i++)
    {
        // 不转成字符串不显示
        //                                                 QString::number(i)--转化成字符串
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(lStudents[i].id)));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(lStudents[i].name));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::number(lStudents[i].age)));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString::number(lStudents[i].grade)));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(QString::number(lStudents[i].uid_class)));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(QString::number(lStudents[i].student_id)));
        ui->tableWidget->setItem(i,6,new QTableWidgetItem(lStudents[i].phone));
        ui->tableWidget->setItem(i,7,new QTableWidgetItem(lStudents[i].wechat));

    }
    //查询学生总数
    ui->lb_cnt->setText(QString("总数:%1").arg(cnt));
}

//清空学生表
void MainWindow::on_btn_clear_clicked()
{
    m_ptrStuSql->clearStuTable();
    updateTab();
}

//删除选中学生
void MainWindow::on_btn_del_clicked()
{
    //选中行
    int i=ui->tableWidget->currentRow();
    if(i>=0)
    {
        //                      item(行，列)
        //  注意                   从第0列开始
        int id=ui->tableWidget->item(i,0)->text().toUInt();

        //经过断点调试
        //发现错误出现在上面选中行的位置
        //行一直为0，无法获取相应行
        qDebug()<<i;
        qDebug()<<id;
        m_ptrStuSql->delStu(id);
        updateTab();
        QMessageBox::information(nullptr,"信息","删除成功");

    }

}

//修改学生表
void MainWindow::on_btn_update_clicked()
{
    StuInfo info;
    int i=ui->tableWidget->currentRow();
    if(i>=0)
    {
        //将选中的值传给变量
        info.id=ui->tableWidget->item(i,0)->text().toUInt();
        info.name=ui->tableWidget->item(i,1)->text();
        info.age=ui->tableWidget->item(i,2)->text().toUInt();
        info.grade=ui->tableWidget->item(i,3)->text().toUInt();
        info.uid_class=ui->tableWidget->item(i,4)->text().toUInt();
        info.student_id=ui->tableWidget->item(i,5)->text().toUInt();
        info.phone=ui->tableWidget->item(i,6)->text();
        info.wechat=ui->tableWidget->item(i,7)->text();
        qDebug()<<i;
        qDebug()<<info.id;

        //这个函数会把表打出来
        m_dlgAddStu.setType(false,info);
        m_dlgAddStu.exec();
        updateTab();
    }

}
//查询
void MainWindow::on_btn_search_clicked()
{
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(8);
    //设置列名称
    QStringList l;
    l<<"序号"<<"姓名"<<"年龄"<<"年级"<<"班级"<<"学号"<<"电话"<<"微信";
    ui->tableWidget->setHorizontalHeaderLabels(l);


    //显示数据表
    auto cnt=m_ptrStuSql->GetStuCnt();
    //分成一页，显示所有数据
    QList<StuInfo> lStudents=m_ptrStuSql->GetPageStu(0,cnt);

    //要搜索的名字中是否含有这个字符
    QString strFilter=ui->le_search->text();
    int index=0;
    for(int i=0;i<lStudents.size();i++)
    {
        //如果不包含搜索字符，继续循环
        if(!lStudents[i].name.contains(strFilter))
        {
            continue;
        }
        // 不转成字符串不显示
        //                                                 QString::number(i)--转化成字符串
        ui->tableWidget->setItem(index,0,new QTableWidgetItem(QString::number(lStudents[i].id)));
        ui->tableWidget->setItem(index,1,new QTableWidgetItem(lStudents[i].name));
        ui->tableWidget->setItem(index,2,new QTableWidgetItem(QString::number(lStudents[i].age)));
        ui->tableWidget->setItem(index,3,new QTableWidgetItem(QString::number(lStudents[i].grade)));
        ui->tableWidget->setItem(index,4,new QTableWidgetItem(QString::number(lStudents[i].uid_class)));
        ui->tableWidget->setItem(index,5,new QTableWidgetItem(QString::number(lStudents[i].student_id)));
        ui->tableWidget->setItem(index,6,new QTableWidgetItem(lStudents[i].phone));
        ui->tableWidget->setItem(index,7,new QTableWidgetItem(lStudents[i].wechat));


        index++;
    }
    //显示行的个数（行数）
    ui->tableWidget->setRowCount(index);
    //查询学生总数
    ui->lb_cnt->setText(QString("总数:%1").arg(index));

}


void MainWindow::on_User_clicked()
{
    switchPage();
    updateTab_User();
}


void MainWindow::on_Student_clicked()
{
    switchPage();
    updateTab();
}
//刷新用户表
void MainWindow::updateTab_User()
{
    ui->UserTable->clear();
    ui->UserTable->setColumnCount(2);
    //设置列名称
    QStringList l;
    l<<"用户名"<<"密码";
    ui->UserTable->setHorizontalHeaderLabels(l);

    //只选中一行，并且不可以直接修改数据
    ui->UserTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->UserTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // //显示数据表
    // auto cnt=m_ptrStuSql->GetStuCnt();
    // //分成一页，显示所有数据
    // QList<StuInfo> lStudents=m_ptrStuSql->GetPageStu(0,cnt);
    QList<UserInfo> lUser  =m_ptrStuSql->getAllUser();
    ui->UserTable->setRowCount(lUser.size());
    for(int i=0;i<lUser.size();i++)
    {
        // 不转成字符串不显示
        //                                                 QString::number(i)--转化成字符串
        ui->UserTable->setItem(i,0,new QTableWidgetItem(lUser[i].username));
        ui->UserTable->setItem(i,1,new QTableWidgetItem(lUser[i].password));
        ui->UserTable->setItem(i,2,new QTableWidgetItem(lUser[i].aut));
    }
        ui->lb_cnt->setText(QString("总数:%1").arg(lUser.size()));
}

// void MainWindow::pass_username(UserInfo info)
// {
//     use_name=info;
// }


//添加用户按钮
void MainWindow::on_btn_adduser_clicked()
{
    UserInfo info;
    // m_dlgAddStu.show();
    //show是普通对话框
    //exec--模态对话框，必须有返回值才能结束
    // m_dlgAddStu.setType(true, info);
    m_AddUser.exec();
    updateTab_User();
}


void MainWindow::on_btn_updateuser_clicked()
{
    UserInfo info;
    int i=ui->UserTable->currentRow();
    if(i>=0)
    {
        //将选中的值传给变量
        info.username=ui->UserTable->item(i,0)->text();
        info.password=ui->UserTable->item(i,1)->text();

        qDebug()<<i;
        qDebug()<<info.username;
        qDebug()<<info.password;
        //调用
        m_UpdateUser.pass(info);
        m_UpdateUser.exec();
        updateTab_User();
    }

}

// 删除用户按钮
void MainWindow::on_btn_deluser_clicked()
{
    //选中行
    int i=ui->UserTable->currentRow();
    if(i>=0)
    {
        //                      item(行，列)
        //  注意                   从第0列开始
        QString Username=ui->UserTable->item(i,0)->text();

        //经过断点调试
        //发现错误出现在上面选中行的位置
        //行一直为0，无法获取相应行
        qDebug()<<i;
        qDebug()<<Username;
        m_ptrUserSql->delUser(Username);
        // m_ptrStuSql->delStu(id);
        updateTab_User();
        QMessageBox::information(nullptr,"信息","删除成功");

    }

}

// 用户表搜索
void MainWindow::on_btn_searchuser_clicked()
{
    ui->UserTable->clear();
    ui->UserTable->setColumnCount(2);
    //设置列名称
    QStringList l;
    l<<"用户名"<<"密码";
    ui->UserTable->setHorizontalHeaderLabels(l);

    QList<UserInfo> luser=m_ptrUserSql->getAllUser();

    //要搜索的名字中是否含有这个字符
    QString strFilter=ui->le_searchuser->text();
    int index=0;
    for(int i=0;i<luser.size();i++)
    {
        //如果不包含搜索字符，继续循环
        if(!luser[i].username.contains(strFilter))
        {
            continue;
        }
        // 不转成字符串不显示
        //                                                 QString::number(i)--转化成字符串
        ui->UserTable->setItem(index,0,new QTableWidgetItem(luser[i].username));
        ui->UserTable->setItem(index,1,new QTableWidgetItem(luser[i].password));
        index++;
    }
    //显示行的个数（行数）
    ui->UserTable->setRowCount(index);
    //查询学生总数
    ui->lb_cnt->setText(QString("总数:%1").arg(index));
}
