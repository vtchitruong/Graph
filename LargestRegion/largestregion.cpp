#include <bits/stdc++.h>

#define inputFile "lr4.inp"
#define outputFile "lr4.out"

using namespace std;

int nRow, mCol; // total rows and columns
vector<vector<int>> g; // grid, graph

void Input()
{
    ifstream f;
    f.open(inputFile);

    f >> nRow >> mCol;

    g.resize(nRow); // init rows of grid
    for (int r = 0; r < nRow; ++r)
    {
        g[r].resize(mCol); // init cols of each row in grid

        int x;
        for (int c = 0; c < mCol; ++c)
        {
            f >> x;
            g[r][c] = x;
        }
    }

    f.close();
}

int count(int r, int c, int max_r, int max_c)
{
    // out of boundaries
    if (r < 0 || r > max_r - 1 || c < 0 || c > max_c - 1)
        return 0;
    
    // value = 0, skip
    if (g[r][c] == 0)
        return 0;
        
    g[r][c] = 0; // change value of cell from 1 to 0 for not to be considered
    
    int res = 1;
    
    // 8 directions
    res += count(r - 1, c, max_r, max_c);
    res += count(r + 1, c, max_r, max_c);
    res += count(r, c - 1, max_r, max_c);
    res += count(r, c + 1, max_r, max_c);
    res += count(r - 1, c - 1, max_r, max_c);
    res += count(r - 1, c + 1, max_r, max_c);
    res += count(r + 1, c - 1, max_r, max_c);
    res += count(r + 1, c + 1, max_r, max_c);
    
    return res;
}

int maxRegion(int n, int m)
{
    int cell;
    int cell_max = 0;
    
    for (int row = 0; row < n; ++row)
    {
        for (int col = 0; col < m; ++col)
        {
            cell = count(row, col, n, m);
            if (cell > cell_max) cell_max = cell;
        }
    }
    return cell_max;
}

void Output()
{
    ofstream f;
    f.open(outputFile);

    int largestRegion = maxRegion(nRow, mCol);

    f << largestRegion;

    f.close();
}


int main()
{
    Input();
    Output();

    return 0;
}