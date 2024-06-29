#ifndef UPDATE_USER_H
#define UPDATE_USER_H
#include"stusql.h"
#include <QDialog>

namespace Ui {
class Update_User;
}

class Update_User : public QDialog
{
    Q_OBJECT

public:
    explicit Update_User(QWidget *parent = nullptr);
    ~Update_User();
    void pass(UserInfo info);

private slots:
    void on_save_clicked();

    void on_cancel_clicked();

private:
    Ui::Update_User *ui;
    UserInfo m_info;
};

#endif // UPDATE_USER_H
