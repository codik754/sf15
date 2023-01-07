//Файл chat.h
#pragma once

#include "sha1.h"
#include <string.h>

#include <iostream>

#define SIZE 10
#define LOGINLENGTH 10

class Chat {
public:
    //Конструктор по умолчанию
    Chat();
    //Конструктор копирования
    Chat(const Chat &other);
    //Деструктор
    ~Chat() {
        delete[] array;
    }
    //Оператор присваивания
    Chat& operator=(const Chat& other);

    //Регистрация пользователя
    void reg(char login[LOGINLENGTH], char pass[], int pass_length);
    //Проверка логина и пароля
    bool login(char login[LOGINLENGTH], char pass[], int pass_length);

    //Показать весь список логинов и паролей
    void show();

private:
    //Состояние пары логин-пароль
    enum enPairStatus {
        free,
        engaged,
        deleted
    };

    struct Pair {
        enPairStatus status_;
        char login_[LOGINLENGTH];
        uint* pass_sha1_hash_;
        

        //Контруктор по умолчанию
        Pair() : status_(enPairStatus::free),login_("UNKNOWN"), pass_sha1_hash_(nullptr) { }
        //Конструктор с параметрами
        Pair(char login[LOGINLENGTH], uint* sh1) : status_(enPairStatus::engaged), pass_sha1_hash_(sh1) {
            strcpy_s(login_, login);
        }
        //Конструктор копирования
        Pair(const Pair& other) : status_(other.status_), pass_sha1_hash_(other.pass_sha1_hash_) {
            strcpy_s(login_, other.login_);
        }
        //Деструктор
        ~Pair() {
            delete[] pass_sha1_hash_;
        }
        //Оператор присваивания
        Pair& operator = (const Pair& other);

        //Установка значений
        void setValues(char login[LOGINLENGTH], uint* sh1, enPairStatus st);

        //Установить в удален
        void setDeleted();

        //Установить в занят
        void setEngaged();
       
        //Установить в свободен
        void setFree();

        //Сравнение хешей
        bool checkPass(const uint* sh1);

        //Вывести логин и хеш
        void show();
    };

    //Хеш-функция для ХТ
    int hash_func(const char login[LOGINLENGTH], int offset);

    Pair *array;//массив для хеш-таблицы
    int mem_size;//размер массива
    int count;//колиество записей
};