#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"page_login.h"
#include <QMainWindow>
#include"stusql.h"
#include<dlg_addstu.h>
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

private:
    void updateTab();

private:
    Ui::MainWindow *ui;

    page_login m_dlglogin;

    StuSql *m_ptrStuSql;
    QStringList m_lname;
    Dlg_AddStu m_dlgAddStu;
    // dlg_delstu m_dlgDelStu;
};
#endif // MAINWINDOW_H
