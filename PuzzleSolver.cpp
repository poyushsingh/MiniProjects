#include<iostream>
using namespace std;

struct Node{
    Node* arr[26];
    bool is_present=false;
    string str;
        
    void put(char ch,Node* new_node){
        arr[ch-'a']=new_node;
    }
        
    Node* get(char ch){
        return arr[ch-'a'];
    }

};

class Trie{
    public:
    Node* root;

    Trie(){
        root=new Node();
    }

    void insert_snippet(Node* node,char ch){
        Node* new_node=new Node();
        node->put(ch,new_node);
    }

    void insert(string word){
        Node* node=root;
        int i=0;
        while(i<word.length()){
            int ind=word[i]-'a';
            if(node->arr[ind]==NULL){
                //not contain key
                insert_snippet(node,word[i]);
            }
            node=node->get(word[i]);
            i++;
        }
        node->is_present=1;
        node->str=word;
    }

    void display(Node* root){
        if((root->is_present) == true){
            cout<<root->str<<endl;
        }
        int i;
        for(i=0;i<26;i++){
            if(root->arr[i]){
                display(root->arr[i]);
            }
        }
    }
        
};

int cnt = -1;
void dfs(char **input,int i,int j,int r,int c,Node* curr,string* ans){
    int ind=input[i][j]-'a';
    if((input[i][j] == '#') or (curr->arr[ind]==NULL)){
        return;
    }

    curr=curr->arr[ind];
    
    if(curr->is_present == 1 ){
        cnt+=1;
        ans[cnt]=curr->str;
        curr->is_present=0;
        
    }

    char ch=input[i][j];
    input[i][j]='#';

    if(i-1>=0){
        //up
        dfs(input,i-1,j,r,c,curr,ans);
    }
    if(j-1>=0){
        //left
        dfs(input,i,j-1,r,c,curr,ans);
    }
    if(i+1<r){
        //down
        dfs(input,i+1,j,r,c,curr,ans);
    }
    if(j+1<c){
        //right
        dfs(input,i,j+1,r,c,curr,ans);
    }

    input[i][j]=ch;
}

void merge(string arr[],string temp[],int l,int mid,int r){
    int i,j,k;
    i=l;
    j=mid;
    k=l;
    
    while((i<=mid-1)&&(j<=r)){
        if(arr[i]<=arr[j]){
            temp[k++]=arr[i++];
        }
        else{
            temp[k++]=arr[j++];
        }
    }
    while(i<=mid-1){
        temp[k++]=arr[i++];
    }
    
    while(j<=r){
        temp[k++]=arr[j++];
    }
    
    for(int i=l;i<=r;i++){
        arr[i]=temp[i];
    }
}


void mergesort(string arr[],string temp[],int l,int r){
    int mid;
    if(l<r){
        mid=(l+r)/2;
        mergesort(arr,temp,l,mid);
        mergesort(arr,temp,mid+1,r);
        merge(arr,temp,l,mid+1,r);
    }
}


int main(){
    Trie as;

    int r,c;
    cin>>r>>c;

    char **input=new char*[r];
    for(int i=0;i<r;i++){
        input[i]=new char[c];
    }


    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            cin>>input[i][j];
        }
    }

    int X;
    cin>>X;

    for(int i=0;i<X;i++){
        string tmp;
        cin>>tmp;
        as.insert(tmp);
    }
    cout<<endl;

    string *ans=new string[30000];

    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            dfs(input,i,j,r,c,as.root,ans);
        }
    }

    string *tmp=new string[cnt+10];
    mergesort(ans,tmp,0,cnt);

    cout<<(cnt+1)<<endl;
    for(int i=0;i<=cnt;i++){
        cout<<ans[i]<<endl;
    }

}


