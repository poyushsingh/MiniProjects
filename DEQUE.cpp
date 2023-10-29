#include<iostream>
#include<typeinfo>
using namespace std;

template<typename T> class DEQUE{
private:
    int f=-1,r=-1,s=0,cap=0;
    T* p;

public:
    T typevalue;

    void deque(){
        p=new (nothrow) T[5];
        if(!p){
            printf("FAILED\n");
        }
        
        cap=5;
        s=0;
    }


    void deque(int n,T x){
        p=new (nothrow) T[n];
        if(!p){
            printf("FAILED\n");
        }
        else{
            for(int i=0;i<n;i++){
                p[i]=x;
            }
        }
        s=n;
        cap=n;
        f=0;
        r=n-1;
    }


    void push_back(T x){
        if(f==-1 && r==-1){
            f=0;                    //means it is the 1st element 
            r=0;                    //to be pushed_back
            p[r]=x;
            
        }
        else if(s==cap){
            T *z=new T[2*cap];
             
            for(int i=0;i<cap;i++){
                z[i]=p[f];
                f=(f+1)%cap;
            }
            f=0;

            cap=2*cap;
            T *temp = p;
            p=z;
            delete[] temp;
            r=(r+1)%cap;
            p[r]=x;
        }
        else{
            r=(r+1)%cap;
            p[r]=x;
        }
        s++;
    }


    void pop_back(){
        if(s==0){
            cout<<"EMPTY\n"<<endl;
        }
        else{
            if(r==0 && f==0){
                f=-1;
                r=-1;
                s--;
                //means deque has only one element
            }
            else{
                r=(r-1+cap)%cap;
                s--;
                //done +cap ,inorder to avoid any -ve indexes
            }
            
        }
    }


    void push_front(T x){
        if(f==-1 && r==-1){
            f=cap-1;
            r=cap-1;            //means 1st element to be pushed_front
            p[f]=x;
        }
        else if(s==cap){
            T *z=new T[2*cap];

            for(int i=0;i<cap;i++){
                z[i]=p[f];
                f=(f+1)%cap;
            }
            f=0;
            r=cap-1;

            cap=2*cap;
            T *temp = p;
            p=z;
            delete[] temp;
            f=(f-1+cap)%cap;
            p[f]=x;
        }
        else{
            f=(f-1+cap)%cap;
            p[f]=x;
        }
        s++;
    }


    void pop_front(){
        if(s==0){
            cout<<"EMPTY"<<endl;
        }
        else if(r==0 && f==0){          //one element in deque
            r=-1;
            f=-1;
            s--;
        }
        else{
            f=(f+1)%cap;
            s--;
        }
    }
    
    
    bool empty(){
        return (s==0);
    }
    
    
    T front(){
        if(s==0){
            // cout<<"EMPTY"<<endl;
            modifiedtype();
            return typevalue;
        }
        else return p[f];
    }
    
    
    T back(){
        if(s==0){
            // cout<<"EMPTY"<<endl;
            modifiedtype();
            return typevalue;
        }
        else return p[r];
    }
    
    
    int size(){
        return s;
    }
    
    
    void clear(){
        f=-1;
        r=-1;
        s=0;
    }
    
    
    void resize(int x,T d){
        T *z=new T[x];
        if(x>s){
            int i=0;
            while(i<s){
                z[i]=p[f];
                f=(f+1)%cap;
                i++;
            }
            f=0;

            cap=x;
            delete[] p;
            p=z;
            delete[] z;
            int tempind=(s)%cap;
            while(tempind!=x){
                p[tempind]=d;
                tempind++;    
            }
            r=cap-1;
            s=x;
                
        }
        else if(x<s){
            int i=0;
            while(i<x){
                z[i]=p[f];
                f=(f+1)%cap;
                i++;
            }
            f=0;
            cap=x;
            s=x;
            r=cap-1;

        }
    }
    
    
    T operator [] (int n){
        if(n>=s || n<0){
            // cout<<"out of range"<<endl;
            modifiedtype();
            return typevalue;
        }                               //gives nth element (0-based indexing)
        else{
            return p[(f+n+cap)%cap];

        }
    }
    

    void modifiedtype(){
        if(typeid(T).name()==typeid(10).name()){
            typevalue=(int)0;
        }
        else if(typeid(T).name()==typeid((float)3.14).name() || typeid(T).name()==typeid((double)3.14).name()){
            typevalue=(float)(0.0);
        }
        else if(typeid(T).name()==typeid('p').name()){
            typevalue='\0';
        }
        else typevalue={};
    }

    
    // void print(){
    //     cout<<endl;
    //     for(int i=0;i<cap;i++){
    //         cout<<i<<" "<<p[i];
    //         cout<<endl;
    //     }
    //     cout<<endl;
    //     cout<<"FRONT:"<<f<<endl;
    //     cout<<"REAR:"<<r<<endl;
    //     cout<<"SIZE:"<<s<<endl;
    //     cout<<"CAPACITY:"<<cap<<endl;
    //     cout<<"EMPTY:"<<empty()<<endl;
    //     cout<<endl;  
    // }
    

};

int main(){
    DEQUE<int> d1;
    // deque<int> d1(7,"1000.123");
    int val;

    int choice,flag=1,n;
    while(flag){
        cout<<"\n";
        cout<<"choose from below:"<<"\n";
        cout<<"1.deque()"<<"\n";
        cout<<"2.deque(n,x)"<<"\n";
        cout<<"3.push_back(x)"<<"\n";
        cout<<"4.pop_back()"<<"\n";
        cout<<"5.push_front(x)"<<"\n";
        cout<<"6.pop_front()"<<"\n";
        cout<<"7.front()"<<"\n";
        cout<<"8.back()"<<"\n";
        cout<<"9.D[n]"<<"\n";
        cout<<"10.empty()"<<"\n";
        cout<<"11.size()"<<"\n";
        cout<<"12.resize(x,d)"<<"\n";
        cout<<"13.clear()"<<"\n";
        cout<<"14.Exit"<<"\n";
        cout<<"\n";

        cout<<"Enter choice:-"<<"\n";
        cin>>choice;

        switch (choice)
        {

        case 1:
            d1.deque();
            break;

        case 2:
            int n;
            cin>>n>>val;
            d1.deque(n,val);
            break;

        case 3:
            cin>>val;
            d1.push_back(val);
            break;

        case 4:
            d1.pop_back();
            break;

        case 5:
            cin>>val;
            d1.push_front(val);
            break;

        case 6:
            d1.pop_front();
            break;

        case 7:
            cout<<"Front:"<<d1.front()<<"\n";
            break;

        case 8:
            cout<<"Back:"<<d1.back()<<"\n";
            break;

        case 9:
            cin>>n;
            cout<<"D["<<n<<"]="<<d1[n]<<"\n";
            break;

        case 10:
            cout<<"isempty="<<d1.empty()<<"\n";
            break;

        case 11:
            cout<<"size="<<d1.size()<<"\n";
            break;
        
        case 12:
            int x;
            cin>>x>>val;
            d1.resize(x,val);
            break;

        case 13:
            d1.clear();
            break;

        case 14:
            flag=0;
            cout<<"BYE !!"<<"\n";
            break;

        default:
            cout<<"ENTER CORRECT CHOICE!!"<<"\n";
            break;
        }
      
    // d1.print();


    }
    
    return 0;

}


