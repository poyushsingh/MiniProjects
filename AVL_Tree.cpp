#include<iostream>
#include<stdlib.h>
#include<unordered_map>
using namespace std; 

template<typename T> class AVLTree{
    public:
    T typevalue;
    int string_flag=0;

    int modifiedtype123(){
        if(typeid(T).name()==typeid(10).name()){
            typevalue=(int)0;
        }
        else if(typeid(T).name()==typeid((float)3.14).name() || typeid(T).name()==typeid((double)3.14).name()){
            typevalue=(float)(0.0);
        }
        else if(typeid(T).name()==typeid('p').name()){
            typevalue='\0';
        }
        else{
            typevalue={};
            string_flag=1;
        }
        return 0;
    }

    class Node{
        public:
        T val;
        int height;
        int cnt;
        int left_cnt;
        int right_cnt;
        Node* left;
        Node* right;
    };

    Node* main_root=NULL;

    Node* Make_Node(T e){
        Node* new_node=new Node();
        new_node->cnt=1;
        new_node->height=1;
        new_node->left_cnt=0;
        new_node->right_cnt=0;
        new_node->left=NULL;
        new_node->right=NULL;
        new_node->val=e;
        return new_node;
    }

    int find_balance_factor(Node* n){
        if(n==NULL){
            return 0;
        }
        return find_height(n->left)-find_height(n->right);
    }

    int find_height(Node* root){
        if(root==NULL){
            return 0;
        }
        else return root->height;
    }

    Node* right_rotate(Node* root){
        Node* tmp1=root->left;
        Node* tmp3=tmp1->right;

        tmp1->right=root;
        root->left=tmp3;
        root->height=max(find_height(root->right),find_height(root->left))+1;
        tmp1->height=max(find_height(tmp1->right),find_height(tmp1->left))+1;

        if(root!=NULL){
            root->left_cnt=countleft(root);
            root->right_cnt=countright(root);
        }

        if(tmp1!=NULL){
            tmp1->left_cnt=countleft(tmp1);
            tmp1->right_cnt=countright(tmp1);
        }

        return tmp1;
    }

    Node* left_rotate(Node* root){
        Node* tmp1=root->right;
        Node* tmp3=tmp1->left;

        root->right->left=root;
        root->right=tmp3;
        root->height=max(find_height(root->left),find_height(root->right))+1;
        tmp1->height=max(find_height(tmp1->left),find_height(tmp1->right))+1;

         if(root!=NULL){
            root->left_cnt=countleft(root);
            root->right_cnt=countright(root);
        }

        if(tmp3!=NULL){
            tmp3->left_cnt=countleft(tmp3);
            tmp3->right_cnt=countright(tmp3);
        }

        return tmp1;
    }

    void inorder(Node* root){
        if(root!=NULL){
            inorder(root->left);
            for(int i=0;i<root->cnt;i++){
                cout<<root->val<<" ";
            }
            inorder(root->right);
        }
        else{
            return;
        }

    }

    void preorder(Node* root){
        if(root!=NULL){
            for(int i=0;i<root->cnt;i++){
                cout<<root->val<<" ";
            }
            preorder(root->left);
            preorder(root->right);
        }
        else{
            return;
        }
    }

    void postorder(Node* root){
        if(root!=NULL){
            postorder(root->left);
            postorder(root->right);
            for(int i=0;i<root->cnt;i++){
                cout<<root->val<<" ";
            }
        }
        else{
            return;
        }
        
    }

    int countright(Node* root){
        if(root->right == NULL){
            return 0;
        }
        else{
            return root->right->left_cnt+root->right->right_cnt+root->right->cnt;
        }
    }

    int countleft(Node* root){
        if(root->left == NULL){
            return 0;
        }
        else{
            return root->left->left_cnt+root->left->right_cnt+root->left->cnt;
        }
    }

    Node* insert_AVL(Node* root,T e){
        if(root == NULL){
            return Make_Node(e);
        }

        if(e < root->val){
            root->left=insert_AVL(root->left,e);
        }
        else if(e > root->val){
            root->right=insert_AVL(root->right,e);
        }
        else{
            (root->cnt)++;
        }

        root->height=max(find_height(root->left),find_height(root->right))+1;
        root->left_cnt=countleft(root);
        root->right_cnt=countright(root);

        int balance_factor=find_balance_factor(root);

        //if balance_factor is -ve ==> left_height>right_height.
        //if balance_factor is -ve ==> right_height>left_height.
        //L-L problem
        if(balance_factor>1 && e < root->left->val){
            return right_rotate(root);
        }
        //R-R problem
        else if(balance_factor<-1 && e > root->right->val){
            return left_rotate(root);
        }
        //L-R problem
        else if(balance_factor>1 && e > root->left->val){
            root->left= left_rotate(root->left);
            return right_rotate(root);
        }
        //R-L problem
        else if(balance_factor<-1 && e < root->right->val){
            root->right=right_rotate(root->right);
            return left_rotate(root);
        }

        return root;

    }

    void insert(T e){
        Node* ans=insert_AVL(main_root,e);
        main_root=ans;
    }

    
    bool search_AVL(Node* main_root,T e){
        if(main_root==NULL){
            return false;
        }
        else if(main_root->val==e){
            return true;
        }

        else if(e < main_root->val){
            bool l=search_AVL(main_root->left,e);
            return l;
        }
        else{
            bool r=search_AVL(main_root->right,e);
            return r;
        }
    }

    bool search(T e){
        return search_AVL(main_root,e);
    }

    int count_occurence_AVL(Node* main_root,T e){
        if(main_root==NULL){
            return 0;
        }
        else if(main_root->val==e){
            return main_root->cnt;
        }

        else if(e < main_root->val){
            int l=count_occurence_AVL(main_root->left,e);
            return l;
        }
        else{
            int r=count_occurence_AVL(main_root->right,e);
            return r;
        }
    }

    int count_occurence(T e){
        return count_occurence_AVL(main_root,e);
    }


    int v=modifiedtype123();
    T lower_maxi=typevalue;
    T lower_bound_AVL(Node* main_root,T e){
        if(main_root==NULL){
            return lower_maxi;
        }
        else if(main_root->val==e){
            return lower_maxi=e;
        }
        if(e<main_root->val){
            lower_maxi=main_root->val;
            T l=lower_bound_AVL(main_root->left,e);

        }
        else{
            T r=lower_bound_AVL(main_root->right,e);
        }

        return lower_maxi;
    }
 

    int v2=modifiedtype123();
    T upper_maxi=typevalue;
    T upper_bound_AVL(Node* main_root,T e){
        if(main_root==NULL){
            return upper_maxi;
        }
        if(e<main_root->val){
            upper_maxi=main_root->val;
            T l=upper_bound_AVL(main_root->left,e);

        }
        else{
            T r=upper_bound_AVL(main_root->right,e);
        }

        return upper_maxi;
    }


    T upper_bound(T e){
        T ans_upper= upper_bound_AVL(main_root,e);
        modifiedtype123();
        upper_maxi=typevalue;
        return ans_upper;
    }


    T lower_bound(T e){
        T ans_lower= lower_bound_AVL(main_root,e);
        modifiedtype123();
        lower_maxi=typevalue;
        return ans_lower;
    }

    int v1=modifiedtype123();
    T custom_bound_val=typevalue;
    T custom_bound_AVL(Node* main_root,T e){
       if(main_root==NULL){
        return custom_bound_val;
       }
       else if(e>main_root->val){
        custom_bound_val=main_root->val;
        custom_bound_AVL(main_root->right,e);
       }
       else{
        custom_bound_AVL(main_root->left,e);
       }
       return custom_bound_val;

    }

    T custom_bound(T e){
        T ans=custom_bound_AVL(main_root,e);
        modifiedtype123();
        custom_bound_val=typevalue;
        return ans;
    }


    T closest_element(T e){
            if(search(e)){
            return e;
            }
            else{
                T right_bound=upper_bound(e);

                T left_bound=custom_bound(e);

                if(left_bound==typevalue){
                    return right_bound;
                }
                else if(right_bound==typevalue){
                    return left_bound;
                }
                else if(right_bound-e > e-left_bound){
                    return left_bound;
                }
                else{
                    return right_bound;
                }
            }
    }

    int count_range_AVL(Node* main_root,T eLeft,T eRight){
        if(main_root==NULL){
            return 0;
        }
        else if(main_root->val == eLeft && main_root->val == eRight){
            return 1;
        }
        else if(main_root->val >= eLeft && main_root->val <= eRight){

            int val9=count_range_AVL(main_root->left,eLeft,eRight);
            int val0=count_range_AVL(main_root->right,eLeft,eRight);
            return main_root->cnt+val9+val0;
        }
        else if(main_root->val < eLeft){
            return count_range_AVL(main_root->right,eLeft,eRight);
        }
        else if(main_root->val > eRight){
            return count_range_AVL(main_root->left,eLeft,eRight);
        }
        else{
            return 0;
        }    
    }

    int count_range(T eLeft,T eRight){
        if(eLeft>eRight){
            return 0;
        }
        else{
        int ans=count_range_AVL(main_root,eLeft,eRight);
        return ans;
        }
    }

    Node* find_inorder_sucessor(Node *deep){
        deep=deep->right;
        while(deep->left!=NULL){
            deep=deep->left;
        }
        return deep;
    }

    Node* delete_AVL(Node* root,T e){
        if(root==NULL){
            return root;
        }
        else if(e<root->val){
            root->left=delete_AVL(root->left,e);
        }
        else if(e>root->val){
            root->right=delete_AVL(root->right,e);
        }
        else{
            if(root->left==NULL && root->right==NULL){   //leaf
                Node* tmp123=root;
                delete(tmp123);
                root=NULL;
                
                
            }
            else if(root->left!=NULL && root->right==NULL){   //left child
                Node* tmp2=root->left;
                *root=*tmp2;
                delete(tmp2);
                
            }
            else if(root->left==NULL && root->right!=NULL){   //right child
                Node* tmp3=root->right;
                *root=*tmp3;
                delete(tmp3);
              
            }

            else{
                Node* to_be_deleted=find_inorder_sucessor(root);   //both child
                root->val=to_be_deleted->val;
                root->cnt=to_be_deleted->cnt;
                root->left_cnt=to_be_deleted->left_cnt;
                root->right_cnt=to_be_deleted->right_cnt;
                root->right=delete_AVL(root->right,to_be_deleted->val);
            }
        }

        if(root==NULL){
            return root;
        }

        root->height=max(find_height(root->left),find_height(root->right))+1;
        root->left_cnt=countleft(root);
        root->right_cnt=countright(root);

        int balance_factor=find_balance_factor(root);

        //if balance_factor is -ve ==> left_height>right_height.
        //if balance_factor is -ve ==> right_height>left_height.
        //L-L problem
        if(balance_factor>1 && find_balance_factor(root->left) >=0 ){
            return right_rotate(root);
        }
        //R-R problem
        else if(balance_factor<-1 && find_balance_factor(root->right) <=0){
            return left_rotate(root);
        }
        //L-R problem
        else if(balance_factor>1 && find_balance_factor(root->left) < 0){
            root->left= left_rotate(root->left);
            return right_rotate(root);
        }
        //R-L problem
        else if(balance_factor<-1 && find_balance_factor(root->right) >0){
            root->right=right_rotate(root->right);
            return left_rotate(root);
        }

        return root;

    }

    void Delete(T e){
        Node* ans=delete_AVL(main_root,e);
        main_root=ans;
    }


    T Kth_largest_AVL(Node* main_root,int k){
        if(main_root->left==NULL && main_root->right==NULL){
            return main_root->val;
        }
        if(k > main_root->right_cnt && k <= main_root->right_cnt+main_root->cnt){
            return main_root->val;
        }
        if(main_root->right_cnt>=k){
            return Kth_largest_AVL(main_root->right,k);
        }
        else{
            k=k-main_root->right_cnt-1;
            return Kth_largest_AVL(main_root->left,k);
        }
    }

    T Kth_largest(int k){
        if(k>main_root->left_cnt+main_root->right_cnt+main_root->cnt){
            modifiedtype123();
            return typevalue;
        } 
        else{
            return Kth_largest_AVL(main_root, k);
        }
    }

};


