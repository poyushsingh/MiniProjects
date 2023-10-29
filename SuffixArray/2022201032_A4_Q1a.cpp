#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// GLOBAL WALA COMMENT//

/*
struct suffix
{
    int index;
    int rank[2];
};

struct suffix suffixes[1000000 + 10];
vector<int> suffixArr;
vector<int> lcp(1000000 + 10, 0);
vector<int> invSuff(1000000 + 10, 0);
string str = "";
string modified_s = "";
vector<int> ans;

int cmp(struct suffix a, struct suffix b)
{
    return (a.rank[0] == b.rank[0]) ? (a.rank[1] < b.rank[1] ? 1 : 0) : (a.rank[0] < b.rank[0] ? 1 : 0);
}

vector<int> build_suffix_array(string txt, int n)
{
    // struct suffix suffixes[n];

    for (int i = 0; i < n; i++)
    {
        suffixes[i].index = i;
        suffixes[i].rank[0] = txt[i] - 'a';
        suffixes[i].rank[1] = ((i + 1) < n) ? (txt[i + 1] - 'a') : -1;
    }

    sort(suffixes, suffixes + n, cmp);

    int ind[n];
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

        sort(suffixes, suffixes + n, cmp);
    }

    // vector<int> suffixArr;
    for (int i = 0; i < n; i++)
        suffixArr.push_back(suffixes[i].index);

    return suffixArr;
}

vector<int> kasai(string txt, vector<int> suffixArr)
{
    int n = suffixArr.size();

    // vector<int> lcp(n, 0);

    // vector<int> invSuff(n, 0);

    for (int i = 0; i < n; i++)
        invSuff[suffixArr[i]] = i;

    int k = 0;

    for (int i = 0; i < n; i++)
    {
        if (invSuff[i] == n - 1)
        {
            k = 0;
            continue;
        }

        int j = suffixArr[invSuff[i] + 1];

        while (i + k < n && j + k < n && txt[i + k] == txt[j + k])
            k++;

        lcp[invSuff[i]] = k;

        if (k > 0)
            k--;
    }

    return lcp;
}

void printArr(vector<int> arr, int n)
{
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

struct pair_our
{
    int first;
    int second;
};

bool cmpoo(pair_our a, pair_our b)
{
    if (a.first == b.first)
    {
        return a.second < b.second;
    }
    else
    {
        return a.first > b.first;
    }
}
*/

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct suffix
{
    int index;
    int rank[2];
} piyush;

bool cmp(piyush a, piyush b)
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

void merge(piyush arr[], piyush temp[], int l, int mid, int r)
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

void mergesort(piyush arr[], piyush temp[], int l, int r)
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

vector<int> build_suffix_array(string txt, int n)
{
    piyush suffixes[n];

    for (int i = 0; i < n; i++)
    {
        suffixes[i].index = i;
        suffixes[i].rank[0] = txt[i] - 'a';
        suffixes[i].rank[1] = ((i + 1) < n) ? (txt[i + 1] - 'a') : -1;
    }

    piyush tmp1[n];
    mergesort(suffixes, tmp1, 0, n - 1);

    int ind[n];
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

        mergesort(suffixes, tmp1, 0, n - 1);
    }

    // int *suffixArr = new int[n];
    vector<int> suffixArr(n);
    for (int i = 0; i < n; i++)
        suffixArr[i] = suffixes[i].index;

    return suffixArr;
}

void printArr(vector<int> arr, int n)
{
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main()
{
    // string txt = "dcabcadcabca";
    // int n = txt.size();
    // vector<int> suffixArr = build_suffix_array(txt, n);
    // cout << "Following is suffix array for " << txt << endl;
    // printArr(suffixArr, n);

    string str = "";
    cin >> str;

    string modified_s = str + str;

    vector<int> ans;
    ans = build_suffix_array(modified_s, modified_s.length());

    // for (auto itr : ans)
    // {
    //     cout << itr << " ";
    // }

    // cout << endl;

    int i;
    for (i = 0; i < modified_s.length(); i++)
    {
        if (ans[i] + str.length() - 1 < modified_s.length())
        {
            break;
        }
    }

    int k = ans[i];

    for (; k < ans[i] + str.length(); k++)
    {
        cout << modified_s[k];
    }
    cout << endl;

    // cout << ans[i];

    return 0;
}