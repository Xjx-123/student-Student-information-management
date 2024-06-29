#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"page_login.h"
#include <QMainWindow>
#include"stusql.h"
#include<dlg_addstu.h>
#include<add_user.h>
#include<update_user.h>
// #include<dlg_delstu.h>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_exit_clicked();
//模拟数据
    void on_bto_simulation_clicked();

    void on_btn_add_clicked();

    void on_btn_clear_clicked();

    void on_btn_del_clicked();

    void on_btn_update_clicked();

    void on_btn_search_clicked();

    void switchPage();

    void on_User_clicked();

    void on_Student_clicked();

    void on_btn_adduser_clicked();

    void on_btn_updateuser_clicked();

    void on_btn_deluser_clicked();

    void on_btn_searchuser_clicked();

private:
    void updateTab();
    void updateTab_User();
    void pass_username(UserInfo info);


private:
    Ui::MainWindow *ui;

    page_login m_dlglogin;

    StuSql *m_ptrStuSql;
    StuSql *m_ptrUserSql;
    QStringList m_lname;
    Dlg_AddStu m_dlgAddStu;
    add_User m_AddUser;
    Update_User m_UpdateUser;
    // dlg_delstu m_dlgDelStu;

};
#endif // MAINWINDOW_H
