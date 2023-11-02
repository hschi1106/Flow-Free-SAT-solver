#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
  if (argc == 1)
  {
    cout << "No input file.\n";
    return 1;
  }
  if (argc == 2)
  {
    cout << "No output path.\n";
    return 1;
  }

  ifstream in, satin;
  ofstream out;
  in.open(argv[1]);
  satin.open(argv[2]);
  out.open(argv[3]);

  int rows;
  int cols;
  int colors;
  string sat;

  in >> rows >> cols >> colors;
  satin >> sat;
  cout << sat << endl;

  vector<vector<vector<int>>> P(rows, vector<vector<int>>(cols, vector<int>(colors)));
  vector<vector<int>> Graph(rows, vector<int>(cols));

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      for (int k = 0; k < colors; k++)
      {
        satin >> P[i][j][k];
      }
    }
  }

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      for (int k = 0; k < colors; k++)
      {
        if (P[i][j][k] > 0)
        {
          Graph[i][j] = k + 1;
        }
      }
    }
  } 

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      cout << Graph[i][j];
    }
    cout << endl;
  }
}