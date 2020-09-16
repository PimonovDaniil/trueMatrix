
// trueMatrix.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

class Matrix {
private:
    int rows;
    int cols;
    double** matrix;

    /*инициализация (создание дубликата матрицы)*/
    void init(int rows, int cols, double** matrix) {
        this->rows = rows; this->cols = cols;
        if ((rows > 0) && (cols > 0)) {
            double** newMatrix = new double* [rows];
            for (int i = 0; i < rows; i++) {
                newMatrix[i] = new double[cols];
            }
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                        newMatrix[i][j] = matrix[i][j];
            this->matrix = newMatrix;
        }
        else {
            this->matrix = NULL;
        }
    }

    /*копирование объекта матрица*/
    void copy(Matrix& other) {
        /*выкидываем за собой мусор*/
        for (int i = 0; i < this->rows; i++)
            delete[] this->matrix[i];
        delete[] this->matrix;
        this->cols = other.cols;
        this->rows = other.rows;

        this->matrix = new double* [this->rows];
        for (int i = 0; i < this->rows; i++) {
            this->matrix[i] = new double[this->cols];
        }
        for (int i = 0; i < this->rows; i++)
            for (int j = 0; j < this->cols; j++)
                this->matrix[i][j] = other[i][j];
    }

public:
    Matrix() {
        init(0, 0, NULL);
    }

    Matrix(int rows,int cols, double** matrix) {
        init(rows, cols, matrix);
        
    }

    Matrix(int square, double** matrix) {
        init(square, square, matrix);
        
    }

    /*конструктор копирования*/
    Matrix(Matrix& other) {
        copy(other);
    }


    ~Matrix() {
        /*выкидываем за собой мусор*/
        for (int i = 0; i < this->rows; i++)
            delete[] this->matrix[i];
        delete[] this->matrix;
    }

    /*подмена понятий (перегрузка)*/
    Matrix& operator=(Matrix& other)
    {
        // Проверка на самоприсваивание
        if (this != &other) copy(other);
        return *this;
    }

    double*& operator[](int index) {
        return this->matrix[index];//TODO сделать проверку индексов
    }

    int getCols() {
        return this->cols;
    }

    int getRows() {
        return this->rows;
    }

    void setLength(int rows, int cols) {
        if ((rows == 0) || (cols == 0)) {
            /*выкидываем за собой мусор*/
            for (int i = 0; i < this->rows; i++)
                delete[] this->matrix[i];
            delete[] this->matrix;

            this->matrix = NULL;
            this->rows = rows;
            this->cols = cols;
        }
        else if ((rows < 0) || (cols < 0)) {
            throw "Размер матрицы не может быть отрицательным";
        }
        else if (!((this->rows == rows) && (this->cols == cols))) {
            /*инициализируем новую матрицу*/
            double** newMatrix = new double* [rows];
            for (int i = 0; i < rows; i++) {
                newMatrix[i] = new double[cols];
            }

            /*переносим данные*/
            for (int i = 0; i < rows; i++)
                for (int j = 0; j < cols; j++)
                    if ((i < this->rows) && (j < this->cols)) {
                        newMatrix[i][j] = this->matrix[i][j];
                    }
                    else {
                        newMatrix[i][j] = 0;
                    }

            /*выкидываем за собой мусор*/
            for (int i = 0; i < this->rows; i++)
                delete[] this->matrix[i];
            delete[] this->matrix;

            this->matrix = newMatrix;
            this->cols = cols;
            this->rows = rows;
        }
    }

    void print() { //TODO
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->cols; j++)
                printf("%lf ", this->matrix[i][j]);
            printf("\n");
        }
    }

};

int main()
{
    /*инициализируем новую матрицу*/
    double** arr = new double* [2];
    for (int i = 0; i < 2; i++) {
        arr[i] = new double[3];
    }
    arr[0][0] = 1; arr[0][1] = 2; arr[0][2] = 3;
    arr[1][0] = 4; arr[1][1] = 5; arr[1][2] = 6;
    /*for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++)
            printf("%lf ", arr[i][j]);
        printf("\n");
    }*/
    Matrix a(2,3,arr);
    Matrix b;
    b = a;
    b.print();

    
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   ++3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
