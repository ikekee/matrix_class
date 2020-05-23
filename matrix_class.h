#ifndef UNTITLED2_MATRIX_CLASS_H
#define UNTITLED2_MATRIX_CLASS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class matrix_from_file
{
private:
    vector<vector <double> >array;

    matrix_from_file constructor(vector<vector<double>> arr);

    vector<double> subtract_line(vector<double> one, vector<double> two);

    vector<double> multiply_line(vector<double> one, double number);

    matrix_from_file new_matrix (int first_index, int second_index, vector<vector <double> > matrix);


public:

    void mass_by_variant(int variant);

    matrix_from_file transpose();

    matrix_from_file matrix_multiplication_number(double number);

    matrix_from_file inverse ();

    void  write_to_csv();

    double determinate();
    void print_matrix();
};

class interface
{
private:
    int request;
    int var;
    double multiply_number;
    matrix_from_file matrix;
public:
    int create_interface();
};



#endif //UNTITLED2_MATRIX_CLASS_H