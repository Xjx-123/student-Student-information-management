#include "stusql.h"
#include<QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>\
// #include<QtDebug>
#include<QDebug>
#include<QCoreApplication>
//继承Sobject类

//单例
StuSql *StuSql::ptrstuSql=nullptr;



StuSql::StuSql(QObject *parent)
    : QObject{parent}
{
    //连接数据库的一种方式
    // QSqlDatabase database;
    // database=QSqlDatabase::addDatabase("QSQLITE");
    // database.setDatabaseName("student");
    // //database.addDatabase("INSERT INTO "student" VALUES
    //             // (NULL, '张三', 12, 3, 2, 1, 15940224444, 'asdzhang');")
    // if(!database.open())
    // {
    //     qDebug() << "No!";
    // }
    // else {
    //     qDebug()<<"Yes!";
    // }

//初始化，连接数据库
    init();
    // q.exec("INSERT INTO student VALUES (135, '张三', 12, 3, 2, 1, 15940224444, 'asdzhang')");

    //测试
    // 添加学生信息--Yes---添加用户信息
    // StuInfo s;
    // s.name="小王";
    // for(int i=0;i<10;i++)
    // {
    //     addStu(s);
    // }

    //清空学生表--Yes
    qDebug()<<GetStuCnt();
    // qDebug()<<clearStuTable();

    // 查询学生总数--Yes
    // qDebug()<<GetStuCnt();

    // （分页获取）获取第二页，一页三个--Yes
    // GetPageStu(2,3);

    // 删除学生信息---YEs
    // delStu(254);

    //修改信息--Yes
    //后期调试无问题，重新寻找修改信息的问题
    // StuInfo s;
    // s.id=7292;
    // s.name="老王";
    // UpdateStuInfo(s);

    //------------
    //用户调试--Yes
    // UserInfo info;
    // info.username="boss";
    // info.password="666";
    // info.aut="admin";
    // addUser(info);
    // addUser(info);
    // qDebug()<<isExist("boss");
    // auto l=getAllUser();
    // info.password="777";
    // UpdateUserInfo(info);
    // delUser("boss");

}
//连接数据库
void StuSql::init()
{
    if (QSqlDatabase::drivers( ).isEmpty ())
    {
        qDebug()<<"No database drivers found";
    }
        // QMessageBox::information(nullptr, tr("No database drivers found"),
        //                          tr ("This demo requires at least one Qt database driver. "
        //                             "Please check the documentation how to build the "
        //                             "Qt soL plugins. " )) ;

    m_db    = QSqlDatabase:: addDatabase ( "QSQLITE");

    //获得的目录路径是可执行文件所在目录，默认情况下，可执行文件是生成在
    //build-mytest-Desktop_Qt_5_10_1_GCC_64bit-Debug 这种形式的文件下的，
    //将“data.db”放到没加data的str地址下
    // auto str = QCoreApplication::applicationDirPath() ;
    // str+="data.db";
    // qDebug()<<str;
    m_db.setDatabaseName("C:\\Users\\xiao\\Desktop\\data.db");
    if (!m_db.open())
    {
        qDebug()<<"data not open";

    }
}



// QSqlQuery exec(const QString &query = QString()) const
//     在数据库上执行一条SQL语句，并返回一个QSqlQuery对象，使用lastError()检索错误信息，如果查询为空，将返回一个空的无效查询，并且lastError()不受影响

