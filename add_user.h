#ifndef ADD_USER_H
#define ADD_USER_H
#include"stusql.h"
#include <QDialog>

namespace Ui {
class add_User;
}

class add_User : public QDialog
{
    Q_OBJECT

public:
    explicit add_User(QWidget *parent = nullptr);
    ~add_User();

private slots:
    void on_btn_save_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::add_User *ui;
};

#endif // ADD_USER_H
