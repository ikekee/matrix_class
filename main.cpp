#include <iostream>
#include "matrix_class.h"
#include <iomanip>
using namespace std;


vector<vector<double>> mass_by_variant(int variant)
{
    vector<vector <double> > array;
    string line;
    ifstream in("E:\\Task.txt");
    double iterations_number = 0;
    if (in.is_open())
    {
        char symbol;
        while(true)
        {
            in.get(symbol);
            if (symbol == '\n')
            {
                in.get(symbol);
                if (symbol == '\n')
                {
                    iterations_number++;
                    if (iterations_number == variant)
                    {break;}
                }
            }
        }
        double number;
        array.clear();
        while(array.size() < 12)
        {
            vector<double> row;
            while(row.size() < 12)
            {
                in >> number;
                row.push_back(number);
            }
            array.push_back(row);
        }
    }
    in.close();
    return array;
}



vector<vector <double> > new_matrix (int first_index, int second_index, vector<vector <double> > matrix)
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
    return minor;
}

vector<vector<double>> transpose(vector<vector<double>> matrix)
{
    double tmp;
    for(int i = 0; i < matrix.size(); ++i)
    {
        for(int j = i; j < matrix.size(); ++j)
        {
            tmp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = tmp;
        }
    }
    return matrix;
}

std::vector<double> subtract_line(std::vector<double> one, std::vector<double> two) {
    for (int q = 0; q < one.size(); q++)
        one[q] -= two[q];
    return one;
}

std::vector<double> multiply_line(std::vector<double> one, double number) {
    for (int q = 0; q < one.size(); q++)
        one[q] *= number;
    return one;
}

double determinate(vector<vector<double>> matrix) {
    for (int q = 0; q < matrix.size(); q++)
        for (int w = q + 1; w < matrix.size(); w++)
            matrix[w] = subtract_line(matrix[w],multiply_line(matrix[q], matrix[w][q] / matrix[q][q]));
    double det = 1;
    for (int q = 0; q < matrix.size(); q++)
        det *= matrix[q][q];
    return det;
}

/*double determinate1 (double det, vector<vector <double> > matrix)
{
    det = 0;
    int counter = 0;
    if (matrix.size() == 2)
    {
        det = matrix[0][0]*matrix[1][1]-matrix[0][1]*matrix[1][0];
        return det;
    }
    for(int i = 0; i < matrix.size(); i++)
    {
        if (counter%2 == 0)
        {
            det += matrix[0][i]*determinate(det, new_matrix(i, matrix));
            counter++;
        }
        else
        {
            det -= matrix[0][i]*determinate(det, new_matrix(i, matrix));
            counter++;
        }
    }
    return det;
}
 vector <vector<double>> matrix = {
            {1,2,2},
            {4,1,6},
            {7,6,9}
    };
    vector <vector<double>> matrix = {
            {1,2,2,5,6},
            {4,1,6,5,2},
            {7,6,9,1,6},
            {2,6,4,3,2},
            {8,5,6,3,2}
    };
*/


vector<vector<double>> inverse (vector<vector<double>> matrix)
{
    vector<vector<double>> inverse_matrix = matrix;
    int counter = 0;
    double multiplier = 1/determinate(matrix);
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix.size(); j++)
        {
            if (counter%2 == 0)
            {
                inverse_matrix[i][j] = multiplier * determinate(new_matrix(i, j, matrix));
                counter++;
            }
            else
            {
                inverse_matrix[i][j] = multiplier * -determinate(new_matrix(i, j, matrix));;
                counter++;
            }
        }
    }
    return transpose(inverse_matrix);
}

int main() {
    interface *UI = new interface;
    (*UI).create_interface();
    delete UI;
    return 0;
}





