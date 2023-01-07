//Файл chat.cpp
#include "chat.h"
#include <iostream>
#include <string.h>

//Конструктор по умолчанию
Chat::Chat() {
    count = 0;
    mem_size = 16;
    array = new Pair[mem_size];
}

//Конструктор копирования
Chat::Chat(const Chat& other) : mem_size(other.mem_size), count(other.count) {
    array = new Pair[mem_size];
    for (size_t i = 0; i < mem_size; ++i) {
        array[i] = other.array[i];
    }
}

//Оператор присваивания
Chat& Chat::operator=(const Chat& other) {
    //Проверка на самоприсвоение
    if (this == &other) {
        return *this;
    }

    count = other.count;
    mem_size = other.mem_size;
    
    if (array) {
        delete[] array;
    }

    array = new Pair[mem_size];
    for (size_t i = 0; i < mem_size; ++i) {
        array[i] = other.array[i];
    }

    return *this;
}

//Регистрация пользователя
void Chat::reg(char login[LOGINLENGTH], char pass[], int pass_length) {
  //  data[data_count++] = AuthData(_login, sha1(_pass, pass_length));
    int index = -1, i = 0;
    // берем пробы по всем i от 0 до размера массива
    for (;i < mem_size; i++) {
        index = hash_func(login, i);
        if (array[index].status_ == enPairStatus::free) {
            // найдена пустая ячейка, занимаем ее
            break;
        }
    }

    if (i >= mem_size) return; // все перебрали, нет места

    // кладем в свободную ячейку пару
    array[index] = Pair(login, sha1(pass, pass_length));
    count++;
}


//Проверка логина и пароля
bool Chat::login(char login[LOGINLENGTH], char pass[], int pass_length) {

    for (int i = 0;i < mem_size; i++) {
        int index = hash_func(login, i);
        //Проверяем состояние записи и логин в ней
        if (array[index].status_ == enPairStatus::engaged &&
            !strcmp(array[index].login_, login)) {
            //Сравниваем хеши паролей
            if (array[index].checkPass(sha1(pass, pass_length))) {
                return true;
            }
            return false;
        }
        else if (array[index].status_ == enPairStatus::free) {
            return false;
        }
    }

    return false;
}

//Показать весь список логинов и паролей
void Chat::show() {
    for (size_t i = 0; i < mem_size; ++i) {
        if (array[i].status_ == enPairStatus::engaged) {
            array[i].show();
        }
    }
}

//Хеш-функция для ХТ
int Chat::hash_func(const char login[LOGINLENGTH], int offset) {
    const double A = 0.618;//коэффициент
    int M = mem_size;

    int val = 0;

    //Суммируем числовые значения символов
    for (size_t i = 0; i < LOGINLENGTH && login[i] != '\0'; ++i) {
        val += login[i];
    }

    //Высчитываем первое значения методом умножения
    int firstResult = int(M * (A * val - int(A * val))) + offset * offset;

    //Высчитываем итоговое значение
    return int(M * (A * firstResult - int(A * firstResult)));
}

//Оператор присваивания
Chat::Pair& Chat::Pair::operator = (const Pair& other) {
    //Проверка на самоприсвоение
    if (this == &other) {
        return *this;
    }

    strcpy_s(login_, other.login_);

    status_ = other.status_;

    if (pass_sha1_hash_)
        delete[] pass_sha1_hash_;

    pass_sha1_hash_ = new uint[SHA1HASHLENGTHUINTS];

    memcpy(pass_sha1_hash_, other.pass_sha1_hash_, SHA1HASHLENGTHBYTES);

    return *this;
}

//Установка значений
void Chat::Pair::setValues(char login[LOGINLENGTH], uint* sh1, enPairStatus st) {
    strcpy_s(login_, login);

    if (pass_sha1_hash_)
        delete[] pass_sha1_hash_;

    status_ = st;

    pass_sha1_hash_ = new uint[SHA1HASHLENGTHUINTS];

    memcpy(pass_sha1_hash_, sh1, SHA1HASHLENGTHBYTES);
}


//Установить в свободен
void Chat::Pair::setFree() {
    status_ = enPairStatus::free;
}

//Установить в занят
void Chat::Pair::setEngaged() {
    status_ = enPairStatus::engaged;
}

//Установить в удален
void Chat::Pair::setDeleted() {
    status_ = enPairStatus::deleted;
}

//Сравнение хешей
bool Chat::Pair::checkPass(const uint* sh1) {
    for (size_t i = 0; i < SHA1HASHLENGTHUINTS; ++i) {
        if (pass_sha1_hash_[i] != sh1[i]) {
            return false;
        }
    }

    return true;
}

//Вывести логин и хеш
void Chat::Pair::show() {
    std::cout << login_ << "     ";

    for (size_t i = 0; i < SHA1HASHLENGTHUINTS; ++i) {
        cout << pass_sha1_hash_[i] << " ";
    }

    std::cout << std::endl;
}