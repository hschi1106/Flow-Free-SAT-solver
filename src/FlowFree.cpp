#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

bool isCertainCell(int row, int col, vector<vector<int>> CertainCell)
{
  for (auto it : CertainCell)
  {
    if (it[0] == row && it[1] == col)
      return true;
  }
  return false;
}

void testClauses(vector<vector<int>> clauses)
{
  cout << "total clauses: " << clauses.size() << endl;
  for (auto it : clauses)
  {
    for (auto itit : it)
    {
      cout << itit << " ";
    }
    cout << endl;
  }
}

void addStartEndCell(vector<vector<vector<int>>> P, vector<vector<int>> &clauses, vector<vector<int>> start_cells, vector<vector<int>> end_cells, int colors)
{
  for (int i = 0; i < colors; i++)
  {
    int tmp = P[start_cells[i][0]][start_cells[i][1]][i];
    clauses.push_back({tmp});
  }
  for (int i = 0; i < colors; i++)
  {
    int tmp = P[end_cells[i][0]][end_cells[i][1]][i];
    clauses.push_back({tmp});
  }
}

void atLeastOneColor(vector<vector<vector<int>>> P, vector<vector<int>> &clauses, int rows, int cols, int colors)
{
  vector<int> tmp;
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      for (int k = 0; k < colors; k++)
      {
        tmp.push_back(P[i][j][k]);
      }
      clauses.push_back(tmp);
      tmp.clear();
    }
  }
}

void atMostOneColor(vector<vector<vector<int>>> P, vector<vector<int>> &clauses, int rows, int cols, int colors)
{
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      for (int k = 0; k < colors; k++)
      {
        for (int l = k + 1; l < colors; l++)
        {
          clauses.push_back({-P[i][j][k], -P[i][j][l]});
        }
      }
    }
  }
}

void noneEndAtLeastOneDirection(vector<vector<vector<int>>> D, vector<vector<int>> &clauses, vector<vector<int>> end_cells, int rows, int cols)
{
  vector<int> tmp;
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      if (!isCertainCell(i, j, end_cells))
      {
        for (int k = 0; k < 4; k++)
        {
          tmp.push_back(D[i][j][k]);
        }
      }
      if (!tmp.empty())
        clauses.push_back(tmp);
      tmp.clear();
    }
  }
}

void noneEndAtMostOneDirection(vector<vector<vector<int>>> D, vector<vector<int>> &clauses, vector<vector<int>> end_cells, int rows, int cols)
{
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      if (!isCertainCell(i, j, end_cells))
      {
        for (int k = 0; k < 4; k++)
        {
          for (int l = k + 1; l < 4; l++)
          {
            clauses.push_back({-D[i][j][k], -D[i][j][l]});
          }
        }
      }
    }
  }
}

