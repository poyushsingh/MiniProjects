#include<iostream>
#include<algorithm>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

class pair_our{
    public:
    long long first;
    long long second;
};

class Heap{
    public:
    long long hpsize;
    pair_our* ar_pr;
    Heap(long long n){
        hpsize=0;
        ar_pr = new pair_our[n];
    }

    void push(pair_our val){
        long long ind=hpsize;
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
        for(long long i=start_ind;i>=0;i--){
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

string output_path;
void merge_small_files(long long no_of_partitions){

    FILE* in[no_of_partitions];

    for(long long i=0;i<no_of_partitions;i++){
        string t="tmp"+to_string(i)+".txt";
        in[i]=fopen(t.c_str(),"r");
    }

    FILE* out=fopen(output_path.c_str(),"w");

    Heap hp(no_of_partitions);
    pair_our pope;

    for(long long i=0;i<no_of_partitions;i++)
    {   
        long long tmpyui;
        long long *tmp_buffer=&tmpyui;
        fscanf(in[i],"%lld",tmp_buffer);
        pope.first=*tmp_buffer;
        pope.second=i;
        hp.push(pope);

    }

    long long count=0;

    while(count!=no_of_partitions){

        pair_our top=hp.top();
        long long min_ele=top.first;
        long long ind=top.second;
        hp.pop();

        fprintf(out,"%lld\n",min_ele);

        long long tmp2;
        long long* tmp_buffer2=&tmp2;
        int tmp=fscanf(in[ind],"%lld",tmp_buffer2);
        min_ele=*tmp_buffer2;

        if(tmp==1){
            pair_our to_insert;
            to_insert.first=*tmp_buffer2;
            to_insert.second=ind;

            hp.push(to_insert);
        }
        else{
            count++;

        }

    }

    for(long long i=0;i<no_of_partitions;i++){
        fclose(in[i]);

    }

    fclose(out);

    for(int i=0;i<no_of_partitions;i++){
        string t="tmp"+to_string(i)+".txt";
        remove(t.c_str());
    }

}

int main(int argc,char** argv){

    clock_t start, end;
    start = clock();

    string input_path=argv[1];
    output_path=argv[2];

    ifstream myfile(input_path);
    if(myfile.fail()){
        cout<<"File does not exists"<<endl;
    }

    long long chunk_size=1000000;
    long long no_of_partitions=0;
    vector<long long> arr;
    long long cnt=0;

    long long current_number=0;
    long long ii=0;

    while (myfile >> current_number){
        cnt++;
        arr.push_back(current_number);
        if(cnt==chunk_size){
            sort(arr.begin(),arr.end());
            string tmp="tmp";
            tmp=tmp+to_string(ii)+".txt";

            ofstream myfile2(tmp);

            for(long long i=0;i<arr.size();i++){
                myfile2<<arr[i];
                myfile2<<" ";
            }

            myfile2.close();
            ii++;
            arr.clear();
            cnt=0;
            no_of_partitions++;

            long long i=tmp.size()-1;
            while(isdigit(tmp[i])){
                tmp.pop_back();
                i--;
            }

        }
    }

    myfile.close();

    if(no_of_partitions==0){
        sort(arr.begin(),arr.end());

        FILE* out1=fopen(output_path.c_str(),"w");
        for(long long i=0;i<arr.size();i++){
            fprintf(out1,"%lld\n",arr[i]);
        }
        fclose(out1);

    }
    else{
        merge_small_files(no_of_partitions);

    }
    end = clock();

    double cpu_time_used =((double) (end - start)) / CLOCKS_PER_SEC;

    cout<<"Number of integers in a temporary file - "<<chunk_size<<"\n";
    cout<<"Number of temporary files created - "<<no_of_partitions<<"\n";
    printf("Total time taken by the program - %.2f\n",cpu_time_used);
}

