//Файл main.cpp
#include <iostream>
#include "chat.h"

int main(){
    setlocale(LC_ALL, "");
    
    Chat chat;//объект под чат
    //Добавляем пользователей
    char login1[10] = "login1";
    char pass1[4] = "123";

    chat.reg(login1, pass1, 4);

    char login2[10] = "login2";
    char pass2[4] = "321";

    chat.reg(login2, pass2, 4);

    char login3[10] = "login3";
    char pass3[4] = "213";

    chat.reg(login3, pass3, 4);

    char login4[10] = "login4";
    char pass4[4] = "312";

    //Выводим все логины и хеши паролей
    chat.show();

    //Проверка логинов и паролей
    std::cout << std::endl << "Проверка логинов и паролей: " << std::endl;
    std::cout << "login1: " << chat.login(login1, pass1, 4) << std::endl;
    std::cout << "login1(с другим паролем): " << chat.login(login1, pass2, 4) << std::endl;
    std::cout << "login2: " << chat.login(login2, pass2, 4) << std::endl;
    std::cout << "login2(с другим паролем): " << chat.login(login2, pass1, 4) << std::endl;
    std::cout << "login3: " << chat.login(login3, pass3, 4) << std::endl;
    std::cout << "login3(с другим паролем): " << chat.login(login3, pass2, 4) << std::endl;
    std::cout << "login4: " << chat.login(login4, pass4, 4) << std::endl;

    return 0;
}
