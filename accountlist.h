#ifndef ACCOUNTLIST_H
#define ACCOUNTLIST_H
#include <QString>
#include <QVector>


struct AccountItem {
    QString username;
    QString password;
};

class AccountList //для хранения массива учетных записей
{
public:
    AccountList(); //конструктор
    bool loadJSON(QString filename); //для чтения из файла

    void appendItem(AccountItem item); //добавление элемента
    AccountItem getItem(int index); //метод для получения элемента
    int size(); //возвращает количество эл-в вектора

private:
    QVector<AccountItem> mItems; //вектор из объектов <AccountItem>
};

#endif // ACCOUNTLIST_H
