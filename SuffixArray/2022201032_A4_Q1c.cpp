#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*accepted on leetcode*/

// struct suffix
// {
//     int index;
//     int rank[2];
// };

// bool cmp(struct suffix a, struct suffix b)
// {
//     if (a.rank[0] == b.rank[0])
//     {
//         return a.rank[1] < b.rank[1];
//     }
//     else
//     {
//         return a.rank[0] < b.rank[0];
//     }
// }

// void merge(struct suffix arr[], struct suffix temp[], int l, int mid, int r)
// {
//     int i, j, k;
//     i = l;
//     j = mid;
//     k = l;

//     while ((i <= mid - 1) && (j <= r))
//     {
//         if (cmp(arr[i], arr[j]))
//         {
//             temp[k++] = arr[i++];
//         }
//         else
//         {
//             temp[k++] = arr[j++];
//         }
//     }
//     while (i <= mid - 1)
//     {
//         temp[k++] = arr[i++];
//     }

//     while (j <= r)
//     {
//         temp[k++] = arr[j++];
//     }

//     for (int i = l; i <= r; i++)
//     {
//         arr[i] = temp[i];
//     }
// }

// void mergesort(struct suffix arr[], struct suffix temp[], int l, int r)
// {
//     int mid;
//     if (l < r)
//     {
//         mid = (l + r) / 2;
//         mergesort(arr, temp, l, mid);
//         mergesort(arr, temp, mid + 1, r);
//         merge(arr, temp, l, mid + 1, r);
//     }
// }

// // int cmp(struct suffix a, struct suffix b)
// // {
// //     return (a.rank[0] == b.rank[0]) ? (a.rank[1] < b.rank[1] ? 1 : 0) : (a.rank[0] < b.rank[0] ? 1 : 0);
// // }

// vector<int> build_suffix_array(string txt, int n)
// {
//     struct suffix suffixes[n];

//     for (int i = 0; i < n; i++)
//     {
//         suffixes[i].index = i;
//         suffixes[i].rank[0] = txt[i] - 'a';
//         suffixes[i].rank[1] = ((i + 1) < n) ? (txt[i + 1] - 'a') : -1;
//     }

//     // sort(suffixes, suffixes + n, cmp);
//     struct suffix tmp1[n];
//     mergesort(suffixes, tmp1, 0, n - 1);

//     int ind[n];
//     for (int k = 4; k < 2 * n; k = k * 2)
//     {
//         int rank = 0;
//         int prev_rank = suffixes[0].rank[0];
//         suffixes[0].rank[0] = rank;
//         ind[suffixes[0].index] = 0;

//         for (int i = 1; i < n; i++)
//         {
//             if (suffixes[i].rank[0] == prev_rank &&
//                 suffixes[i].rank[1] == suffixes[i - 1].rank[1])
//             {
//                 prev_rank = suffixes[i].rank[0];
//                 suffixes[i].rank[0] = rank;
//             }
//             else
//             {
//                 prev_rank = suffixes[i].rank[0];
//                 suffixes[i].rank[0] = ++rank;
//             }
//             ind[suffixes[i].index] = i;
//         }

//         for (int i = 0; i < n; i++)
//         {
//             int nextindex = suffixes[i].index + k / 2;
//             suffixes[i].rank[1] = (nextindex < n) ? suffixes[ind[nextindex]].rank[0] : -1;
//         }

//         // sort(suffixes, suffixes + n, cmp);
//         struct suffix tmp1[n];
//         mergesort(suffixes, tmp1, 0, n - 1);
//     }

//     vector<int> suffixArr;
//     for (int i = 0; i < n; i++)
//         suffixArr.push_back(suffixes[i].index);

//     return suffixArr;
// }

// vector<int> kasai(string txt, vector<int> suffixArr)
// {
//     int n = suffixArr.size();

//     vector<int> lcp(n, 0);

//     vector<int> inside_suffix(n, 0);

//     for (int i = 0; i < n; i++)
//         inside_suffix[suffixArr[i]] = i;

//     int k = 0;

