#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;
int main() {
    double v0, k0,a1,b1,a2,b2,T,N;
    cin>>v0>>k0>>a1>>b1>>a2>>b2>>T>>N;
    v0-=a2/b2;
    k0-=a1/b1;
    vector<double> ts,vs,ks;
    for(int i=0;i<=N;i++){
        double t = i*(T/N);
        ts.push_back(t);
        vs.push_back(v0*cos(sqrt(a1*a2)*t)-k0*sqrt(a2)*b1*sin(sqrt(a1*a2)*t)/(b2*sqrt(a1))+a2/b2);
        ks.push_back(v0*sqrt(a1)*b2*sin(sqrt(a1*a2)*t)/(b1*sqrt(a2))+k0*cos(sqrt(a1*a2)*t)+a1/b1);
    }
    cout<<"t:"<<endl;
    for(int i=0;i<=N;i++){
        cout<<setprecision(2)<< fixed<<ts[i]<<" ";
    }
    cout<<endl<<"v:"<<endl;
    for(int i=0;i<=N;i++){
        cout<<vs[i]<<" ";
    }
    cout<<endl<<"k:"<<endl;
    for(int i=0;i<=N;i++){
        cout<<ks[i]<<" ";
    }
    cout<<endl;
    return 0;
}