void startEndNeighborAtLeastMostOneSameColor(vector<vector<vector<int>>> P, vector<vector<int>> &clauses, vector<vector<int>> start_cells, vector<vector<int>> end_cells, int rows, int cols, int colors)
{
  vector<vector<int>> terminal_cells = start_cells;
  terminal_cells.insert(terminal_cells.end(), end_cells.begin(), end_cells.end());
  vector<vector<int>> neighbor;
  vector<int> tmp;
  for (int i = 0; i < colors; i++)
  {
    if (start_cells[i][0] - 1 >= 0 && !isCertainCell(start_cells[i][0] - 1, start_cells[i][1], terminal_cells))
    {
      tmp.push_back(P[start_cells[i][0] - 1][start_cells[i][1]][i]);
    }
    if (start_cells[i][0] + 1 < rows && !isCertainCell(start_cells[i][0] + 1, start_cells[i][1], terminal_cells))
    {
      tmp.push_back(P[start_cells[i][0] + 1][start_cells[i][1]][i]);
    }
    if (start_cells[i][1] - 1 >= 0 && !isCertainCell(start_cells[i][0], start_cells[i][1] - 1, terminal_cells))
    {
      tmp.push_back(P[start_cells[i][0]][start_cells[i][1] - 1][i]);
    }
    if (start_cells[i][1] + 1 < cols && !isCertainCell(start_cells[i][0], start_cells[i][1] + 1, terminal_cells))
    {
      tmp.push_back(P[start_cells[i][0]][start_cells[i][1] + 1][i]);
    }
    if (!tmp.empty())
    {
      clauses.push_back(tmp);
      neighbor.push_back(tmp);
    }

    tmp.clear();

    if (end_cells[i][0] - 1 >= 0 && !isCertainCell(end_cells[i][0] - 1, end_cells[i][1], terminal_cells))
    {
      tmp.push_back(P[end_cells[i][0] - 1][end_cells[i][1]][i]);
    }
    if (end_cells[i][0] + 1 < rows && !isCertainCell(end_cells[i][0] + 1, end_cells[i][1], terminal_cells))
    {
      tmp.push_back(P[end_cells[i][0] + 1][end_cells[i][1]][i]);
    }
    if (end_cells[i][1] - 1 >= 0 && !isCertainCell(end_cells[i][0], end_cells[i][1] - 1, terminal_cells))
    {
      tmp.push_back(P[end_cells[i][0]][end_cells[i][1] - 1][i]);
    }
    if (end_cells[i][1] + 1 < cols && !isCertainCell(end_cells[i][0], end_cells[i][1] + 1, terminal_cells))
    {
      tmp.push_back(P[end_cells[i][0]][end_cells[i][1] + 1][i]);
    }
    if (!tmp.empty())
    {
      clauses.push_back(tmp);
      neighbor.push_back(tmp);
    }
    tmp.clear();
  }
  for (auto it : neighbor)
  {
    for (int i = 0; i < it.size(); i++)
    {
      for (int j = i + 1; j < it.size(); j++)
      {
        clauses.push_back({-it[i], -it[j]});
      }
    }
  }
}

void noneEndPointToSameColor(vector<vector<vector<int>>> P, vector<vector<vector<int>>> D, vector<vector<int>> &clauses, vector<vector<int>> end_cells, int rows, int cols, int colors)
{
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      if (!isCertainCell(i, j, end_cells))
      {
        if (i - 1 >= 0)
        {
          for (int k = 0; k < colors; k++)
          {
            clauses.push_back({-D[i][j][0], -P[i][j][k], P[i - 1][j][k]});
          }
        }
        if (i + 1 < rows)
        {
          for (int k = 0; k < colors; k++)
          {
            clauses.push_back({-D[i][j][1], -P[i][j][k], P[i + 1][j][k]});
          }
        }
        if (j - 1 >= 0)
        {
          for (int k = 0; k < colors; k++)
          {
            clauses.push_back({-D[i][j][2], -P[i][j][k], P[i][j - 1][k]});
          }
        }
        if (j + 1 < cols)
        {
          for (int k = 0; k < colors; k++)
          {
            clauses.push_back({-D[i][j][3], -P[i][j][k], P[i][j + 1][k]});
          }
        }
      }
    }
  }
}

void twoCellsCantPointToEachOther(vector<vector<vector<int>>> D, vector<vector<int>> &clauses, int rows, int cols)
{
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      if (i - 1 >= 0)
      {
        clauses.push_back({-D[i][j][0], -D[i - 1][j][1]});
      }
      if (i + 1 < rows)
      {
        clauses.push_back({-D[i][j][1], -D[i + 1][j][0]});
      }
      if (j - 1 >= 0)
      {
        clauses.push_back({-D[i][j][2], -D[i][j - 1][3]});
      }
      if (j + 1 < cols)
      {
        clauses.push_back({-D[i][j][3], -D[i][j + 1][2]});
      }
    }
  }
}

void cantPointToBoundary(vector<vector<vector<int>>> D, vector<vector<int>> &clauses, int rows, int cols)
{
  for (int i = 0; i < cols; i++)
  {
    clauses.push_back({-D[0][i][0]});
    clauses.push_back({-D[rows - 1][i][1]});
  }
  for (int i = 0; i < rows; i++)
  {
    clauses.push_back({-D[i][0][2]});
    clauses.push_back({-D[i][cols - 1][3]});
  }
}