//查询学生总数
quint32 StuSql::GetStuCnt()
{
    QSqlQuery sql(m_db);
    sql.exec("select count(id) from student;");
    quint32 uiCnt=0;
    while(sql.next())
    {
        //??????
        uiCnt=sql.value(0).toUInt();
    }
    return uiCnt;
}
//对数据分页(页数，每页有多少数据)
QList<StuInfo> StuSql::GetPageStu(quint32 page, quint32 uiCnt)
{
    QList<StuInfo> l;
    QSqlQuery sql(m_db);
    QString strql= QString("select * from student order by id limit %1 offset %2").
                    arg(uiCnt).arg(page *uiCnt);
    sql.exec(strql);
    StuInfo info;
    while(sql.next())
    {
        info.id=sql.value(0).toUInt();
        info.name=sql.value(1).toString();
        info.age=sql.value(2).toUInt();
        info.grade=sql.value(3).toUInt();
        info.uid_class=sql.value(4).toUInt();
        info.student_id=sql.value(5).toUInt();
        info.phone=sql.value(6).toString();
        info.wechat=sql.value(7).toString();
        //存放到表中
        l.push_back(info);
    }
    return l;
}
//增加学生信息
void StuSql::addStu(StuInfo info)
{
    QSqlQuery sql(m_db);
    QString strsql=QString("insert into student values(null,'%1',%2,%3,%4,%5,'%6','%7')").
                     arg(info.name).arg(info.age).
                     arg(info.grade).arg(info.uid_class).
                     arg(info.student_id).arg(info.phone).
                     arg(info.wechat);
    //是否添加成功
    qDebug()<<sql.exec(strsql);
}
//删除
bool StuSql::delStu(int id)
{
    QSqlQuery sql(m_db);
    // sql.exec(QString("delete from student where id=%1").arg(id));

    return sql.exec(QString("delete from student where id=%1").arg(id));
}
//清空表
bool StuSql::clearStuTable()
{
    QSqlQuery sql(m_db);
    sql.exec("delete from student");
    //自增表没有归0，需要后期找问题
    //！！！
    // ！！！
    return sql.exec("delete from sqlite_sequence WHERE name = ‘student’");

}
//修改
bool StuSql::UpdateStuInfo(StuInfo info)
{
    QSqlQuery sql(m_db);
    // /*update student set name = 'asd' where id=25*/;
    QString strsql=QString("update student set name = '%1',age=%2,grade=%3,"
                             "class=%4,studentid=%5,phone='%6',"
                             "wechat='%7' where id=%8").
                        arg(info.name).arg(info.age).arg(info.grade).
                        arg(info.uid_class).arg(info.student_id).
                     arg(info.phone).arg(info.wechat).arg(info.id);

    //是否修改成功s
    return sql.exec(strsql);
}

QList<UserInfo> StuSql::getAllUser()
{
    QList<UserInfo> l;
    QSqlQuery sql(m_db);
    // QString strql= QString("select * from username ");
    // sql.exec(strql);
    // 合并为
    sql.exec("select * from username ");

    UserInfo info;
    while(sql.next())
    {
        info.username=sql.value(0).toString();
        info.password=sql.value(1).toString();
        info.aut=sql.value(2).toString();

        //存放到表中
        l.push_back(info);
    }
    return l;
}

bool StuSql::isExist(QString strUser)
{
    QSqlQuery sql(m_db);
    return sql.exec(QString("select * from username where username='%1'").arg(strUser));

}

bool StuSql::UpdateUserInfo(UserInfo info)
{
    QSqlQuery sql(m_db);
    // /*update student set name = 'asd' where id=25*/;
    //注意：user表里的数据为  auth,
    // 定义的userInfo里面为   aut
    QString strsql=QString("update username set password = '%1',auth='%2'"
                             " where username='%3'").
                     arg(info.password).arg(info.aut).arg(info.username);

    //是否修改成功s
    return sql.exec(strsql);
}

bool StuSql::addUser(UserInfo info )
{
    QSqlQuery sql(m_db);
    // UserInfo info;
    QString strsql=QString("insert into username values('%1','%2','%3')").
                     arg(info.username).arg(info.password).
                     arg(info.aut);
    //是否添加成功
    return sql.exec(strsql);
}

bool StuSql::delUser(QString strUserName)
{
    QSqlQuery sql(m_db);
    return sql.exec(QString("delete from username where username='%1'").arg(strUserName));

}


