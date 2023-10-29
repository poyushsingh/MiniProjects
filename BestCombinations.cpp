#include<iostream>
#include<stdlib.h>
using namespace std; 

void merge(int arr[],int temp[],int l,int mid,int r){
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


void mergesort(int arr[],int temp[],int l,int r){
    int mid;
    if(l<r){
        mid=(l+r)/2;
        mergesort(arr,temp,l,mid);
        mergesort(arr,temp,mid+1,r);
        merge(arr,temp,l,mid+1,r);
    }
}


class pair_our{
    public:
    long long first;
    long long second;
    pair_our(long long a,long long b){
        first=a;
        second=b;
    }
    pair_our(){}
};


pair_our ar_pr[2001];
class Heap{
    public:
    long long hpsize;
    Heap(){
        hpsize=0;
    }

    void push(pair_our val){
        int ind=hpsize;
        ar_pr[ind].first=val.first;
        ar_pr[ind].second=val.second;
        hpsize=hpsize+1;

        buildHeap(ar_pr,hpsize);
        
    }

    void heapify(pair_our arr[],long long size,long long i){
        long long maxi=i;
        long long leftchild=2*i+1;
        long long rightchild=2*i+2;

        if(leftchild<size && arr[i].first>arr[leftchild].first){
            maxi=leftchild;
        }
        if(rightchild<size && arr[maxi].first>arr[rightchild].first){
            maxi=rightchild;
        }
        if(maxi!=i){
            swap(arr[maxi].first,arr[i].first);
            swap(arr[maxi].second,arr[i].second);
            heapify(arr,size,maxi);
        }
    }

    void buildHeap(pair_our arr[],long long N){
        long long start_ind=(N/2)-1;
        for(int i=start_ind;i>=0;i--){
            heapify(arr,N,i);
        }
    }
    
    void pop(){
        if(hpsize==0){
            return;
        }
        else if(hpsize==1){
            hpsize--;
            return;
        }

        ar_pr[0].first=ar_pr[hpsize-1].first;
        ar_pr[0].second=ar_pr[hpsize-1].second;
        hpsize--;

        buildHeap(ar_pr,hpsize);
    }

    pair_our top(){
        return ar_pr[0];
    }
  

};

int main(){
    
    int n,k;
    cin>>n>>k;
    int abs[n];
    long long max_sum=0;
    for(int i=0;i<n;i++){          //0 based
        int tmp;
        cin>>tmp;
        if(tmp>=0){
            max_sum+=tmp;
            abs[i]=tmp;
        }
        else{
            abs[i]=-tmp;
        }
    }
        
    Heap hp;
    int tmp1[n];
    mergesort(abs,tmp1,0,n-1);
    
    pair_our po(abs[0],0);

    hp.push(po);

    long long to_subtract[k];
    int sizeof_to_subtract=0;

    while(hp.hpsize>0 && sizeof_to_subtract<k-1){
        pair_our tp=hp.top();

        hp.pop();

        long long tp_val=tp.first;
        long long tp_ind=tp.second;

        to_subtract[sizeof_to_subtract]=tp_val;

        sizeof_to_subtract++;

        if(tp_ind<n-1){
            pair_our p1(tp_val+abs[tp_ind+1],tp_ind+1);
            hp.push(p1);

            pair_our p2(abs[tp_ind+1]+(tp_val-abs[tp_ind]),tp_ind+1);
            hp.push(p2);

        }

    }
    
    long long ans[k+1];
    ans[0]=max_sum;
    for(int i=1;i<k;i++){
        ans[i]=(max_sum-to_subtract[i-1]);
    }
    
    for(int i=0;i<k;i++){
        cout<<ans[i]<<" ";
    }
        
}