#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "matrix_class.h"

matrix_from_file matrix_from_file:: constructor(vector<vector<double>> arr)
{
    matrix_from_file matrix;
    matrix.array = arr;
    return matrix;
}

void matrix_from_file:: mass_by_variant(int variant)
{
    string line;
    ifstream in("E:\\Task.txt");
    int size_counter = 0;
    int mass_size;
    double iterations_number = 0;
    if (in.is_open())
    {
        char symbol;
        while(true)
        {
            in.get(symbol);
            if (symbol == '\n')
            {
                size_counter++;
                in.get(symbol);
                if (symbol == '\n')
                {
                    mass_size = size_counter;
                    size_counter = 0;
                    iterations_number++;
                    if (iterations_number == variant)
                    {break;}
                }
            }
        }
        double number;
        array.clear();
        while(array.size() < mass_size)
        {
            vector<double> row;
            while(row.size() < mass_size)
            {
                in >> number;
                row.push_back(number);
            }
            array.push_back(row);
        }
    }
    in.close();
}

matrix_from_file matrix_from_file:: transpose()
{
    double tmp;
    vector<vector<double>> transposed_matrix = array;
    for(int i = 0; i < transposed_matrix.size(); ++i)
    {
        for(int j = i; j < transposed_matrix.size(); ++j)
        {
            tmp = transposed_matrix[i][j];
            transposed_matrix[i][j] = transposed_matrix[j][i];
            transposed_matrix[j][i] = tmp;
        }
    }
    return constructor(transposed_matrix);
}

void matrix_from_file:: print_matrix()
{
    cout << endl << "Your matrix:" << endl;
    for (vector<double> column: array)
    {
        for(double elem: column)
        {
            cout<<elem << '\t';
        }
        cout << endl;
    }
}

matrix_from_file matrix_from_file:: matrix_multiplication_number(double number)
{
    matrix_from_file multiplied_matrix = constructor(array);
    for (int i = 0; i < multiplied_matrix.array.size(); ++i)
    {
        for(int j = 0; j < multiplied_matrix.array.size(); ++j)
        {
            multiplied_matrix.array[i][j] *= number;
        }
    }
    return multiplied_matrix;
}

void matrix_from_file:: write_to_csv() {
    fstream out;
    out.open("E:\\123.csv");
    if (out.is_open()) {
        for (int i = 0; i < array.size(); ++i) {
            for (int j = 0; j < array.size(); ++j) {
                out << array[i][j] << ';';
            }
            out << endl;
        }
        out.close();
    }
}

double matrix_from_file:: determinate()
{
    vector<vector <double>> tmp_array = array;
    for (int q = 0; q < tmp_array.size(); q++)
        for (int w = q + 1; w < tmp_array.size(); w++)
            tmp_array[w] = subtract_line(tmp_array[w],multiply_line(tmp_array[q], tmp_array[w][q] / tmp_array[q][q]));
    double det = 1;
    for (int q = 0; q < tmp_array.size(); q++)
        det *= tmp_array[q][q];
    return det;
}

vector<double> matrix_from_file:: subtract_line(vector<double> one, vector<double> two) {
    for (int q = 0; q < one.size(); q++)
        one[q] -= two[q];
    return one;
}

vector<double> matrix_from_file:: multiply_line(vector<double> one, double number) {
    for (int q = 0; q < one.size(); q++)
        one[q] *= number;
    return one;
}

matrix_from_file matrix_from_file:: inverse ()
{
    matrix_from_file inverse_matrix = constructor(array);
    int counter = 0;
    double multiplier = 1/determinate();
    for (int i = 0; i < inverse_matrix.array.size(); i++)
    {
        for (int j = 0; j < inverse_matrix.array.size(); j++)
        {
            if (counter%2 == 0)
            {
                inverse_matrix.array[i][j] = multiplier * new_matrix(i, j, array).determinate();
                counter++;
            }
            else
            {
                inverse_matrix.array[i][j] = multiplier * -new_matrix(i, j, array).determinate();
                counter++;
            }
        }
    }
    return inverse_matrix.transpose();
}

matrix_from_file matrix_from_file:: new_matrix (int first_index, int second_index, vector<vector <double> > matrix)
{
    vector<vector <double> > minor;
    for(int i = 0; i < matrix.size(); i++)
    {
        vector<double> row;
        for(int j = 0; j <matrix.size(); j++)
        {
            if ((i != first_index) & (j != second_index))
            {
                row.push_back(matrix[i][j]);
            }
        }
        if (!row.empty())
            minor.push_back(row);
    }
    return constructor(minor);
}

int interface:: create_interface()
{
    cout << "Oh, hello there!"<<endl;
    cout << "Print:"<< endl;
    cout << "1 - if u want to create a matrix (variant needed)"<< endl;
    cout << "0 - if u want to exit"<< endl;
    cin >> request;
    if (request == 0)
    {
        return 0;
    }
    if ((request != 0) & (request != 1))
    {
        cout << "Wrong request"<< endl;
    }
    if (request == 1)
    {
        cout << "Print ur variant below:" << endl;
        cin >> var;
        matrix_from_file matrix;
        matrix.mass_by_variant(var);
        cout << "There is your matrix:" << endl;
        matrix.print_matrix();
        matrix_from_file transposed_matrix = matrix.transpose();
        matrix_from_file inverse_matrix = matrix.inverse();
        matrix_from_file multiplied_matrix;
        while (true)
        {
            cout << "Print:"<< endl;
            cout << "1 - if u want to transpose your matrix" << endl;
            cout << "2 - if u want to multiply the matrix by the number" << endl;
            cout << "3 - if u want to find the determinant of a matrix" << endl;
            cout << "4 - if u want to write any matrix to .csv file" << endl;
            cout << "5 - if u want to inverse your matrix" << endl;
            cout << "0 - if u want to exit" << endl;
            cin >> request;
            if (request == 0)
            {
                break;
            }
            if ((request != 0) & (request != 1)& (request != 2)& (request != 3)& (request != 4))
            {
                cout << "Wrong request"<< endl;
            }
            if (request == 1)
            {
                transposed_matrix.print_matrix();
            }
            if (request == 2)
            {
                cout << "Print the number below:" << endl;
                cin >> multiply_number;
                multiplied_matrix = matrix.matrix_multiplication_number(multiply_number);
                multiplied_matrix.print_matrix();
            }
            if (request == 3)
            {
                cout << endl << matrix.determinate() << endl;
            }
            if (request == 4)
            {
                cout << "Which matrix do you want to write?" << endl;
                cout << "Print:" << endl;
                cout << "1 - if you want to write transposed matrix"<< endl;
                cout << "2 - if you want to write multiplied matrix" << endl;
                cout << "3 - if you want to write inverse matrix" << endl;
                cin >> request;
                if (request == 1)
                    transposed_matrix.write_to_csv();
                if (request == 2)
                    multiplied_matrix.write_to_csv();
                if (request == 3)
                    inverse_matrix.write_to_csv();
                cout << endl << "Done!"<< endl;
            }
            if (request == 5)
            {
                inverse_matrix.print_matrix();
            }
        }
    }
}