//     for (int i = 0; i < n; i++)
//     {
//         if (inside_suffix[i] == n - 1)
//         {
//             k = 0;
//             continue;
//         }

//         int j = suffixArr[inside_suffix[i] + 1];

//         while (i + k < n && j + k < n && txt[i + k] == txt[j + k])
//             k++;

//         lcp[inside_suffix[i]] = k;

//         if (k > 0)
//             k--;
//     }

//     return lcp;
// }

// void printArr(vector<int> arr, int n)
// {
//     for (int i = 0; i < n; i++)
//         cout << arr[i] << " ";
//     cout << endl;
// }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct suffix
{
    int index;
    int rank[2];
} piyush;

static bool cmp(piyush a, piyush b)
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

    vector<int> suffixArr(n);
    for (int i = 0; i < n; i++)
        suffixArr[i] = suffixes[i].index;

    return suffixArr;
}

vector<int> kasai(string txt, vector<int> suffixArr)
{
    int n = suffixArr.size();

    vector<int> lcp(n, 0);

    vector<int> inside_suffix(n, 0);

    for (int i = 0; i < n; i++)
        inside_suffix[suffixArr[i]] = i;

    int k = 0;

    for (int i = 0; i < n; i++)
    {
        if (inside_suffix[i] == n - 1)
        {
            k = 0;
            continue;
        }

        int j = suffixArr[inside_suffix[i] + 1];

        while (i + k < n && j + k < n && txt[i + k] == txt[j + k])
            k++;

        lcp[inside_suffix[i]] = k;

        if (k > 0)
            k--;
    }

    return lcp;
}

void printArr(vector<int> arr, string updated_str, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << "-->" << updated_str.substr(arr[i]);

        cout << endl;
    }
}

struct pair_our
{
    int first;
    int second;
};

static bool cmpoo(pair_our a, pair_our b)
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

int main()
{
    string str = "";

    cin >> str;

    string tmp = str;
    int str_size = str.size();
    reverse(str.begin(), str.end());
    string updated_str = tmp + "@" + str;
    // cout << "updated_str - " << updated_str << endl;
    int updated_str_size = updated_str.length();

    vector<int> suffixArr = build_suffix_array(updated_str, updated_str.length());
    int n = suffixArr.size();

    //     cout << "Suffix Array : \n";
    //     printArr(suffixArr, updated_str, n);

    vector<int> lcp = kasai(updated_str, suffixArr);

    // cout << "\nLCP Array : \n";
    // printArr(lcp, updated_str, n);

    pair_our pair_;
    vector<pair_our> vec;

    int size = lcp.size();
    int maxlen = 1;
    int va = suffixArr[1];
    for (int i = 1; i < updated_str_size; i++)
    {
        // cout << "qwer" << endl;
        if (lcp[i - 1] > maxlen)
        {
            if ((updated_str_size - suffixArr[i - 1] > str_size && updated_str_size - suffixArr[i] <= str_size))
            {
                int var = updated_str_size - (suffixArr[i] + lcp[i - 1]);
                if (var == suffixArr[i - 1])
                {
                    maxlen = lcp[i - 1];
                    va = suffixArr[i - 1];
                }
            }
            else if (updated_str_size - suffixArr[i - 1] <= str_size && updated_str_size - suffixArr[i] > str_size)
            {
                int var = updated_str_size - (suffixArr[i - 1] + lcp[i - 1]);
                if (var == suffixArr[i])
                {
                    maxlen = lcp[i - 1];
                    va = suffixArr[i];
                }
            }

            // cout << "!W" << endl;

            // vec.push_back({lcp[i - 1], (i - 1)});
        }
    }
    cout << updated_str.substr(va, maxlen) << endl;

    // sort(vec.begin(), vec.end(), cmpoo);

    // for (auto itr : vec)
    // {
    //     cout << itr.first << " " << itr.second << endl;
    // }

    // string ans = "";

    // int cnt = vec[0].first;

    // int i = suffixArr[vec[0].second];

    // while (cnt--)
    // {
    //     ans += updated_str[i];
    //     i++;
    // }

    // cout << ans << endl;

    return 0;
}
