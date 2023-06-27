#include "accountlist.h"
#include "QJsonDocument"
#include "QJsonObject"
#include "QJsonArray"
#include "QFile"

AccountList::AccountList() //конструктор
{

}

bool AccountList::loadJSON(QString filename)
{
    // создаем объект файла
    QFile file(filename);

    // открываем на чтение
    if (!file.open(QFile::ReadOnly)) { //(QFile::ReadOnly) - разрешаем только чтение
        qDebug()<<"Failed to open file:" << filename;
        return false;
    }

    // чтение из файла
    QByteArray jsonBytes = file.readAll(); //создаем объект класса QByteArray, куда записываем сод-е файла

    QJsonParseError err; //создаем объект класса QJsonParseError для записи ошибок
    QJsonDocument json_doc = QJsonDocument::fromJson(jsonBytes, &err); //запишем либо jsonBytes, либо ошибку

    if (json_doc.isNull()) { //проверка на ошибку
        qDebug() <<"Error when parsing JSON:" << err.errorString();
        return false;
    }

    if (!json_doc.isArray()) {
        qDebug() << "JSON is not array";
        return false;
    }

    QJsonArray jsonArray = json_doc.array(); //с пом-ю метода .array преобразовываем док в массив

    for (int i = 0; i < jsonArray.count(); i++) { //начинаем цикл
        if (!jsonArray.at(i).isObject()) { //проверка, что json - объект
            qDebug() << "Not a JSON object";
            continue;
        }

        QJsonObject object = jsonArray.at(i).toObject(); //преобразование элемента к объекту

        AccountItem item;

        //парсинг:
        if (object.contains("username") && object["username"].isString())
            item.username = object["username"].toString();

        if (object.contains("password") && object["password"].isString())
            item.password = object["password"].toString();

        this->appendItem(item); //добавление значения в вектор
    }


    return true;
}


void AccountList::appendItem(AccountItem item) //метод для добавления нового элемента в вектор
{
    this->mItems.append(item);
}

AccountItem AccountList::getItem(int index) //метод для получения ацтема по индексу
{
    return this->mItems.at(index);
}

int AccountList::size() //метод для получения кол-ва элементов
{
    return this->mItems.size();
}
