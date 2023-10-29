#include<iostream>
#include<stdlib.h>
#include<unordered_map>
using namespace std;

template<typename T> class Sparse_Matrix{
    public: 

    //cnt1 will count number of non-zero in matrix_1
    //cnt2 will count number of non-zero in matrix_2
    //cnt3 will count number of non-zero in arr_ans
    void add_sparse_mat_array(){
        int n1,m1,cnt1=0;
        cin>>n1>>m1;

        T** arr1;               //dynamic allocation of 2D array so that we can free it before function call ends.
        arr1 = new T*[3];
        for(int i=0;i<3;i++){       
            arr1[i]=new T[n1*m1];
        }
        for(int i=0;i<n1;i++){
            for(int j=0;j<m1;j++){
                T val;
                cin>>val;
                if(val!=0){
                    arr1[0][cnt1]=i;
                    arr1[1][cnt1]=j;
                    arr1[2][cnt1]=val;
                    cnt1++;
                }
            }
        }

        int n2,m2,cnt2=0;
        cin>>n2>>m2;

        T** arr2;            //dynamic allocation of 2D array so that we can free it before function call ends.
        arr2 = new T*[3];
        for(int i=0;i<3;i++){
            arr2[i]=new T[n2*m2];
        }
        for(int i=0;i<n2;i++){
            for(int j=0;j<m2;j++){
                T val;
                cin>>val;
                if(val!=0){
                    arr2[0][cnt2]=i;
                    arr2[1][cnt2]=j;
                    arr2[2][cnt2]=val;
                    cnt2++;
                }
            }
        }

        int ptr1=0,ptr2=0,ptr3=0,cnt3=0;
        int tmp=cnt1+cnt2+5;

        T** arr_ans;            //dynamic allocation of 2D array so that we can free it before function call ends.
        arr_ans=new T*[3];
        for(int i=0;i<3;i++){
            arr_ans[i]=new T[tmp];
        }          

        while(ptr1<=cnt1 && ptr2<=cnt2){
            if(arr1[0][ptr1]<arr2[0][ptr2]){
                //arr1 row is smaller
                arr_ans[0][ptr3]=arr1[0][ptr1];
                arr_ans[1][ptr3]=arr1[1][ptr1];
                arr_ans[2][ptr3]=arr1[2][ptr1];
                ptr1++;
                ptr3++;
                cnt3++;
            }
            else if(arr1[0][ptr1]>arr2[0][ptr2]){
                //arr2 row is smaller
                arr_ans[0][ptr3]=arr2[0][ptr2];
                arr_ans[1][ptr3]=arr2[1][ptr2];
                arr_ans[2][ptr3]=arr2[2][ptr2];
                ptr2++;
                ptr3++;
                cnt3++;
            }
            else{
                //row are same
                if(arr1[1][ptr1]==arr2[1][ptr2]){
                    //column are same
                    T tmp_ans=arr1[2][ptr1]+arr2[2][ptr2];
                    arr_ans[0][ptr3]=arr1[0][ptr1];
                    arr_ans[1][ptr3]=arr1[1][ptr1];
                    arr_ans[2][ptr3]=tmp_ans;
                    ptr1++;
                    ptr2++;
                    ptr3++;
                    cnt3++;
                }
                else{
                    if(arr1[1][ptr1]<arr2[1][ptr2]){
                        //arr1 column is smaller
                        arr_ans[0][ptr3]=arr1[0][ptr1];
                        arr_ans[1][ptr3]=arr1[1][ptr1];
                        arr_ans[2][ptr3]=arr1[2][ptr1];
                        ptr1++;
                        ptr3++;
                        cnt3++;

                    }
                    else{
                        //arr2 column is smaller
                        arr_ans[0][ptr3]=arr2[0][ptr2];
                        arr_ans[1][ptr3]=arr2[1][ptr2];
                        arr_ans[2][ptr3]=arr2[2][ptr2];
                        ptr2++;
                        ptr3++;
                        cnt3++;
                    }
                }
            }
        }

        // cout<<"Addition:\n";
        printf("\n");
        int local_ptr=0;
        for(int i=0;i<n1;i++){
            for(int j=0;j<m1;j++){
                if(arr_ans[0][local_ptr] == i && arr_ans[1][local_ptr] == j){
                    cout<<arr_ans[2][local_ptr]<<" ";
                    local_ptr++;
                }
                else{
                    cout<<"0"<<" ";
                }
            }
            cout<<endl;
        }
        delete[] arr1;
        delete[] arr2;
        delete[] arr_ans;

    }

    void transpose_sparse_mat_array(){
        int n1,m1,cnt1=0;
        cin>>n1>>m1;

        T** arr1;
        arr1 = new T*[3];
        for(int i=0;i<3;i++){
            arr1[i]=new T[n1*m1];
        }

        for(int i=0;i<n1;i++){
            for(int j=0;j<m1;j++){
                T val;
                cin>>val;
                if(val!=0){
                    arr1[0][cnt1]=i;
                    arr1[1][cnt1]=j;
                    arr1[2][cnt1]=val;
                    cnt1++;
                }
            }
        }

        int local_ptr_transpose=0;
        for(int i=0;i<cnt1;i++){
            swap(arr1[0][local_ptr_transpose],arr1[1][local_ptr_transpose]);
            local_ptr_transpose++;
        }

        //sort
        for(int i=0;i<cnt1;i++){
            for(int j=i+1;j<cnt1;j++){
                if(arr1[0][i]>arr1[0][j]){
                    T tmp1=arr1[0][i];
                    T tmp2=arr1[1][i];
                    T tmp3=arr1[2][i];
                    
                    arr1[0][i]=arr1[0][j];
                    arr1[1][i]=arr1[1][j];
                    arr1[2][i]=arr1[2][j];

                    arr1[0][j]=tmp1;
                    arr1[1][j]=tmp2;
                    arr1[2][j]=tmp3;
                    
                }
                else if(arr1[0][i]==arr1[0][j]){
                    if(arr1[1][i]>arr1[1][j]){
                        T tmp1=arr1[0][i];
                        T tmp2=arr1[1][i];
                        T tmp3=arr1[2][i];
                        
                        arr1[0][i]=arr1[0][j];
                        arr1[1][i]=arr1[1][j];
                        arr1[2][i]=arr1[2][j];

                        arr1[0][j]=tmp1;
                        arr1[1][j]=tmp2;
                        arr1[2][j]=tmp3;

                    }
                }
            }
        }

        // cout<<"Transpose:\n";
        printf("\n");
        int local_ptr=0;
        for(int i=0;i<m1;i++){
            for(int j=0;j<n1;j++){
                if(arr1[0][local_ptr] == i && arr1[1][local_ptr] == j){
                    cout<<arr1[2][local_ptr]<<" ";
                    local_ptr++;
                }
                else{
                    cout<<"0"<<" ";
                }
            }
            cout<<endl;
        }
        delete[] arr1;

    }

    void mul_sparse_mat_array(){
        int n1,m1,cnt1=0;
        cin>>n1>>m1;

        T** arr1;
        arr1 = new T*[3];
        for(int i=0;i<3;i++){
            arr1[i]=new T[n1*m1];
        }
        for(int i=0;i<n1;i++){
            for(int j=0;j<m1;j++){
                T val;
                cin>>val;
                if(val!=0){
                    arr1[0][cnt1]=i;
                    arr1[1][cnt1]=j;
                    arr1[2][cnt1]=val;
                    cnt1++;
                }
            }
        }

        int n2,m2,cnt2=0;
        cin>>n2>>m2;

        T** arr2;
        arr2 = new T*[3];
        for(int i=0;i<3;i++){
            arr2[i]=new T[n2*m2];
        }

        for(int i=0;i<n2;i++){
            for(int j=0;j<m2;j++){
                T val;
                cin>>val;
                if(val!=0){
                    arr2[0][cnt2]=i;
                    arr2[1][cnt2]=j;
                    arr2[2][cnt2]=val;
                    cnt2++;
                }
            }
        }

        //transpose 2nd array.
        int local_ptr_transpose=0;
        for(int i=0;i<cnt1;i++){
            swap(arr2[0][local_ptr_transpose],arr2[1][local_ptr_transpose]);
            local_ptr_transpose++;
        }

        int tmp=cnt1*cnt2+5;

        T** arr_ans_mul;
        arr_ans_mul = new T*[3];
        for(int i=0;i<3;i++){
            arr_ans_mul[i]=new T[100005];
        }
        int ptr_mul=0;

        for(int i=0;i<cnt1;i++){
            for(int j=0;j<cnt2;j++){
                if(arr1[1][i]==arr2[1][j]){
                    arr_ans_mul[0][ptr_mul]=arr1[0][i];
                    arr_ans_mul[1][ptr_mul]=arr2[0][j];
                    arr_ans_mul[2][ptr_mul]=arr1[2][i]*arr2[2][j];

                    ptr_mul++;
                }
            }
        }

        for(int i=0;i<ptr_mul;i++){
            for(int j=i+1;j<ptr_mul;j++){
                if(arr_ans_mul[0][i]==arr_ans_mul[0][j]){
                    if(arr_ans_mul[1][i]==arr_ans_mul[1][j]){
                        arr_ans_mul[2][i]+=arr_ans_mul[2][j];
                        arr_ans_mul[0][j]=1e9;
                        arr_ans_mul[1][j]=1e9;
                        arr_ans_mul[2][j]=1e9;

                    }
                }
            }
        }

        //sort
        for(int i=0;i<ptr_mul;i++){
            for(int j=i+1;j<ptr_mul;j++){
                if(arr_ans_mul[0][i]>=0 && arr_ans_mul[0][j]>=0){
                    if(arr_ans_mul[0][i]>arr_ans_mul[0][j]){
                        int tmp1=arr_ans_mul[0][i];
                        int tmp2=arr_ans_mul[1][i];
                        int tmp3=arr_ans_mul[2][i];
                        
                        arr_ans_mul[0][i]=arr_ans_mul[0][j];
                        arr_ans_mul[1][i]=arr_ans_mul[1][j];
                        arr_ans_mul[2][i]=arr_ans_mul[2][j];

                        arr_ans_mul[0][j]=tmp1;
                        arr_ans_mul[1][j]=tmp2;
                        arr_ans_mul[2][j]=tmp3;
                        
                    }
                    else if(arr_ans_mul[0][i]==arr_ans_mul[0][j]){
                        if(arr_ans_mul[1][i]>arr_ans_mul[1][j]){
                            int tmp1=arr_ans_mul[0][i];
                            int tmp2=arr_ans_mul[1][i];
                            int tmp3=arr_ans_mul[2][i];
                            
                            arr_ans_mul[0][i]=arr_ans_mul[0][j];
                            arr_ans_mul[1][i]=arr_ans_mul[1][j];
                            arr_ans_mul[2][i]=arr_ans_mul[2][j];

                            arr_ans_mul[0][j]=tmp1;
                            arr_ans_mul[1][j]=tmp2;
                            arr_ans_mul[2][j]=tmp3;

                        }
                    }
                }
            }
        }

        // cout<<"Multiplication : "<<endl;
        printf("\n");
        int local_ptr_mul=0;
        for(int i=0;i<n1;i++){
            for(int j=0;j<m2;j++){
                if(arr_ans_mul[0][local_ptr_mul] == i && arr_ans_mul[1][local_ptr_mul] == j){    
                    cout<<arr_ans_mul[2][local_ptr_mul]<<" ";
                    local_ptr_mul++;
                }
                else if(arr_ans_mul[0][local_ptr_mul]==-10 && arr_ans_mul[1][local_ptr_mul]==-10){
                    cout<<"0"<<" ";
                    local_ptr_mul++;
                }
                else{
                    cout<<"0"<<" ";
                }
            }
            printf("\n");
        }
        delete[] arr1;
        delete[] arr2;
        delete[] arr_ans_mul;
    }

    class Node{
        public:
        int row;
        int col;
        T val;
        Node* next;

        Node(){
            row=0;
            col=0;
            val=0;
            next=NULL;
        }

    };

    void display(Node* root,int n,int m)
    {
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(root==NULL){
                    cout<<"0"<<" ";
                    continue;
                }
                else if(root->row == i && root->col == j){    
                    cout<<root->val<<" ";
                    root=root->next;
                }
                else{
                    cout<<"0"<<" ";
                }
            }
            printf("\n");
        }
    }

    void add_sparse_mat_LL(){
        int n1,m1,cnt1=0;
        cin>>n1>>m1;
        Node* head1=NULL;

        for(int i=0;i<n1;i++){
            for(int j=0;j<m1;j++){
                T tmpval;
                cin>>tmpval;
                if(tmpval!=0){
                    Node* new_node1=new Node();
                    Node* ptr;
                    new_node1->row=i;
                    new_node1->col=j;
                    new_node1->val=tmpval;
                    new_node1->next=NULL;
                    if(head1==NULL){
                        head1=new_node1;
                    }
                    else{
                        ptr=head1;
                        while(ptr->next!=NULL){
                            ptr=ptr->next;
                        }
                        ptr->next=new_node1;

                    }

                }
            }
        }

        int n2,m2,cnt2=0;
        cin>>n2>>m2;
        Node* head2=NULL;

        for(int i=0;i<n1;i++){
            for(int j=0;j<m1;j++){
                T tmpval2;
                cin>>tmpval2;
                if(tmpval2!=0){
                    Node* new_node2=new Node();
                    Node* ptr;
                    new_node2->row=i;
                    new_node2->col=j;
                    new_node2->val=tmpval2;
                    new_node2->next=NULL;
                    if(head2==NULL){
                        head2=new_node2;
                    }
                    else{
                        ptr=head2;
                        while(ptr->next!=NULL){
                            ptr=ptr->next;
                        }
                        ptr->next=new_node2;

                    }

                }
            }
        }

        Node* p=head1;
        Node* q=head2;
        Node* ans_LL_head=NULL;
        Node* ans_ptr=NULL;

        while(p!=NULL && q!=NULL){
            if(p->row==q->row){
                if(p->col==q->col){
                    Node* ans_LL=new Node();
                    ans_LL->row=p->row;
                    ans_LL->col=p->col;
                    ans_LL->val=(p->val+q->val);
                    ans_LL->next=NULL;
                    if(ans_LL_head==NULL){
                        ans_LL_head=ans_LL;
                    }
                    else{
                        ans_ptr=ans_LL_head;
                        while(ans_ptr->next!=NULL){
                            ans_ptr=ans_ptr->next;
                        }
                        ans_ptr->next=ans_LL;

                    }
                    p=p->next;
                    q=q->next;
                }
                else if(p->col < q->col){
                    Node* ans_LL=new Node();
                    ans_LL->row=p->row;
                    ans_LL->col=p->col;
                    ans_LL->val=(p->val);
                    ans_LL->next=NULL;
                    if(ans_LL_head==NULL){
                        ans_LL_head=ans_LL;
                    }
                    else{
                        ans_ptr=ans_LL_head;
                        while(ans_ptr->next!=NULL){
                            ans_ptr=ans_ptr->next;
                        }
                        ans_ptr->next=ans_LL;

                    }
                    p=p->next;
                }
                else{
                    Node* ans_LL=new Node();
                    ans_LL->row=q->row;
                    ans_LL->col=q->col;
                    ans_LL->val=(q->val);
                    ans_LL->next=NULL;
                    if(ans_LL_head==NULL){
                        ans_LL_head=ans_LL;
                    }
                    else{
                        ans_ptr=ans_LL_head;
                        while(ans_ptr->next!=NULL){
                            ans_ptr=ans_ptr->next;
                        }
                        ans_ptr->next=ans_LL;

                    }
                    q=q->next;

                }
            }
            else{
                if(p->row < q->row){
                    Node* ans_LL=new Node();
                    ans_LL->row=p->row;
                    ans_LL->col=p->col;
                    ans_LL->val=(p->val);
                    ans_LL->next=NULL;
                    if(ans_LL_head==NULL){
                        ans_LL_head=ans_LL;
                    }
                    else{
                        ans_ptr=ans_LL_head;
                        while(ans_ptr->next!=NULL){
                            ans_ptr=ans_ptr->next;
                        }
                        ans_ptr->next=ans_LL;

                    }
                    p=p->next;

                }
                else{
                    Node* ans_LL=new Node();
                    ans_LL->row=q->row;
                    ans_LL->col=q->col;
                    ans_LL->val=(q->val);
                    ans_LL->next=NULL;
                    if(ans_LL_head==NULL){
                        ans_LL_head=ans_LL;
                    }
                    else{
                        ans_ptr=ans_LL_head;
                        while(ans_ptr->next!=NULL){
                            ans_ptr=ans_ptr->next;
                        }
                        ans_ptr->next=ans_LL;

                    }
                    q=q->next;
                }
            }
        }

        while(p!=NULL){
            Node* ans_LL=new Node();
            ans_LL->row=p->row;
            ans_LL->col=p->col;
            ans_LL->val=(p->val);
            ans_LL->next=NULL;
            if(ans_LL_head==NULL){
                ans_LL_head=ans_LL;
            }
            else{
                ans_ptr=ans_LL_head;
                while(ans_ptr->next!=NULL){
                    ans_ptr=ans_ptr->next;
                }
                ans_ptr->next=ans_LL;

            }
            p=p->next;

        }

        while(q!=NULL){
            Node* ans_LL=new Node();
            ans_LL->row=p->row;
            ans_LL->col=q->col;
            ans_LL->val=(q->val);
            ans_LL->next=NULL;
            if(ans_LL_head==NULL){
                ans_LL_head=ans_LL;
            }
            else{
                ans_ptr=ans_LL_head;
                while(ans_ptr->next!=NULL){
                    ans_ptr=ans_ptr->next;
                }
                ans_ptr->next=ans_LL;

            }
            q=q->next;

        }
        
        printf("\n");
        display(ans_LL_head,n1,m1);

    }

    Node* merge(Node* left,Node* right){
        if(left==NULL){
            return right;
        }

        if(right==NULL){
            return left;
        }

        Node* res=new Node();
        Node* tmp=res;
        while(left!=NULL && right!=NULL){
            if(left->row == right->row){
                if(left->col < right->col){
                    tmp->next=left;
                    tmp=left;
                    left=left->next;
                }
                else{
                    tmp->next=right;
                    tmp=right;
                    right=right->next;
                }
            }
            else if(left->row < right->row){
                tmp->next=left;
                tmp=left;
                left=left->next;
            }
            else{
                tmp->next=right;
                tmp=right;
                right=right->next;
            }
        }
        
        while(left!=NULL){
            tmp->next=left;
            tmp=left;
            left=left->next;
            
        }
        
        while(right!=NULL){
            tmp->next=right;
            tmp=right;
            right=right->next;
        }
        res=res->next;
        return res;

    }

    Node* findmid(Node* head){
        Node* first=head->next;
        Node* second=head;
        while(first!=NULL && first->next!=NULL){
            first=first->next->next;
            second=second->next;
        }
        return second;
    }

    Node* mergeSort(Node* head){
        if(head==NULL || head->next==NULL){
            return head;
        }

        Node* mid=findmid(head);
        Node* left=head;
        Node* right=mid->next;
        mid->next=NULL;

        left=mergeSort(left);
        right=mergeSort(right);
        
        Node* ans=merge(left,right);
        
        return ans;
    }

    void linked_list_print(Node* n){
        while (n != NULL) {
            cout<<n->row<<endl;
            cout<<n->col<<endl;
            cout<<n->val<<endl;
            cout<<endl;
            n = n->next;
        }
    }


    void transpose_sparse_mat_LL(){
        int n1,m1,cnt1=0;
        cin>>n1>>m1;
        Node* head1=NULL;

        for(int i=0;i<n1;i++){
            for(int j=0;j<m1;j++){
                T tmpval;
                cin>>tmpval;
                if(tmpval!=0){
                    Node* new_node1=new Node();
                    Node* ptr;
                    new_node1->row=i;
                    new_node1->col=j;
                    new_node1->val=tmpval;
                    new_node1->next=NULL;
                    if(head1==NULL){
                        head1=new_node1;
                    }
                    else{
                        ptr=head1;
                        while(ptr->next!=NULL){
                            ptr=ptr->next;
                        }
                        ptr->next=new_node1;

                    }

                }
            }
        }

        Node* tmp_ptr=head1;
        while(tmp_ptr != NULL){
            int tmp=tmp_ptr->col;
            tmp_ptr->col=tmp_ptr->row;
            tmp_ptr->row=tmp;
            tmp_ptr=tmp_ptr->next;
        }

        Node* ans_final=mergeSort(head1);

        printf("\n");
        // cout<<"Transpose:"<<endl;
        display(ans_final,m1,n1);

    }

    void mul_sparse_mat_LL(){
        int n1,m1,cnt1=0;
        cin>>n1>>m1;
        Node* head1=NULL;

        for(int i=0;i<n1;i++){
            for(int j=0;j<m1;j++){
                T tmpval;
                cin>>tmpval;
                if(tmpval!=0){
                    Node* new_node1=new Node();
                    Node* ptr;
                    new_node1->row=i;
                    new_node1->col=j;
                    new_node1->val=tmpval;
                    new_node1->next=NULL;
                    if(head1==NULL){
                        head1=new_node1;
                    }
                    else{
                        ptr=head1;
                        while(ptr->next!=NULL){
                            ptr=ptr->next;
                        }
                        ptr->next=new_node1;

                    }

                }
            }
        }

        int n2,m2,cnt2=0;
        cin>>n2>>m2;
        Node* head2=NULL;

        for(int i=0;i<n2;i++){
            for(int j=0;j<m2;j++){
                T tmpval2;
                cin>>tmpval2;
                if(tmpval2!=0){
                    Node* new_node2=new Node();
                    Node* ptr;
                    new_node2->row=i;
                    new_node2->col=j;
                    new_node2->val=tmpval2;
                    new_node2->next=NULL;
                    if(head2==NULL){
                        head2=new_node2;
                    }
                    else{
                        ptr=head2;
                        while(ptr->next!=NULL){
                            ptr=ptr->next;
                        }
                        ptr->next=new_node2;

                    }

                }
            }
        }

        //swapped row and column of 2nd list
        Node* tmp_ptr=head2;
        while(tmp_ptr != NULL){
            int tmp=tmp_ptr->col;
            tmp_ptr->col=tmp_ptr->row;
            tmp_ptr->row=tmp;
            tmp_ptr=tmp_ptr->next;
        }

        Node* ptr_head1=NULL;
        Node* ptr_head2=NULL;
        Node* final_ans_head=NULL;
        Node* tmp_ans_ptr=NULL;

        for(ptr_head1=head1;ptr_head1!=NULL;ptr_head1=ptr_head1->next){
            for(ptr_head2=head2;ptr_head2!=NULL;ptr_head2=ptr_head2->next){
                if(ptr_head1->col==ptr_head2->col){
                    Node* ans_tmp=new Node();
                    ans_tmp->row=ptr_head1->row;
                    ans_tmp->col=ptr_head2->row;
                    ans_tmp->val=(ptr_head1->val*ptr_head2->val);
                    ans_tmp->next=NULL;
                    if(final_ans_head==NULL){
                        final_ans_head=ans_tmp;
                    }
                    else{
                        tmp_ans_ptr=final_ans_head;
                        while(tmp_ans_ptr->next != NULL){
                            tmp_ans_ptr=tmp_ans_ptr->next;
                        }
                        tmp_ans_ptr->next=ans_tmp;
                    }
                    
                }
            }
        }

        Node* remove_dup_i=NULL;
        Node* remove_dup_j=NULL;

        for(remove_dup_i=final_ans_head;remove_dup_i!=NULL;remove_dup_i=remove_dup_i->next){
            for(remove_dup_j=remove_dup_i->next;remove_dup_j!=NULL;remove_dup_j=remove_dup_j->next){
                if(remove_dup_i->row==remove_dup_j->row){
                    if(remove_dup_i->col==remove_dup_j->col){
                        remove_dup_i->val+=remove_dup_j->val;
                        Node* to_del_tmp=remove_dup_i;
                        while(to_del_tmp->next!=remove_dup_j){
                            to_del_tmp=to_del_tmp->next;
                        }
                        to_del_tmp->next=to_del_tmp->next->next;

                    }
                }
            }
        }

        Node* without_dup_sorted=mergeSort(final_ans_head);
        printf("\n");
        display(without_dup_sorted,n1,m2);

    }

};



int main(){

    // printf("1.ARRAY\n");
    // printf("2.LINKED LIST\n");
    int choice;
    cin>>choice;

    // printf("1.ADDITION\n");
    // printf("2.TRANSPOSE\n");
    // printf("3.MULTIPLICATION\n");
    int option;
    cin>>option;

    Sparse_Matrix<int> sm;

    if(choice==1){
        if(option==1){
            sm.add_sparse_mat_array();
        }
        else if(option==2){
            sm.transpose_sparse_mat_array();
        }
        else if(option==3){
            sm.mul_sparse_mat_array();
        }
    }
    else if(choice==2){
        if(option==1){
            sm.add_sparse_mat_LL();
        }
        else if(option==2){
            sm.transpose_sparse_mat_LL();
        }
        else if(option==3){
            sm.mul_sparse_mat_LL();
        }
    }
    // else{
    //     cout<<"ENTER CORRECT CHOICE!!"<<endl;
    // }

}
