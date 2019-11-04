#include <matrix_export.h>

// шаблонный класс Матрица
template <typename T>
class MATRIX_EXPORT MATRIX
{
private:
    T** M; // матрица
    int m; // количество строк
    int n; // количество столбцов

public:
    // конструкторы
    MATRIX()
    {
        n = m = 0;
        M = nullptr;
    }

    // конструктор с двумя параметрами
    MATRIX(int _m, int _n)
    {
        m = _m;
        n = _n;

        // Выделить память для матрицы
        // Выделить пам'ять для массива указателей
        M = (T**) new T*[m]; // количество строк, количество указателей

        // Выделить память для каждого указателя
        for (int i = 0; i < m; i++)
        M[i] = (T*)new T[n];

        // заполнить массив M нулями
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                M[i][j] = 0;
    }

    // Конструктор копирования - обязательный
    MATRIX(const MATRIX& _M)
    {
        // Создается новый объект для которого виделяется память
        // Копирование данных *this <= _M
        m = _M.m;
        n = _M.n;

        // Выделить память для M
        M = (T**) new T*[m]; // количество строк, количество указателей

        for (int i = 0; i < m; i++)
            M[i] = (T*) new T[n];

        // заполнить значениями
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                M[i][j] = _M.M[i][j];
    }

    // методы доступа
    T GetMij(int i, int j)
    {
        if ((m > 0) && (n > 0))
            return M[i][j];
        else
            return 0;
    }

    void SetMij(int i, int j, T value)
    {
        if ((i < 0) || (i >= m))
            return;
        if ((j < 0) || (j >= n))
            return;
        M[i][j] = value;
    }

    // метод, выводящий матрицу
    void Print(const char* ObjName)
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

    // оператор копирования - обязательный
    MATRIX operator=(const MATRIX& _M)
    {
        if (n > 0)
        {
            // освободить память, выделенную ранее для объекта *this
            for (int i = 0; i < m; i++)
                delete[] M[i];
        }

        if (m > 0)
        {
          delete[] M;
        }

        // Копирование данных M <= _M
        m = _M.m;
        n = _M.n;

        // Выделить память для M опять
        M = (T**) new T*[m]; // количество строк, количество указателей
        for (int i = 0; i < m; i++)
          M[i] = (T*) new T[n];

        // заполнить значениями
        for (int i = 0; i < m; i++)
          for (int j = 0; j < n; j++)
            M[i][j] = _M.M[i][j];
        return *this;
    }

    // Деструктор - освобождает память, выделенную для матрицы
    ~MATRIX()
    {
        if (n > 0)
        {
            // освободить выделенную память для каждой строки
            for (int i = 0; i < m; i++)
            delete[] M[i];
        }

        if (m > 0)
            delete[] M;
    }

    // транспонирование
    MATRIX transpose()
    {
        MATRIX<T> T(n, m);

        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                T.M[j][i] = M[i][j];

        return T;
    }

    // умножение на матрицу
    MATRIX multiply (MATRIX B)
    {
        MATRIX<T> C(m, B.n);

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
    MATRIX sum(MATRIX B)
    {
        MATRIX<T> C(m, n);

        if (B.m != m || B.n != n)
            return {};

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                C.M[i][j] += M[i][j] + B.M[i][j];

        return C;
    }

    // вычитание
    MATRIX sub(MATRIX B)
    {
        MATRIX<T> C(m, n);

        if (B.m != m || B.n != n)
            return {};

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                C.M[i][j] += M[i][j] - B.M[i][j];

        return C;
    }

    // умножение на число
    template <typename CoefType>
    MATRIX multiply(CoefType k)
    {
        MATRIX<T> K(m, n);

        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                K.M[i][j] = M[i][j] * k;

        return K;
    }
};
