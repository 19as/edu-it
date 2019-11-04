#include <matrix_export.h>
#include <iostream>

class __declspec(dllexport) MATRIX
{
private:
    int** M; // матрица
    int m; // количество строк
    int n; // количество столбцов

public:
    // конструкторы
    MATRIX();

    // конструктор с двумя параметрами
    MATRIX(int _m, int _n);

    // Конструктор копирования - обязательный
    MATRIX(const MATRIX& _M);

    // методы доступа
    int GetMij(int i, int j);

    void SetMij(int i, int j, int value);

    // метод, выводящий матрицу
    void Print(const char* ObjName);

    // оператор копирования - обязательный
    MATRIX operator=(const MATRIX& _M);

    // Деструктор - освобождает память, выделенную для матрицы
    ~MATRIX();

    // транспонирование
    MATRIX transpose();

    // умножение на матрицу
    MATRIX multiply(MATRIX B);

    // сложение
    MATRIX sum(MATRIX B);

    // вычитание
    MATRIX sub(MATRIX B);

    // умножение на число
    MATRIX multiply(int k);
};
