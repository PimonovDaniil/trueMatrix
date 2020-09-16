
// trueMatrix.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

class Matrix {
private:
    int rows;
    int cols;
    int** matrix;

    void init(int rows, int cols, int** matrix) {
        this->rows = rows; this->cols = cols;
        if ((rows > 0) && (cols > 0)) {
            int** newMatrix = new int* [rows];
            for (int i = 0; i < rows; i++) {
                newMatrix[i] = new int[cols];
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

public:
    Matrix() {
        init(0, 0, NULL);
    }

    Matrix(int rows,int cols, int** matrix) {
        init(rows, cols, matrix);
        
    }

    Matrix(int square, int** matrix) {
        init(square, square, matrix);
        
    }

    void setLength(int rows, int cols) {
        if ((rows == 0) || (cols == 0)) {
            this->matrix = NULL;
            this->rows = rows;
            this->cols = cols;
        }
        else if ((rows < 0) || (cols < 0)) {
            throw "Размер матрицы не может быть отрицательным";
        }
        else if (!((this->rows == rows) && (this->cols == cols))) {
            /*инициализируем новую матрицу*/
            int** newMatrix = new int* [rows];
            for (int i = 0; i < rows; i++) {
                newMatrix[i] = new int[cols];
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

    void print() {
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->cols; j++)
                printf("%d ", this->matrix[i][j]);
            printf("\n");
        }
    }

};

int main()
{
    /*инициализируем новую матрицу*/
    int** arr = new int* [2];
    for (int i = 0; i < 2; i++) {
        arr[i] = new int[3];
    }
    arr[0][0] = 1; arr[0][1] = 2; arr[0][2] = 3;
    arr[1][0] = 4; arr[1][1] = 5; arr[1][2] = 6;
    Matrix a(2,3,arr);
    a.print();
    a.setLength(2, 9);
    a.print();

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
