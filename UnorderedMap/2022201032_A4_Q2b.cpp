#include <iostream>
#include <vector>
using namespace std;

int compute_hash(int x)
{
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    if (x < 0)
    {
        return -x;
    }
    else
    {
        return x;
    }
}

int compute_hash(string str)
{
    int hash = 7;
    for (int i = 0; i < str.length(); i++)
    {
        hash = hash * 31 + str[i];
    }
    if (hash < 0)
    {
        return -hash;
    }
    else
    {
        return hash;
    }
}

template <class T1, class T2>
class unordered_map
{
public:
    struct Node
    {
        T1 key;
        T2 val;
        bool is_last = 1;
        Node *next = NULL;
    };

    int size;
    int capacity;
    Node *arr[1543];
    unordered_map()
    {
        size = 0;
        capacity = 1543;
        for (int i = 0; i < capacity; i++)
        {
            Node *tmp_new_node = new Node();
            tmp_new_node->key = 0;
            tmp_new_node->val = 0;
            tmp_new_node->is_last = 1;
            arr[i] = tmp_new_node;
        }
    }

    bool string_flag_T1 = 0;
    bool string_flag_T2 = 0;
    T1 typevalue_T1;
    T2 typevalue_T2;

    int modifiedtype_T1()
    {
        if (typeid(T1).name() == typeid(10).name())
        {
            typevalue_T1 = (int)0;
        }
        else if (typeid(T1).name() == typeid((float)3.14).name() || typeid(T1).name() == typeid((double)3.14).name())
        {
            typevalue_T1 = (float)(0.0);
        }
        else if (typeid(T1).name() == typeid('p').name())
        {
            typevalue_T1 = '\0';
        }
        else
        {
            typevalue_T1 = {};
            string_flag_T1 = 1;
        }
        return 0;
    }

    int modifiedtype_T2()
    {
        if (typeid(T2).name() == typeid(10).name())
        {
            typevalue_T2 = (int)0;
        }
        else if (typeid(T2).name() == typeid((float)3.14).name() || typeid(T2).name() == typeid((double)3.14).name())
        {
            typevalue_T2 = (float)(0.0);
        }
        else if (typeid(T2).name() == typeid('p').name())
        {
            typevalue_T2 = '\0';
        }
        else
        {
            typevalue_T2 = {};
            string_flag_T2 = 1;
        }
        return 0;
    }

    void insert(T1 key, T2 val)
    {
        Node *new_node = new Node();

        int received_hash = compute_hash(key);

        if (arr[received_hash % capacity]->is_last == 1)
        { // empty slot
            arr[received_hash % capacity]->key = key;
            arr[received_hash % capacity]->val = val;
            arr[received_hash % capacity]->is_last = 0;
            arr[received_hash % capacity]->next = new_node;
            size++;
        }
        else
        {
            // need to do chaining and check if key is already present or not.
            Node *tmp = arr[received_hash % capacity];

            while (tmp->key != key && tmp->is_last != 1)
            {
                tmp = tmp->next;
            }

            if (tmp->key == key)
            {
                if (key < 0)
                {
                    erase(key);
                }
                else
                {
                    tmp->key = key;
                    tmp->val = val;
                }
            }
            else if (tmp->is_last == 1)
            {
                size++;
                Node *new_node = new Node();
                tmp->key = key;
                tmp->val = val;
                tmp->is_last = 0;
                tmp->next = new_node;
            }
        }
    }

    bool find(T1 key)
    {
        int received_hash = compute_hash(key);
        Node *tmp = arr[received_hash % capacity];

        while (tmp->is_last != 1)
        {
            if (tmp->key == key)
            {
                return true;
            }
            tmp = tmp->next;
        }
        return false;
    }

    void erase(T1 key)
    {
        int received_hash = compute_hash(key);
        Node *tmp = arr[received_hash % capacity];

        Node *prev = NULL;

        if (find(key))
        {
            while (tmp->is_last != 1)
            {
                if (tmp->key == key)
                {
                    if (prev == NULL)
                    {

                        if (tmp->next->is_last == 1)
                        {
                            Node *new_node = new Node();
                            delete tmp->next;
                            arr[received_hash % capacity] = new_node;
                            size--;
                            return;
                        }
                        else
                        {
                            arr[received_hash % capacity] = tmp->next;
                            delete tmp;
                            size--;
                            return;
                        }
                    }
                    else
                    {
                        prev->next = tmp->next;
                        delete tmp;
                        size--;
                        return;
                    }
                }
                prev = tmp;
                tmp = tmp->next;
            }
        }
    }

    T2 operator[](T1 key)
    {
        if (find(key))
        {
            int received_hash = compute_hash(key);
            Node *tmp = arr[received_hash % capacity];
            while (tmp->key != key)
            {
                tmp = tmp->next;
            }
            // cout << "inside overload function - " << tmp->val << endl;
            return tmp->val;
        }
        else
        {
            // cout << "NOT FOUND" << endl;
            modifiedtype_T2();
            return typevalue_T2;
        }
    }

    void print()
    {

        for (int i = 0; i < capacity; i++)
        {
            if (arr[i]->is_last == 1)
            {
                cout << "empty " << i << endl;
            }
            else
            {
                Node *tmp = arr[i];

                while (tmp->is_last != 1)
                {
                    cout << tmp->key << " " << tmp->val << "--->";
                    tmp = tmp->next;
                }
                cout << endl;
            }
        }
        cout << endl;
        cout << endl;
    }
};

int main()
{
    int n, k;
    cin >> n >> k;

    if (k > n)
    {
        cout << "No group can be formed" << endl;
        // return;
    }
    else
    {
        vector<int> vec(n);

        for (int i = 0; i < n; i++)
        {
            cin >> vec[i];
        }

        unordered_map<int, int> mp;
        int dist_cnt = 0;

        for (int i = 0; i < k; i++)
        {
            int tmp = mp[vec[i]];
            if (tmp == 0)
            {
                dist_cnt++;
            }
            mp.insert(vec[i], tmp + 1);
        }
        // cout << mp.size << " ";
        cout << dist_cnt << " ";

        for (int i = k; i < n; i++)
        {
            int tmp1 = mp[vec[i - k]];
            if (tmp1 == 1)
            {
                dist_cnt--;
            }
            mp.insert(vec[i - k], tmp1 - 1);

            int tmp2 = mp[vec[i]];
            if (tmp2 == 0)
            {
                dist_cnt++;
            }
            mp.insert(vec[i], tmp2 + 1);

            cout << dist_cnt << " ";
        }
    }
    return 0;
}
