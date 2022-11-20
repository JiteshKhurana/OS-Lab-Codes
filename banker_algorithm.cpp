#include <iostream>
using namespace std;

int main()
{

    int n = 5; // No of processes
    int m = 3; // No of resources
    int alloc[5][3] = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};
    int max[5][3] = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {4, 2, 2}, {5, 3, 3}};
    int available[3] = {3, 3, 2}; // Available resources

    int need[n][m];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    int finish[n], ans[n], ind = 0;
    memset(finish, 0, sizeof(finish));

    for (int k = 0; k < 5; k++)
    {
        for (int i = 0; i < n; i++)
        {
            if (finish[i] == 0)
            {
                int flag = 0;
                for (int j = 0; j < m; j++)
                {
                    if (need[i][j] > available[j])
                    {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0)
                {
                    ans[ind++] = i;
                    for (int y = 0; y < m; y++)
                    {
                        available[y] += alloc[i][y];
                        finish[i] = 1;
                    }
                }
            }
        }
    }

    int flag = 1;

    for (int i = 0; i < n; i++)
    {
        if (finish[i] == 0)
        {
            flag = 0;
            cout << "The given sequence is not safe";
            break;
        }
    }

    if (flag == 1)
    {
        cout << "Following is the SAFE Sequence" << endl;
        for (int i = 0; i < n; i++)
            cout << " P" << ans[i] << " ->";
    }

    return (0);
}
