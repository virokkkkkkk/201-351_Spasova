#ifndef ACCOUNTLIST_H
#define ACCOUNTLIST_H
#include <QString>
#include <QVector>


struct AccountItem {
    QString username;
    QString password;
};

class AccountList
{
public:
    AccountList();
    bool loadJSON(QString filename);

    void appendItem(AccountItem item);
    AccountItem getItem(int index);
    int size();

private:
    QVector<AccountItem> mItems;
};

#endif // ACCOUNTLIST_H
