#include <iostream>
#include "accountlist.h"
#include "QDebug"

const std::string PIN = "1234";

int main(int argc, char *argv[])
{

    std::cout << "Enter pin: ";
    std::string pin;
    std::cin >> pin;
    if (pin != PIN) {
        std::cout << "Incorrect PIN" << std::endl;
        return 0;
    }

    AccountList accountList;
    accountList.loadJSON("credentials.json");


    while (1) {
        std::cout << "Enter account index: ";
        int index = 0;
        std::cin >> index;

        if (index == -1) {
            return 0;
        }

        if (index > accountList.size() - 1 ) {
            std::cout << "Account not found" << std::endl ;
            continue;
        }
        qDebug() << accountList.getItem(index).password << accountList.getItem(index).username;
    }


    return 0;
}