void cantPointToStart(vector<vector<vector<int>>> D, vector<vector<int>> &clauses, vector<vector<int>> start_cells, int rows, int cols)
{
  for (auto pos : start_cells)
  {
    if (pos[0] - 1 >= 0)
    {
      clauses.push_back({-D[pos[0] - 1][pos[1]][1]});
    }
    if (pos[0] + 1 < rows)
    {
      clauses.push_back({-D[pos[0] + 1][pos[1]][0]});
    }
    if (pos[1] - 1 >= 0)
    {
      clauses.push_back({-D[pos[0]][pos[1] - 1][3]});
    }
    if (pos[1] + 1 < cols)
    {
      clauses.push_back({-D[pos[0]][pos[1] + 1][2]});
    }
  }
}

void noneStartAtLeastPointedByOne(vector<vector<vector<int>>> D, vector<vector<int>> &clauses, vector<vector<int>> start_cells, int rows, int cols)
{
  vector<int> tmp;
  vector<vector<int>> neighbor;
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      if (!isCertainCell(i, j, start_cells))
      {
        if (i - 1 >= 0)
        {
          tmp.push_back(D[i - 1][j][1]);
        }
        if (i + 1 < rows)
        {
          tmp.push_back(D[i + 1][j][0]);
        }
        if (j - 1 >= 0)
        {
          tmp.push_back(D[i][j - 1][3]);
        }
        if (j + 1 < cols)
        {
          tmp.push_back(D[i][j + 1][2]);
        }
        if (!tmp.empty())
        {
          clauses.push_back(tmp);
          neighbor.push_back(tmp);
          tmp.clear();
        }
      }
    }
  }
  for (auto it : neighbor)
  {
    for (int i = 0; i < it.size(); i++)
    {
      for (int j = i + 1; j < it.size(); j++)
      {
        clauses.push_back({-it[i], -it[j]});
      }
    }
  }
}

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

  ifstream in;
  ofstream out;
  in.open(argv[1]);
  out.open(argv[2]);

  if (!in.is_open())
  {
    cout << "Failed to open file.\n";
    return 1;
  }

  int rows;
  int cols;
  int colors;
  vector<vector<int>> start_cells;
  vector<vector<int>> end_cells;
  int x, y;
  vector<int> tmp;

  in >> rows >> cols >> colors;

  for (int i = 0; i < colors; i++)
  {
    in >> x >> y;
    tmp = {x, y};
    start_cells.push_back(tmp);
  }
  for (int i = 0; i < colors; i++)
  {
    in >> x >> y;
    tmp = {x, y};
    end_cells.push_back(tmp);
  }

  vector<vector<vector<int>>> P(rows, vector<vector<int>>(cols, vector<int>(colors)));
  vector<vector<vector<int>>> D(rows, vector<vector<int>>(cols, vector<int>(4)));

  int count = 1;
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      for (int k = 0; k < colors; k++)
      {
        P[i][j][k] = count;
        count++;
      }
    }
  }
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      for (int k = 0; k < 4; k++)
      {
        D[i][j][k] = count;
        count++;
      }
    }
  }

  vector<vector<int>> terminal_cells = start_cells;
  terminal_cells.insert(terminal_cells.end(), end_cells.begin(), end_cells.end());

  vector<vector<int>> clauses;

  addStartEndCell(P, clauses, start_cells, end_cells, colors);
  atLeastOneColor(P, clauses, rows, cols, colors);
  atMostOneColor(P, clauses, rows, cols, colors);
  noneEndAtLeastOneDirection(D, clauses, end_cells, rows, cols);
  noneEndAtMostOneDirection(D, clauses, end_cells, rows, cols);
  startEndNeighborAtLeastMostOneSameColor(P, clauses, start_cells, end_cells, rows, cols, colors);
  noneEndPointToSameColor(P, D, clauses, end_cells, rows, cols, colors);
  twoCellsCantPointToEachOther(D, clauses, rows, cols);
  cantPointToBoundary(D, clauses, rows, cols);
  cantPointToStart(D, clauses, start_cells, rows, cols);
  noneStartAtLeastPointedByOne(D, clauses, start_cells, rows, cols);

  testClauses(clauses);

  out << "p"
      << " "
      << "cnf"
      << " " << rows * cols * (colors + 4) << " " << clauses.size() << endl;
  out << endl;
  for (auto it : clauses)
  {
    for (auto itit : it)
    {
      out << itit << " ";
    }
    out << "0" << endl;
  }

  return 0;
}