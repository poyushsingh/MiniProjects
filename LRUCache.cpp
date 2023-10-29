#include<stdio.h>
#include<iostream>
#include<unordered_map>
using namespace std;

class Node{
    public:
    int key;
    int value;
    Node* left;
    Node* right;

    Node(int n1,int n2){
        key=n1;
        value=n2;
        left=NULL;
        right=NULL;
    }

};

class LRUCache{
    public:
    int capacity;
    int sizeofDLL;
    unordered_map<int,Node*> piyush;
    Node* start_Node;
    Node* end_Node;

    LRUCache(int n){
        capacity=n;
        sizeofDLL=0;
        start_Node = new Node(0,0);
        end_Node = new Node(0,0);
        start_Node->right=end_Node;
        start_Node->left=NULL;

        end_Node->left=start_Node;
        end_Node->right=NULL;
    }

    LRUCache(){}

    void insert_snippet(Node* insert_Node){
        insert_Node->right=start_Node->right;
        start_Node->right->left=insert_Node;
        start_Node->right=insert_Node;
        insert_Node->left=start_Node;
    }

    void delete_snippet(Node* delete_Node){
        delete_Node->right->left=delete_Node->left;
        delete_Node->left->right=delete_Node->right;
        delete_Node->left=NULL;
        delete_Node->right=NULL;
        delete(delete_Node);
    }

    void printList(){
        //Node* last=Node();
        cout << "\nTraversal in forward direction \n";
        while (start_Node != NULL) {
            cout << " " << start_Node->key << " "<< start_Node->value << " ";
            start_Node = start_Node->right;
        }

    }

    void set(int key1,int value1){
        if(piyush.find(key1)!=piyush.end()){
            //present
            Node* del=piyush[key1];
            delete_snippet(del);


            Node* new_tmp3=new Node(key1,value1);
            insert_snippet(new_tmp3);

            piyush[key1]=new_tmp3;

        }
        else{
            //not present
            if(sizeofDLL < capacity){
                //we have space in cache
                Node* new_tmp=new Node(key1,value1);
                insert_snippet(new_tmp);

                piyush[key1]=new_tmp;
                sizeofDLL++;
            }
            else{
                //need to replace LRU page
                int to_del_key=end_Node->left->key;
                piyush.erase(to_del_key);

                Node* del2=end_Node->left;
                delete_snippet(del2);


                Node* new_tmp3=new Node(key1,value1);
                insert_snippet(new_tmp3);

                piyush[key1]=new_tmp3;   
            }

        }
    }

    int get(int key2){
        if(piyush.find(key2)==piyush.end()){
            //not present
            return -1;
        }
        else{
            //present
            int res=piyush[key2]->value;

            //add Node next to head
            Node* new_tmp2=new Node(key2,res);
            insert_snippet(new_tmp2);

            Node* del=piyush[key2];
            delete_snippet(del);

            piyush[key2]=new_tmp2;
            return res;

        }

    }
};


int main(){
    int size,queries;
    cin>>size>>queries;

    LRUCache lru(size);
    int arr[size]={0};
    int ind=0;
    while(queries--){
        int type,val1,val2;
        cin>>type;
        if(type==1){
            //get
            cin>>val1;
            arr[ind]=lru.get(val1);
            ind++;

        }
        else if(type==2){
            //set
            cin>>val1>>val2;
            lru.set(val1,val2);

        }
    }

    cout<<endl;
    for(int i=0;i<ind;i++){
        cout<<arr[i]<<endl;
    }

}