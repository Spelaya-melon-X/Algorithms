#include <iostream>
#include <vector>
#include <algorithm>
#include <complex>
#include <iomanip>
using namespace std;
using cd = complex<double>;
const double  PI = acos(-1);
void fft(vector<cd>& a,bool inv){
    int n=a.size() ;
    for(int i=1,j=0;i<n;i ++ ){
        int  bit=n>>1;
        for(;j&bit;bit>>=1) j^=bit;
        j^=bit;  if(i<j)  swap(a[i],a[j]);
    }
    for(int len=2; len<=n ;len<<=1){
        double  ang = 2*PI/len*(inv ? -1 : 1 );
        cd wlen(cos(ang),sin(ang));
        for(int i=0;i<n;i +=len){
            cd w(1);
            for(int j=0;j<len/2;j ++){
                cd u=a[i + j], v=a[i  +  j  +  len/2 ]* w;
                a[i  +  j]=u  +  v;  a[ i  +   j     +  len/ 2] = u-v ; w *= wlen;
            }
        }
    }
    if(inv) for(auto &x:a) x/=n;
}
vector<long long> mulFFT(const vector<int>& A,const vector<int>& B){
    int n=1; while(n<(int)A.size() + (int)B.size()) n<<=1;
    vector<cd> fa(n);
    for(size_t i=0;i<A.size(); ++i) fa[i].real(A[i]);
    for(size_t i=0;i<B.size(); ++i) fa[i].imag(B[i]);
    fft(fa,false);
    vector<cd> fb(n);
    for(int i=0;i<n;i++ ){
        int j=(n-i)&(n-1);
        cd a1=(fa[i] +   (fa[j]))*0.5;
        cd b1=(fa[i]-conj(fa[j]))*(cd(0,-0.5));
        fb[i]=a1*b1;
    }
    fft(fb,true);
    vector<long long> res(n);
    for(int i=0;i<n;i ++ ) res[i]= (long long)(fb[i].real() + 0.5);
    return res;
}
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string sa,sb; getline(cin,sa); getline(cin,sb);
    
    auto trim=[](string &s){ int L=0; while(L<(int)s.size() && isspace((unsigned char)s[L]))  ++L;
        int R=s.size()-1; while(R>=0 && isspace((unsigned char)s[R])) --R;
        s = (L>R) ? string("0") : s.substr(L,R-L + 1);
    };
    trim(sa); trim(sb);
    auto strip=[&](string &s){ int i=0; while(i + 1<(int)s.size() && s[i]=='0')  ++i; s=s.substr(i); };

    strip(sa); strip(sb);
    if(sa=="0"||sb=="0"){ 
        cout<<"0\n";
        return 0; }
    const int BASE=1000, DIG=3;
    auto toChunks=[&](const string &s){
        vector<int> v;
        for(int i=(int)s.size(); i>0; i-= DIG){
            int st=max(0,i-DIG); v.push_back(stoi(s.substr(st,i-st)));
        }
        return v;
    };
    auto A=toChunks(sa), B=toChunks(sb);
    auto C=mulFFT(A,B);
    long long carry=0;
    for(size_t i=0;i<C.size(); ++i){ long long cur=C[i] + carry; C[i]=cur%BASE; carry=cur/BASE; }
    while(carry){ C.push_back(carry%BASE); carry/=BASE; }
    while(!C.empty() && C.back()==0) C.pop_back();
    cout<<C.back();
    for(int i=(int)C.size()-2;i>=0;--i) cout<<setw(DIG)<<setfill('0')<<C[i];
    cout<<"\n";
}
