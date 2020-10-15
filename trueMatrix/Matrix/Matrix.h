#pragma once
#include <iostream>
namespace mathTools
{

    class settings;

	class Matrix
	{
        //friend std::ostream& operator<< (std::ostream& os, const Matrix& matrix);
    private:
        int rows;
        int cols;
        int numObj;
        double* matrix;
        static int num;
        
        void init(int rows, int cols,    double* matrix);/*инициализация (создание дубликата матрицы)*/
        void copy(const Matrix& other);/*копирование объекта матрица*/

        class MatrixRow {
        private:
            const Matrix* m_owner;
            unsigned m_r;
        public:
            MatrixRow(const Matrix* owner, unsigned r);
     
            double operator[] (unsigned r) const;
            double& operator[] (unsigned r);
        };

    public:
        static settings* setting;
        static bool debug;
        Matrix(); /*конструктор  без параметров*/
        Matrix(int rows, int cols, double* matrix); /*принимает матрицу с размерами rows cols*/
        Matrix(int rows, int cols);/*матрица размеров rows cols заполненная нулями*/
        Matrix(int square, double* matrix);/*принимает квадратную матрицу*/
        Matrix(int square);/*матрица размера square^2 заполненная нулями*/
        Matrix(Matrix& other) ;/*конструктор копирования*/
        ~Matrix();/*деструктор*/

        /*подмена понятий (перегрузка)*/
        Matrix& operator=(const Matrix& other);
        MatrixRow operator[](const int index);
        //const double* operator[](const int index) const;
        /*Matrix& operator+=(const Matrix& other);
        Matrix& operator-=(const Matrix& other);
        Matrix& operator*=(double k);
        Matrix& operator*=(const Matrix& other);
        Matrix operator+(const Matrix& other);
        Matrix operator-(const Matrix& other);
        Matrix operator*(const Matrix& other);
        Matrix operator*(double k);*/
     
        
        static settings* settings();
        int getCols() const; //узнать кол-во столбцов
        int getRows() const; //узнать кол-во рядов

        /*Изменяет размер матрицы. Работает как и в сторону увеличения, так
        и в сторону уменьшения вплоть до удаления при пареметрах (0, 0).
        При уменьшении размеров матрицы лишние элементы удаляются, при увиличерии
        заполняются нулями. */
        //void setLength(int rows, int cols);

        //bool isMultiply(const Matrix& other); //проверка на возможность умножения
        //bool isSum(const Matrix& other); //проверка на возможность сложения/вычитания

        double getMax(); //вернуть максимальный элемент
        double getMin(); //вернуть минимальный элемент

      

	};


    /*класс в котором хранятся настройки
    формата вывода матрицы на экран. */
    class settings
    {
    private:
        int setw;
        int precision;
        static settings* uniqueInstance;
        settings(); 

    public:
        static settings* create();
        void setSetw(int s);
        void setPrecision(int p);
        int getSetw();
        int getPrecision();
    };
}
