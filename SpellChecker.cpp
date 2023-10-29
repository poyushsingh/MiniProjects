#include<iostream>
#include<vector>
using namespace std;

struct Node{
    Node* arr[26];
    bool is_present=0;
    string str=" ";

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
            if(node->arr[word[i]-'a']==NULL){
                //not contain key
                insert_snippet(node,word[i]);
            }
            node=node->get(word[i]);
            i++;
        }
        node->is_present=1;
        node->str=word;
    }

    void find_ans(Node* root, int level,int &cnt,vector<string> &ans){
        if (root->is_present==true){
            cnt=cnt+1;
            ans.push_back(root->str);
        }
    
        int i;
        for (i=0;i<26;i++){
            if (root->arr[i]){
                find_ans(root->arr[i], level + 1,cnt,ans);
            }
        }
    }

    int levi_dist(string s1,string s2){
        int n=s1.size();
        int m=s2.size();
        vector<vector<int>> dp(n+1,vector<int> (m+1)); 

        for(int j=0;j<=m;j++){
            dp[0][j]=j;
        }
        for(int i=0;i<=n;i++){
            dp[i][0]=i;
        }

        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(s1[i-1]==s2[j-1]){
                    dp[i][j]=dp[i-1][j-1];
                }
                else{
                    dp[i][j]=1+min(dp[i][j-1],min(dp[i-1][j-1],dp[i-1][j]));
                }

            }
        }

        return dp[n][m];
    }

    bool spellcheck(string word){
        Node* node=root;
        int i=0;

        while(i<word.length()){
            if(node->arr[word[i]-'a']!=NULL){
                node=node->get(word[i]);
            }
            i++;
        }
        if(node->is_present==true){
            return 1;
        }
        else{
            return 0;
        }

    }

    void autocomplete(string word){
        Node* node=root;
        int i=0,flag=0,cnt=0;

        vector<string> ans;
        
        while(i<word.length()){
            if(node->arr[word[i]-'a']!=NULL){
                node=node->get(word[i]);
                i++;
            }
            else{
                flag=1;
                cout<<"-1"<<endl;
                break;
            }
            
        }
        if(flag==0){
            find_ans(node,0,cnt,ans);
        }

        cout<<(cnt)<<endl;
        for(auto it:ans){
            cout<<it<<endl;
        }
        
    }

    void autocorrect(string word){
        int cnt=0;
        int local=0;
        int n1=word.size();
        vector<string> ans;
        vector<string> final_ans;
        find_ans(root,0,cnt,ans);

        for(auto it:ans){
            int n2=it.size();
            if(abs(n1-n2)<=3 && levi_dist(word,it)<=3){
                local++;
                final_ans.push_back(it);
            }
        }

        cout<<local<<endl;
        for(auto it:final_ans){
            cout<<it<<endl;
        }

    }   
};

int main(){
    Trie as;

    int n,q;
    cin>>n>>q;

    for(int i=0;i<n;i++){
        string tmp="";
        cin>>tmp;
        as.insert(tmp);
    }

    for(int i=0;i<q;i++){
        int first;
        string second;

        cin>>first;
        cin>>second;

        if(first==1){
            cout<<as.spellcheck(second)<<endl;
        }
        else if(first==2){
            as.autocomplete(second);
        }
        else if(first==3){
            as.autocorrect(second);
        }

    }

}