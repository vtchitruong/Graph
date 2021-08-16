#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g; // grid, graph

int count(int r, int c, int max_r, int max_c)
{
    if (r < 0 || r > max_r - 1 || c < 0 || c > max_c - 1)
        return 0;
        
    if (g[r][c] == 0)
        return 0;
        
    g[r][c] = 0; // change value of cell from 1 to 0 for not to be considered
    
    int res = 1;
    
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

int maxRegion(int n, int m, vector<vector<int>> grid)
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

int main()
{

    return 0;
}