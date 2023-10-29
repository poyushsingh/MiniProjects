#include <iostream>
using namespace std;

int parent(int arr[], int x)
{
    while (arr[x] != -1)
    {
        cout << "hiii" << endl;
        x = arr[x];
    }
    return x;

    // if (arr[x] == -1)
    // {
    //     return x;
    // }
    // else
    // {
    //     return arr[x] = parent(arr, x);
    // }
}

int main()
{
    int n, m;
    cin >> n >> m;

    int arr[n + 1];
    int max_size[n + 1];
    int maxi = 1;
    for (int i = 0; i < n + 1; i++)
    {
        arr[i] = -1;
        max_size[i] = 1;
    }

    int no_of_parties = n;

    for (int i = 0; i < m; i++)
    {
        int flag = 0;
        int a, b;
        cin >> a >> b;
        if (arr[a] == -1 && arr[b] == -1 && (a != b))
        {
            arr[a] = b;
            max_size[a] += max_size[b];
            max_size[b] = max_size[a];
            maxi = max(maxi, max(max_size[b], max_size[a]));
            no_of_parties--;
            // for (int i = 0; i < n + 1; i++)
            // {
            //     cout << i << " - " << arr[i] << "     ";
            // }
            // cout << "max_size" << endl;
            // // cout << endl;
            // for (int i = 0; i < n + 1; i++)
            // {
            //     cout << i << " - " << max_size[i] << "     ";
            // }

            // cout << no_of_parties << " "
            //      << maxi << endl;
        }
        else if (arr[a] != -1 && arr[b] == -1 && (a != b))
        {
            int p1 = parent(arr, a);
            int p2 = parent(arr, b);

            if (p1 == p2)
            {
                flag = 1;
            }
            if (flag == 1)
            {
                // for (int i = 0; i < n + 1; i++)
                // {
                //     cout << i << " - " << arr[i] << "     ";
                // }
                // cout << "max_size" << endl;
                // for (int i = 0; i < n + 1; i++)
                // {
                //     cout << i << " - " << max_size[i] << "     ";
                // }
                // cout << no_of_parties << " "
                //      << maxi << endl;
            }
            else
            {
                arr[b] = p1;
                // max_size[b] += max_size[a];

                max_size[p2] += max_size[p1];

                max_size[p1] = max_size[p2];
                maxi = max(maxi, max(max_size[p2], max_size[p1]));
                no_of_parties--;
                // for (int i = 0; i < n + 1; i++)
                // {
                //     cout << i << " - " << arr[i] << "     ";
                // }
                // cout << "max_size" << endl;
                // for (int i = 0; i < n + 1; i++)
                // {
                //     cout << i << " - " << max_size[i] << "     ";
                // }
                // cout << no_of_parties << " "
                //      << maxi << endl;
            }
        }
        else if (arr[a] == -1 && arr[b] != -1 && (a != b))
        {
            int p1 = parent(arr, a);
            int p2 = parent(arr, b);

            if (parent(arr, a) == parent(arr, b))
            {
                flag = 1;
            }
            if (flag == 1)
            {
                // for (int i = 0; i < n + 1; i++)
                // {
                //     cout << i << " - " << arr[i] << "     ";
                // }
                // cout << "max_size" << endl;
                // for (int i = 0; i < n + 1; i++)
                // {
                //     cout << i << " - " << max_size[i] << "     ";
                // }
                // cout << no_of_parties << " "
                //      << maxi << endl;
            }
            else
            {
                arr[a] = p2;
                max_size[p1] += max_size[p2];
                max_size[p2] = max_size[p1];

                maxi = max(maxi, max(max_size[p2], max_size[p1]));
                no_of_parties--;
                // for (int i = 0; i < n + 1; i++)
                // {
                //     cout << i << " - " << arr[i] << "     ";
                // }
                // cout << "max_size" << endl;
                // for (int i = 0; i < n + 1; i++)
                // {
                //     cout << i << " - " << max_size[i] << "     ";
                // }
                // cout << no_of_parties << " "
                //      << maxi << endl;
            }
        }
        else if (arr[a] != -1 && arr[b] != -1 && (a != b))
        {
            if (parent(arr, a) == parent(arr, b))
            {
                flag = 1;
            }
            if (flag == 1)
            {
                // for (int i = 0; i < n + 1; i++)
                // {
                //     cout << i << " - " << arr[i] << "     ";
                // }
                // cout << "max_size" << endl;
                // for (int i = 0; i < n + 1; i++)
                // {
                //     cout << i << " - " << max_size[i] << "     ";
                // }
            }
            // cout << no_of_parties << " "
            //      << maxi << endl;
            else
            {
                int p1 = parent(arr, a);
                int p2 = parent(arr, b);

                arr[a] = p2;
                max_size[p1] += max_size[p2];
                max_size[p2] = max_size[p1];
                maxi = max(maxi, max(max_size[p2], max_size[p1]));
                no_of_parties--;
                // for (int i = 0; i < n + 1; i++)
                // {
                //     cout << i << " - " << arr[i] << "     ";
                // }
                // cout << "max_size" << endl;
                // for (int i = 0; i < n + 1; i++)
                // {
                //     cout << i << " - " << max_size[i] << "     ";
                // }
                // cout << no_of_parties << " "
                //      << maxi << endl;
                // }
            }
        }
        cout << no_of_parties << " "
             << maxi << endl;
    }
}