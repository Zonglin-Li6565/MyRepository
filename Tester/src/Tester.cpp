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
#include <cmath>
#include <string>
#include <iostream>
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
      iss >> input(i, j);
    }
  }
}

matrix sigmoid(const matrix& input)
{
  matrix newmatrix(input.getdimension());
  for(size_t i = 0; i < input.getrowsize(); i++)
  {
    for(size_t j = 0; j < input.getcolumnsize(); j++)
    {
      newmatrix(i, j) = 1.0 / (1.0 + exp(0 - input.access(i, j)));
    }
  }
  return newmatrix;
}

matrix der_sigmoid(const matrix& input)
{
  matrix sig = sigmoid(input);
  return sig >> (1 - sig);
}

void normalize(matrix& input)
{
  double min = 10000.0;
  double max = -10000.0;
  for(size_t i = 0; i < input.getrowsize(); i++)
  {
    for(size_t j = 0; j < input.getcolumnsize(); j++)
    {
      if(input(i, j) < min) min = input(i, j);
      if(input(i, j) > max) max = input(i, j);
    }
  }
  for(size_t i = 0; i < input.getrowsize(); i++)
  {
    for(size_t j = 0; j < input.getcolumnsize(); j++)
    {
      input(i, j) = (input(i, j) - min) / (max - min);
    }
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
//    cout << "error = \n" << error.tostring() << endl;
    costs[i] = sum(((0 - desiredoutput) >> logmatrix(prediction)) - ((1 - desiredoutput) >> logmatrix(1 - prediction))) / M;
    cout << costs[i] << endl;
    double lambda = -0.05;
    s_node.backward(f_node.backward(error, lambda), lambda);
    f_node.updateweights();
    s_node.updateweights();
  }

}
