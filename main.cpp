#include <iostream>
#include "accountlist.h"
#include "QDebug" //для вывода в консоль сообщений

const std::string PIN = "1234"; //создаем константу типа строки для пинкода

int main(int argc, char *argv[])
{

    std::cout << "Enter pin: ";
    std::string pin;
    std::cin >> pin;
    if (pin != PIN) {
        std::cout << "Incorrect PIN" << std::endl; //std::endl - перевод строки (\n)
        return 0;
    }

    AccountList accountList; //создание объекта класса AccountList
    accountList.loadJSON("credentials.json");


    while (true) { //бесконечный цикл, ожидающий ввода от пользователя
        std::cout << "Enter account index: ";
        int index = 0;
        std::cin >> index;

        if (index == -1) {
            return 0;
        }

        if (index > accountList.size() - 1 ) { //сравнение с макс индексом
            std::cout << "Account not found" << std::endl ;
            continue;
        }
        qDebug() << accountList.getItem(index).username << accountList.getItem(index).password; //вывод учетных данных
    }


    return 0;
}
