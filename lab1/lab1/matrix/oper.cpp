#include "oper.h"

#include <iostream>

MATRIX::MATRIX()
{
    n = m = 0;
    M = nullptr;
}

// конструктор с двум€ параметрами
MATRIX::MATRIX(int _m, int _n)
{
    m = _m;
    n = _n;

    // ¬ыделить пам€ть дл€ матрицы
    // ¬ыделить пам'€ть дл€ массива указателей
    M = (int**) new int*[m]; // количество строк, количество указателей

    // ¬ыделить пам€ть дл€ каждого указател€
    for (int i = 0; i < m; i++)
        M[i] = (int*)new int[n];

    // заполнить массив M нул€ми
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            M[i][j] = 0;
}

//  онструктор копировани€ - об€зательный
MATRIX::MATRIX(const MATRIX& _M)
{
    // —оздаетс€ новый объект дл€ которого видел€етс€ пам€ть
    //  опирование данных *this <= _M
    m = _M.m;
    n = _M.n;

    // ¬ыделить пам€ть дл€ M
    M = (int**) new int*[m]; // количество строк, количество указателей

    for (int i = 0; i < m; i++)
        M[i] = (int*) new int[n];

    // заполнить значени€ми
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            M[i][j] = _M.M[i][j];
}

// методы доступа
int MATRIX::GetMij(int i, int j)
{
    if ((m > 0) && (n > 0))
        return M[i][j];
    else
        return 0;
}

void MATRIX::SetMij(int i, int j, int value)
{
    if ((i < 0) || (i >= m))
        return;
    if ((j < 0) || (j >= n))
        return;
    M[i][j] = value;
}

// метод, вывод€щий матрицу
void MATRIX::Print(const char* ObjName)
{
    std::cout << "Object: " << ObjName << std::endl;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            std::cout << M[i][j] << "\t";
        std::cout << std::endl;
    }
    std::cout << "---------------------" << std::endl << std::endl;
}

// оператор копировани€ - об€зательный
MATRIX MATRIX::operator=(const MATRIX& _M)
{
    if (n > 0)
    {
        // освободить пам€ть, выделенную ранее дл€ объекта *this
        for (int i = 0; i < m; i++)
            delete[] M[i];
    }

    if (m > 0)
    {
        delete[] M;
    }

    //  опирование данных M <= _M
    m = _M.m;
    n = _M.n;

    // ¬ыделить пам€ть дл€ M оп€ть
    M = (int**) new int*[m]; // количество строк, количество указателей
    for (int i = 0; i < m; i++)
        M[i] = (int*) new int[n];

    // заполнить значени€ми
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            M[i][j] = _M.M[i][j];
    return *this;
}

// ƒеструктор - освобождает пам€ть, выделенную дл€ матрицы
MATRIX::~MATRIX()
{
    if (n > 0)
    {
        // освободить выделенную пам€ть дл€ каждой строки
        for (int i = 0; i < m; i++)
            delete[] M[i];
    }

    if (m > 0)
        delete[] M;
}

// транспонирование
MATRIX MATRIX::transpose()
{
    MATRIX T(n, m);

    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            T.M[j][i] = M[i][j];

    return T;
}

// умножение на матрицу
MATRIX MATRIX::multiply(MATRIX B)
{
    MATRIX C(m, B.n);

    for (int i = 0; i < m; i++)
        for (int j = 0; j < B.n; j++)
        {
            C.M[i][j] = 0;
            for (int k = 0; k < n; k++)
                C.M[i][j] += M[i][k] * B.M[k][j];
        }

    return C;
}

// сложение
MATRIX MATRIX::sum(MATRIX B)
{
    MATRIX C(m, n);

    if (B.m != m || B.n != n)
        return {};

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            C.M[i][j] += M[i][j] + B.M[i][j];

    return C;
}

// вычитание
MATRIX MATRIX::sub(MATRIX B)
{
    MATRIX C(m, n);

    if (B.m != m || B.n != n)
        return {};

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            C.M[i][j] += M[i][j] - B.M[i][j];

    return C;
}

// умножение на число
MATRIX MATRIX::multiply(int k)
{
    MATRIX K(m, n);

    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            K.M[i][j] = M[i][j] * k;

    return K;
}