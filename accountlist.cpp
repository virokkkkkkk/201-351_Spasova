#include "accountlist.h"
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonArray"
#include "QFile"

AccountList::AccountList()
{

}

bool AccountList::loadJSON(QString filename)
{
    // создаем объект файла
    QFile file(filename);

    // открываем на чтение
    if (!file.open(QFile::ReadOnly)) {
        qDebug()<<"Failed to open file:" << filename;
        return false;
    }

    // чтение из файла
    QByteArray jsonBytes = file.readAll();

    QJsonParseError err;
    QJsonDocument json_doc = QJsonDocument::fromJson(jsonBytes, &err);

    if (json_doc.isNull()) {
        qDebug() <<"Error when parsing JSON:" << err.errorString();
        return false;
    }

    if (!json_doc.isArray()) {
        qDebug() << "JSON is not array";
        return false;
    }

    QJsonArray jsonArray = json_doc.array();

    for (int i = 0; i < jsonArray.count(); i++) {
        if (!jsonArray.at(i).isObject()) {
            qDebug() << "Not a JSON object";
            continue;
        }

        QJsonObject object = jsonArray.at(i).toObject();

        AccountItem item;

        if (object.contains("username") && object["username"].isString())
            item.username = object["username"].toString();

        if (object.contains("password") && object["password"].isString())
            item.password = object["password"].toString();

        this->appendItem(item);
    }


    return true;
}


void AccountList::appendItem(AccountItem item)
{
    this->mItems.append(item);
}

AccountItem AccountList::getItem(int index)
{
    return this->mItems.at(index);
}

int AccountList::size()
{
    return this->mItems.size();
}
