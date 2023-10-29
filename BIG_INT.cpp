#include<iostream>
using namespace std;

#define SIZE 50000
template <class T> class Stack{

private:
    int top;
    T arr[SIZE];

public:
    Stack();

    void push(T k);

    void pop();

    T topEle();

    bool isFull();

    bool isEmpty();

};

template <class T>
Stack<T>::Stack(){
    top=-1;

}

template <class T>
void Stack<T>::push(T k){
    if(isFull()){
        cout<<"FULL\n";
    }
    top=top+1;
    arr[top]=k;

}

template <class T>
T Stack<T>::topEle(){
    T topelement=arr[top];
    return topelement;

}

template <class T>
void Stack<T>::pop(){
    top=top-1;

}

template <class T>
bool Stack<T>::isFull(){
    if(top==(SIZE-1)){
        return 1;
    }
    else return 0;

}

template <class T>
bool Stack<T>::isEmpty(){
    if(top==-1){
        return 1;
    }
    else return 0;

}


class BigInteger{

public:

// Performs addition of two strings
string add(string t1,string t2){
    int carry=0,sum=0;
    string ans="";

    int i=t1.size()-1;
    int j=t2.size()-1;
    while(i>=0 && j>=0){
        sum=((t1[i]-'0')+(t2[j]-'0')+carry)%10;
        carry=((t1[i]-'0')+(t2[j]-'0')+carry)/10;
        ans=to_string(sum)+ans;
        i--;j--;
    }
    while(i>=0 ){
        sum=((t1[i]-'0')+carry)%10;
        carry=((t1[i]-'0')+carry)/10;
        ans=to_string(sum)+ans;
        i--;
    }

    while(j>=0 ){
        sum=((t2[j]-'0')+carry)%10;
        carry=((t2[j]-'0')+carry)/10;
        ans=to_string(sum)+ans;
        j--;
    }
    if(carry){
          ans=to_string(1)+ans;
    }

    return ans;

}


// Performs multiplication of two strings
string mul(string x,string y){
    if(x=="0" || y=="0"){
        return "0";
    } 
    int power=0;
    int l1=x.size();
    int l2=y.size();
    int ans[l1+l2]={0};

    for(int j=l2-1;j>=0;j--){
        int carry=0,pro=1;
        int i=l1-1;
        int place=l1+l2-1-power;               //place tells us from which place to begin from RHS,
        while(i>=0){                           //i.e,how many places to leave.
            pro=((x[i]-'0')*(y[j]-'0')+ans[place]+carry)%10;    //ans[place] is included because we ,
            carry=((x[i]-'0')*(y[j]-'0')+ans[place]+carry)/10;  //will add and update at the same time.

            ans[place]=pro;
            place--;
            i--;
        }
        ans[place]=carry;
        place--;
        power++;            //power++ means we are telling place to shift left after every iteration.
    }

    int j=0;
    while(ans[j]==0){
          j++;                  //removing zeros from beginning of answer.
    }
    
    string result="";
    for(;j<(l1+l2);j++){
        result+=to_string(ans[j]);
    }

    return result;

}


// performs 10's complement of smaller string
string comp(string str){
    string comp="";
    for(int i=0;i<str.length();i++){
        comp+=('9'-str[i])+'0';           //subtracting each digit of ,
    }                                   //smaller number by 9to get 9's , 
                                        //complement and then adding 1 to                
    return add(comp,"1");               //get 10's complement.

}


// Performs Subtraction of two strings
string sub(string t1,string t2){
    if(isequal(t1,t2)){
        return "0";
    }
    if(t2.length()<t1.length()){            //done because unequal lenghts, 
          int diff=t1.length()-t2.length(); //gives incorrect answer,
          for(int i=0;i<diff;i++){          //while finding 10's complement.
                t2='0'+t2;
          }
    }
    string compt2=comp(t2);

    string ans=add(t1,compt2);

    ans[0]='0';                     // Done because when we do large-small,
                                    //in 10's complement it gives carry,
    int j=0;                        //and for correct answer we need to,
    while(ans[j]=='0'){             //discard that carry.
        j++;
    }

    string answithoutzero="";
    for(;j<ans.size();j++){
        answithoutzero+=ans[j];     //removing zeros from beginning of answer.
    }

    return answithoutzero;

}

// gives the priority of operator
int priority(char opr){
    if(opr=='x'){
        return 2;
    }
    if(opr=='+' || opr=='-'){
        return 1;
    }
    else return 0;

}


//evaluates the operation on t1 and t2
string evaluate(string t1,string t2,char operar){
    if(operar=='+') return add(t1,t2);
    if(operar=='-') return sub(t1,t2);
    else return mul(t1,t2);
     

}


string fastexpo(string base,long long exponent){
    if(exponent==0) return "1";
    if(exponent==1) return base;
    string temp=fastexpo(base,exponent/2);
    if(exponent%2 == 0){                            //Fast exponentiation 
        return mul(temp,temp);
    }
    else return mul(mul(temp,temp),base);

}


bool isgreater(string a,string b){
    int i=0;
    while(a[i]=='0' && i<a.size()){
        i++;
    }
    int asizewithout0=a.size()-i;
    string updateda="";
    for(int i=0;i<asizewithout0;i++){
        updateda[i]=a[i];
    }

    int j=0;
    while(b[j]=='0' && j<b.size()){
        j++;
    }
    int bsizewithout0=b.size()-j;
    string updatedb="";
    for(int i=0;i<asizewithout0;i++){
        updatedb[i]=b[i];
    }

    if(asizewithout0>bsizewithout0){
        return 1;                       
    }
    else if(asizewithout0==bsizewithout0){
        int i=0;
        if(updateda[i]>updatedb[i]){
            return 1;
        }
        else if(updateda[i]<updatedb[i]){
            return 0;
        }
        else{
            while(updateda[i]==updatedb[i]){
                i++;
            }
            if(updateda[i]>updatedb[i]){
                return 1;
            }
            else{
                return 0;
            }
        }
    }
    else{
        return 0;
    }

}

bool isequal(string a,string b){
    if(a.size()!=b.size()){
        return 0;
    }
    else{
        int i=0;
        while(i<a.size()){
            if(a[i]!=b[i]){
                return 0;
            }
            i++;
        }
        return 1;
    }

}


string longdiv(string s1,string s2){
    if(s2.size()>s1.size()){
        return "0";
    }
    string ans="";
    int ind=0;
    string temp="";
    temp+=s1[ind];
            
    while(isgreater(s2,temp)){
        string tempasd="";
        ind++;
        tempasd+=s1[ind];
        temp=add(mul(temp,"10"),tempasd);
    }
     
    while(s1.size()>ind){
        string cnt="1";
        string tempmul=mul(s2,cnt);

        while(isgreater(temp,tempmul) || isequal(temp,tempmul)){
            cnt=add(cnt,"1");
            tempmul=mul(s2,cnt);
        }

        string q=sub(cnt,"1");
        string r=sub(temp,mul(s2,q));
                 
        ans+=q;
      
        string dsa="";
        ind++;
        dsa+=s1[ind];
        temp=add(mul(r,"10"),dsa);
    }
    return ans;
}


string mod(string s1,string s2){
    string quo=longdiv(s1,s2);
    string modulo=sub(s1,mul(s2,quo));
    return modulo;
}


string gcd(string a,string b){
    if(a=="0") return b;
    if(b=="0") return a;
    else return gcd(b,mod(a,b));
}


string factorial(string s){
    if(s=="2") return "2";
    else return mul(s,factorial(sub(s,"1")));

}

};


