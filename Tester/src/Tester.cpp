//============================================================================
// Name        : Tester.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include "./Matrix/matrix.h"
#include "forwardnode.h"
#include <vector>
#include <stdexcept>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string>
#define TIMES 50
#define M 2000
using namespace std;

matrix input(M, 400);
matrix desiredoutput(M, 10);
double costs[TIMES];

void datareader()
{
  ifstream infile_x("X.txt");
  ifstream infile_y("Y.txt");
  string line;
  for(int i = 0; i < M && getline(infile_x, line); i++)
  {
    istringstream iss(line);
    for(int j = 399; j >= 0; j--)
    {
      iss >> input[i][j];
    }
  }
}

matrix& operator-(double first, matrix& second)
{
  matrix& newmatrix = *new matrix(second.getdimension());
  for(int i = 0; i < second.dimension_r_; i++)
  {
    for(int j = 0; j < second.dimension_c_; j++)
    {
      newmatrix[i][j] = first - second[i][j];
    }
  }
  return newmatrix;
}

matrix& sigmoid(matrix& input)
{
  matrix& newmatrix = *new matrix(input.getdimension());
  for(int i = 0; i < input.dimension_r_; i++)
  {
    for(int j = 0; j < input.dimension_c_; j++)
    {
      newmatrix[i][j] = 1.0 / (1.0 + exp( - input[i][j]));
    }
  }
  return newmatrix;
}

matrix& der_sigmoid(matrix& input)
{
  matrix& sig = sigmoid(input);
  return sig >> (1 - sig);
}

void normalize(matrix& input)
{
  double min = 10000.0;
  double max = -10000.0;
  for(int i = 0; i < input.getrowsize(); i++)
  {
    vector<double> row = input[i];
    for(int j = 0; j < input.dimension_c_; j++)
    {
      if(row[j] < min) min = row[j];
      if(row[j] > max) max = row[j];
    }
  }
  for(int i = 0; i < input.dimension_r_; i++)
  {
    vector<double> row = input[i];
    for(int j = 0; j < input.dimension_c_; j++)
      row[j] = (row[j] - min) / (max - min);
  }
}

int main() {
  datareader();
  dimension snd_inputdimension(M, 400);
  dimension snd_outputdimension(M, 50);
  dimension fst_inputdimension(M, 50);
  dimension fst_outputdimension(M, 10);
  forwardnode f_node(fst_outputdimension, fst_inputdimension);
  forwardnode s_node(snd_outputdimension, snd_inputdimension);
  f_node.setactivationfunction(&sigmoid);
  f_node.setderivativeactivation(&der_sigmoid);
  s_node.setactivationfunction(&sigmoid);
  s_node.setderivativeactivation(&der_sigmoid);
  normalize(input);
  for(int i = 0; i < TIMES; i++)
  {
    matrix prediction = f_node.forward(s_node.forward(input));
    matrix error = prediction - desiredoutput;
    costs[i] = sum(((0 - desiredoutput) >> log(prediction)) - ((1 - desiredoutput) >> log(1 - prediction))) / M;
    cout << costs[i] << endl;
    double lambda = 0.1;
    s_node.backward(f_node.backward(error, lambda), lambda);
    f_node.weighterrors_ = &(*f_node.weighterrors_ / M);
    s_node.weighterrors_ = &(*s_node.weighterrors_ / M);
    f_node.updateweights();
    s_node.updateweights();
  }

}
