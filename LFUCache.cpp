#include<stdio.h>
#include<iostream>
#include<unordered_map>
using namespace std;

class Node{
    public:
    int key;
    int value;
    int freq;
    Node* left;
    Node* right;

    Node(int n1,int n2){
        key=n1;
        value=n2;
        left=NULL;
        right=NULL;
        freq=1;
    }

    Node(){}

};

class Vector{
    public:
    int sizeofVec;
    Node* start_Node;
    Node* end_Node;

    Vector(){
        sizeofVec=0;
        start_Node = new Node(0,0);
        end_Node = new Node(0,0);
        
        start_Node->right=end_Node;
        start_Node->left=NULL;

        end_Node->left=start_Node;
        end_Node->right=NULL;
    }

    void insert_snippet(Node* insert_node,Node* start_Node,Node* end_Node){
        insert_node->right=start_Node->right;
        start_Node->right->left=insert_node;
        start_Node->right=insert_node;
        insert_node->left=start_Node;
    }

    void delete_snippet(Node* delete_node,Node* start_Node,Node* end_Node){
        delete_node->right->left=delete_node->left;
        delete_node->left->right=delete_node->right;
        delete_node->left=NULL;
        delete_node->right=NULL;
    }

    void insertfront(Node* node){
        insert_snippet(node,start_Node,end_Node);
        sizeofVec++;
    }

    void deleteback(Node* node){
        delete_snippet(node,start_Node,end_Node);
        sizeofVec--;
    }

};

class LFUCache {
     public:
    int capacity;
    int sizeofDLL;
    int min_freq;
    unordered_map<int,Vector*> vector_for_frequency_list;
    unordered_map<int,Node*> key_node_pair;

    LFUCache(int capacity1) {
        capacity=capacity1;
        sizeofDLL=0;
        min_freq=0;
    }

    LFUCache(){}
    
    void update_vector_for_frequency_list(Node* node){
        Node* store_address=node;
        vector_for_frequency_list[node->freq]->deleteback(node);
        
        int tmp_freq=store_address->freq;
        int tmp_value=vector_for_frequency_list[tmp_freq]->sizeofVec;
        if(tmp_freq==min_freq && tmp_value==0){
            min_freq=min_freq+1;
        }

        int req_freq=store_address->freq+1;
        Vector* new_vec;
        if(vector_for_frequency_list.find(req_freq) == vector_for_frequency_list.end()){
            new_vec=new Vector();
        }
        else{
            new_vec=vector_for_frequency_list[req_freq];
        }
        
        store_address->freq+=1;
        new_vec->insertfront(store_address);
        vector_for_frequency_list[store_address->freq]=new_vec;

        int k=store_address->key;
        key_node_pair[k]=store_address;
    }
    
    
    
    int get(int key2) {
        if(key_node_pair.find(key2) == key_node_pair.end()){
            //not present
            return -1;
        }
        else{
            //present
            int res=key_node_pair[key2]->value;
            update_vector_for_frequency_list(key_node_pair[key2]);
            return res;
        }
        
    }

    void put_present(int key1, int value1){
        Node* del=key_node_pair[key1];
        del->value=value1;
        update_vector_for_frequency_list(del);
    }
    
    void put_Not_present(int key1, int value1){
        min_freq=1;
        sizeofDLL++;
        Node* new_node2=new Node(key1,value1);
        Vector* new_vec2;

        if(vector_for_frequency_list.find(min_freq) == vector_for_frequency_list.end()){
            new_vec2=new Vector();
        }
        else{
            new_vec2=vector_for_frequency_list[min_freq];
        }

        new_vec2->insertfront(new_node2);

        key_node_pair[key1]=new_node2;
                
        vector_for_frequency_list[min_freq]=new_vec2;
    }
    
    void set(int key1, int value1) {
        if(key_node_pair.find(key1)!=key_node_pair.end()){
            //present

            put_present(key1,value1);

        }
        else{
            if(sizeofDLL < capacity){
                //we have space in cache
                
                put_Not_present(key1,value1);
                
            }
            else{
                //need to replace LFU Cache
                
                Vector* vec=vector_for_frequency_list[min_freq];
                
                int to_del=vec->end_Node->left->key;
                key_node_pair.erase(to_del);
                
                Node* to_del_vec=vec->end_Node->left;
                vector_for_frequency_list[min_freq]->deleteback(to_del_vec);
                
                put_Not_present(key1,value1);
                

            }
            

        }
        
    }
};



int main(){
    int size,queries;
    cin>>size>>queries;

    LFUCache lfu(size);
    int arr[size]={0};
    int ind=0;
    while(queries--){
        int type,val1,val2;
        cin>>type;
        if(type==1){
            //get
            cin>>val1;
            arr[ind]=lfu.get(val1);
            ind++;

        }
        else if(type==2){
            //set
            cin>>val1>>val2;
            lfu.set(val1,val2);

        }
    }

    cout<<endl;
    for(int i=0;i<ind;i++){
        cout<<arr[i]<<endl;
    }

}