int main(){

    int  typeofoperation;
    BigInteger bi;
    while(1){
        printf("Enter type of operation code:\n");
        printf("1.Expression\n");
        printf("2.Exponentiation\n");
        printf("3.GCD\n");
        printf("4.Factorial\n");
        printf("5.Exit\n");
        
        cin>>typeofoperation;

        if(typeofoperation==1){
            printf("Enter String:");
            string s="";
            cin>>s;

            Stack<string> num;
            Stack<char> opr;

            for(int i=0;i<s.length();i++){
                if(s[i]>='0' && s[i]<='9') {
                    string val="";
                    while(i<s.length() && (s[i]>='0' && s[i]<='9')){
                        val+=to_string(s[i]-'0');
                        i++;
                    }
                    i--;
                    num.push(val);
                }
                else{
                    while(!opr.isEmpty() && bi.priority(opr.topEle()) >= bi.priority(s[i])){
                        string t1=num.topEle();
                        num.pop();
                        
                        string t2=num.topEle();
                        num.pop();
                        
                        char operar=opr.topEle();
                        opr.pop();
                        
                        num.push(bi.evaluate(t2,t1,operar));
                    }
                    opr.push(s[i]);
                }

            }

            while(!opr.isEmpty()){
                string t1=num.topEle();
                num.pop();
                
                string t2=num.topEle();
                num.pop();
                
                char operar=opr.topEle();
                opr.pop();
                
                num.push(bi.evaluate(t2,t1,operar));
            }

            cout<<num.topEle()<<"\n";
            cout<<"\n";

        }
        else if(typeofoperation==2){
            string base="";
            long long exponent=0;
            printf("Enter Base:");
            cin>>base;
            printf("Enter exponent:");
            cin>>exponent;

            string ansofexpo="";

            ansofexpo=bi.fastexpo(base,exponent);

            for(int i=0;i<ansofexpo.size();i++){
                cout<<ansofexpo[i];
            }
            cout<<"\n";

        }
        else if(typeofoperation==3){
            string a="";
            string b="";
            printf("Enter 1st num:\n");
            cin>>a;
            printf("Enter 2nd num:\n");
            cin>>b;
            string ansofgcd=bi.gcd(a,b);

            cout<<ansofgcd;
            cout<<"\n";

        }
        else if(typeofoperation==4){
            string n="";
            printf("Enter number:");
            cin>>n;

            string ansoffact=bi.factorial(n);
            for(int i=0;i<ansoffact.size();i++){
                cout<<ansoffact[i];
            }
            cout<<"\n";

        }
        else if(typeofoperation==5){
            printf("BYE!!\n");
            break;
        }
        else {
            cout<<"ENTER CORRECT OPERATION NUMBER !"<<"\n";
        }
    }

    return 0;
        
}
