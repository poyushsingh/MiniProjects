#include <iostream>
#include <vector>
#define INT_MAX 2147483647

using namespace std;

class pair_our
{
public:
    int first;
    int second;
};

class Heap
{
public:
    long long hpsize;
    pair_our *ar_pr;
    Heap(long long n)
    {
        hpsize = 0;
        ar_pr = new pair_our[n];
    }

    void push(pair_our val)
    {
        long long ind = hpsize;
        ar_pr[ind].first = val.first;
        ar_pr[ind].second = val.second;
        hpsize = hpsize + 1;

        buildHeap(ar_pr, hpsize);
    }

    void heapify(pair_our arr[], long long size, long long i)
    {
        long long maxi = i;
        long long leftchild = 2 * i + 1;
        long long rightchild = 2 * i + 2;

        if (leftchild < size && arr[i].first > arr[leftchild].first)
        {
            maxi = leftchild;
        }
        if (rightchild < size && arr[maxi].first > arr[rightchild].first)
        {
            maxi = rightchild;
        }
        if (maxi != i)
        {
            swap(arr[maxi].first, arr[i].first);
            swap(arr[maxi].second, arr[i].second);
            heapify(arr, size, maxi);
        }
    }

    void buildHeap(pair_our arr[], long long N)
    {
        long long start_ind = (N / 2) - 1;
        for (long long i = start_ind; i >= 0; i--)
        {
            heapify(arr, N, i);
        }
    }

    bool isempty()
    {
        return (hpsize == 0);
    }

    void pop()
    {
        if (hpsize == 0)
        {
            return;
        }
        else if (hpsize == 1)
        {
            hpsize--;
            return;
        }

        ar_pr[0].first = ar_pr[hpsize - 1].first;
        ar_pr[0].second = ar_pr[hpsize - 1].second;
        hpsize--;

        buildHeap(ar_pr, hpsize);
    }

    pair_our top()
    {
        return ar_pr[0];
    }
};

int main()
{
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<int>> adj[n + 1];
    vector<int> police(n);
    vector<int> ans(n + 1, INT_MAX);
    Heap hp(m);

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        vector<int> t1, t2;
        t1.push_back(v);
        t1.push_back(w);
        adj[u].push_back(t1);
        t2.push_back(u);
        t2.push_back(w);
        adj[v].push_back(t2);
    }

    for (int i = 0; i < k; i++)
    {
        cin >> police[i];
        ans[police[i]] = 0;
        hp.push({0, police[i]});
    }

    // int **tmp;
    // tmp = new int *[3];
    // for (int i = 0; i < 3; i++)
    // {
    //     tmp[i] = new int[m];
    // }

    // for (int i = 0; i < m; i++)
    // {
    //     cin >> tmp[0][i] >> tmp[1][i] >> tmp[2][i];
    // }

    // int arr[3][2 * m];

    // int i;
    // for (i = 0; i < m; i++)
    // {
    //     arr[0][i] = tmp[0][i];
    //     arr[1][i] = tmp[1][i];
    //     arr[2][i] = tmp[2][i];
    // }

    // int z = 0;
    // for (int j = 0; j < m; j++)
    // {

    //     arr[0][m + j] = tmp[1][z];
    //     arr[1][m + j] = tmp[0][z];
    //     arr[2][m + j] = tmp[2][z];
    //     z++;
    // }

    // delete[] tmp;
    // Heap hp(m);
    // int ans[n + 1];

    // for (int i = 0; i < (n + 1); i++)
    // {
    //     ans[i] = INT_MAX;
    // }

    // int police[k];

    // for (int i = 0; i < k; i++)
    // {
    //     cin >> police[i];
    //     ans[police[i]] = 0;
    //     hp.push({0, police[i]});
    // }

    while (!hp.isempty())
    {
        pair_our p = hp.top();
        int dist = p.first;
        int node = p.second;

        hp.pop();

        for (auto it : adj[node])
        {
            int adj_node = it[0];
            int edge_weight = it[1];

            if (dist + edge_weight < ans[adj_node])
            {
                ans[adj_node] = dist + edge_weight;
                hp.push({ans[adj_node], adj_node});
            }
        }

        // for (int i = 0; i < 2 * m; i++)
        // {
        //     if (adj[0][i] == node)
        //     {
        //         int adj_node = adj[1][i];
        //         int edge_weight = arr[2][i];

        //         if (dist + edge_weight < ans[adj_node])
        //         {
        //             ans[adj_node] = dist + edge_weight;
        //             hp.push({ans[adj_node], adj_node});
        //         }
        //     }
        // }
    }

    for (int i = 1; i < n + 1; i++)
    {
        if (ans[i] == INT_MAX)
        {
            cout << "-1"
                 << " ";
        }
        else
        {
            cout << ans[i] << " ";
        }
    }
    cout << endl;
}