int main(){

    int flag=1;
    AVLTree<int> avl;
    int response;
    typedef int T;
    avl.modifiedtype123();

     while(flag){
        printf("\n");
        printf("1.Insertion\n");
        printf("2.Deletion\n");
        printf("3.Search\n");
        printf("4.Count occuences of element\n");
        printf("5.Lower_bound\n");
        printf("6.Upper_bound\n");
        if(avl.string_flag!=1){
            printf("7.Closest element\n");
        }
        printf("8.K-th largest element\n");
        printf("9.Count number of values in a given range\n");
        printf("10.Print Preorder\n");
        printf("11.Print Inorder\n");
        printf("12.Print Postorder\n");
        printf("13.Exit\n");

        cin>>response;

        if(response==1){
            T val;
            cin>>val;
            avl.insert(val);
        }
        else if(response==2){
            T val2;
            cin>>val2;
            avl.Delete(val2);
        }
        else if(response==3){
            T val3;
            cin>>val3;
            cout<<avl.search(val3)<<endl;
        }
        else if(response==4){
            T val4;
            cin>>val4;
            cout<<avl.count_occurence(val4)<<endl;
        }
        else if(response==5){
            T val5;
            cin>>val5;
            cout<<avl.lower_bound(val5)<<endl;
        }
        
        else if(response==6){
            T val6;
            cin>>val6;
            cout<<avl.upper_bound(val6)<<endl;
        }
        else if(response==7){
            avl.modifiedtype123();
            if(avl.string_flag!=1){
                T val7;
                cin>>val7;
                cout<<avl.closest_element(val7)<<endl;
            }
            else{
                cout<<" "<<endl;
            }
        }
        else if(response==8){
            int val8;
            cin>>val8;
            cout<<avl.Kth_largest(val8)<<endl;
        }
        else if(response==9){
            T left;
            T right;
            cin>>left>>right;
            cout<<avl.count_range(left,right)<<endl;
        }
        else if(response==10){
            cout<<endl;
            avl.preorder(avl.main_root);
        }
        else if(response==11){
            cout<<endl;
            avl.inorder(avl.main_root);
        }
        else if(response==12){
            cout<<endl;
            avl.postorder(avl.main_root);
        }
        else if(response==13){
            flag=0;
            cout<<"Bye !!"<<endl;
        }
        else{
            cout<<"ENTER CORRECT CHOICE!!"<<"\n";
        }
        

    } 

}