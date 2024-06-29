#ifndef STUSQL_H
#define STUSQL_H
#include<QSqlDatabase>
#include <QObject>
//类型        描述
//qint8     char
//qint16	short int
//qint32	int
//qint64	long long int

//quint8	unsigned char
//quint16	unsigned short
//quint32	unsigned int
//quint64	unsigned long long int

struct StuInfo
{
    int id;
    QString name;
    quint8 age;
    quint16 grade;
    quint16 uid_class;
    quint32 student_id;
    QString phone;
    QString wechat;
};

struct UserInfo
{
    QString username;
    QString password;
    QString aut;
};

class StuSql : public QObject
{
    Q_OBJECT
public:
    //单例？
    //声明静态指针承接唯一实例
    static StuSql *ptrstuSql;
    static StuSql *getinstance()
    {
        //指针名放到后面，出现少“=”情况就会报错
        if(nullptr==ptrstuSql)
        {
            ptrstuSql=new StuSql;
        }
        return ptrstuSql;
    }

    static StuSql *ptrUserSql;
    static StuSql *getinstance_user()
    {
        //指针名放到后面，出现少“=”情况就会报错
        if(nullptr==ptrUserSql)
        {
            ptrUserSql=new StuSql;
        }
        return ptrUserSql;
    }


    explicit StuSql(QObject *parent = nullptr);

    void init();
    //
    //
    //查询所有学生数量
    quint32 GetStuCnt();

    //查询第几页学生数据，从第0页开始计数
    //(第几页，一页有多少学生)
    QList<StuInfo> GetPageStu(quint32 page,quint32 uiCnt);

    //增加学生
    void addStu(StuInfo info);

    //删除学生
    bool delStu(int id);

    //清空学生表
    bool clearStuTable();

    //修改学生信息
    bool UpdateStuInfo(StuInfo info);

    //查询所有用户
    QList<UserInfo> getAllUser();

    //查询用户名是否存在
    // bool isExist(QString strUser);
    bool isExist(UserInfo info);

    //修改用户信息（只能改密码和权限）
    bool UpdateUserInfo(UserInfo info);

    //添加单个用户
    bool addUser(UserInfo info);

    //删除单个用户
    bool delUser(QString strUserName);

    // // 查找用户是否存在
    // bool checkUser(UserInfo info);

signals:
private:
    QSqlDatabase m_db;
};

#endif // STUSQL_H
