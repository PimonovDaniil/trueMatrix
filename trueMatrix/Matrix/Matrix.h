#pragma once

namespace mathTools
{

	class Matrix
	{
    private:
        int rows;
        int cols;
        double** matrix;

        /*инициализация (создание дубликата матрицы)*/
        void init(int rows, int cols, double** matrix);

        /*копирование объекта матрица*/
        void copy(Matrix& other);

    public:
        /*конструктор  без параметров*/
        Matrix();

        /*принимает матрицу с размерами rows cols*/
        Matrix(int rows, int cols, double** matrix);

        /*матрица размеров rows cols заполненная нулями*/
        Matrix(int rows, int cols);

        /*принимает квадратную матрицу*/
        Matrix(int square, double** matrix);

        /*матрица размера square^2 заполненная нулями*/
        Matrix(int square);

        /*конструктор копирования*/
        Matrix(Matrix& other);

        /*деструктор*/
        ~Matrix();

        /*подмена понятий (перегрузка)*/
        Matrix& operator=(Matrix& other);

        /*подмена понятий (перегрузка)*/
        double*& operator[](int index);

        /*подмена понятий (перегрузка)*/
        void operator+=(Matrix& other);

        /*подмена понятий (перегрузка)*/
        void operator-=(Matrix& other);

        int getCols(); //узнать кол-во столбцов

        int getRows(); //узнать кол-во рядов

        /*Изменяет размер матрицы. Работает как и в сторону увеличения, так
        и в сторону уменьшения вплоть до удаления при пареметрах (0, 0).
        При уменьшении размеров матрицы лишние элементы удаляются, при увиличерии
        заполняются нулями. */
        void setLength(int rows, int cols);

        bool isMultiply(Matrix other);

        bool isSum(Matrix other);

        double getMax();

        double getMin();

        void print(); //TODO добавить перегрузку оператора <<
	};
}
