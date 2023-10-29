#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define int long long
#define endl "\n"
vector<int> lcp_arr;
// priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> hp;
string str = "";

struct suffix
{
    int index;
    int rank[2];
};

struct suffix temp1[1000000 + 10];
struct suffix suffixes[1000000 + 10];
int ind[1000000 + 10];
vector<int> suffixArr;

bool cmp(struct suffix a, struct suffix b)
{
    if (a.rank[0] == b.rank[0])
    {
        return a.rank[1] < b.rank[1];
    }
    else
    {
        return a.rank[0] < b.rank[0];
    }
}

void merge(struct suffix arr[], struct suffix temp[], int l, int mid, int r)
{
    int i, j, k;
    i = l;
    j = mid;
    k = l;

    while ((i <= mid - 1) && (j <= r))
    {
        if (cmp(arr[i], arr[j]))
        {
            temp[k++] = arr[i++];
        }
        else
        {
            temp[k++] = arr[j++];
        }
    }
    while (i <= mid - 1)
    {
        temp[k++] = arr[i++];
    }

    while (j <= r)
    {
        temp[k++] = arr[j++];
    }

    for (int i = l; i <= r; i++)
    {
        arr[i] = temp[i];
    }
}

void mergesort(struct suffix arr[], struct suffix temp[], int l, int r)
{
    int mid;
    if (l < r)
    {
        mid = (l + r) / 2;
        mergesort(arr, temp, l, mid);
        mergesort(arr, temp, mid + 1, r);
        merge(arr, temp, l, mid + 1, r);
    }
}

// int cmp(struct suffix a, struct suffix b)
// {
//     return (a.rank[0] == b.rank[0]) ? (a.rank[1] < b.rank[1] ? 1 : 0) : (a.rank[0] < b.rank[0] ? 1 : 0);
// }

vector<int> build_suffix_array(string txt, int n)
{
    // struct suffix suffixes[n];

    for (int i = 0; i < n; i++)
    {
        suffixes[i].index = i;
        suffixes[i].rank[0] = txt[i] - 'a';
        suffixes[i].rank[1] = ((i + 1) < n) ? (txt[i + 1] - 'a') : -1;
    }

    // sort(suffixes, suffixes + n, cmp);
    mergesort(suffixes, temp1, 0, n - 1);

    // int ind[n];
    for (int k = 4; k < 2 * n; k = k * 2)
    {
        int rank = 0;
        int prev_rank = suffixes[0].rank[0];
        suffixes[0].rank[0] = rank;
        ind[suffixes[0].index] = 0;

        for (int i = 1; i < n; i++)
        {

            if (suffixes[i].rank[0] == prev_rank &&
                suffixes[i].rank[1] == suffixes[i - 1].rank[1])
            {
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = rank;
            }
            else
            {
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = ++rank;
            }
            ind[suffixes[i].index] = i;
        }

        for (int i = 0; i < n; i++)
        {
            int nextindex = suffixes[i].index + k / 2;
            suffixes[i].rank[1] = (nextindex < n) ? suffixes[ind[nextindex]].rank[0] : -1;
        }

        // sort(suffixes, suffixes + n, cmp);
        mergesort(suffixes, temp1, 0, n - 1);
    }

    // vector<int> suffixArr;
    for (int i = 0; i < n; i++)
    {
        suffixArr.push_back(suffixes[i].index);
    }

    return suffixArr;
}

vector<int> lcp(1000000 + 10, 0);
vector<int> inside_suffix(1000000 + 10, 0);

vector<int> kasai(string txt, vector<int> suffixArr, int x)
{
    int n = suffixArr.size();

    // vector<int> lcp(n, 0);

    // vector<int> inside_suffix(n, 0);

    for (int i = 0; i < n; i++)
        inside_suffix[suffixArr[i]] = i;

    int k = 0;

    for (int i = 0; i < n; i++)
    {

        if (inside_suffix[i] + x - 1 > n - 1)
        {
            k = 0;
            continue;
        }

        int j = suffixArr[inside_suffix[i] + x - 1];

        while (i + k < n && j + k < n && txt[i + k] == txt[j + k])
            k++;

        lcp[inside_suffix[i]] = k;

        if (k > 0)
            k--;
    }

    // return the constructed lcp array
    return lcp;
}

// Utility function to print an array
void printArr(vector<int> arr, int n)
{
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int32_t main()
{
    // fastio;

    int k, nr;
    cin >> k >> nr;
    // cout << k << endl;

    cin >> str;
    // cout << str << endl;

    // int n = str.length();

    // if (k == 1)
    // {
    //     cout << nr << endl;
    // }
    // else
    // {
    // suffixArr.clear();
    suffixArr = build_suffix_array(str, str.length());
    int n = suffixArr.size();

    // cout << "Suffix Array : \n";
    // printArr(suffixArr, n);
    // lcp_arr.clear();
    lcp_arr = kasai(str, suffixArr, k);
    // cout << "\nLCP Array : \n";
    // printArr(lcp_arr, n);

    int maxi = -1e8;

    for (int i = 0; i < lcp_arr.size(); i++)
    {
        maxi = max(maxi, lcp_arr[i]);
    }

    cout << maxi << endl;
    // }

    //     int maxi = -1e9;

    //     for (int i = 0; i < k - 1; i++)
    //     {
    //         hp.push({lcp_arr[i], i});
    //     }

    //     maxi = max(maxi, hp.top().first);

    //     for (int i = k - 1; i < n; i++)
    //     {
    //         hp.push({lcp_arr[i], i});
    //         while (hp.top().second <= i - k + 1)
    //         {
    //             hp.pop();
    //         }

    //         maxi = max(maxi, hp.top().first);
    //     }

    //     cout << maxi << endl;
    // }
    return 0;
}