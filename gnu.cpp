#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#ifdef WIN32
#define GNUPLOT_NAME "C:\\gnuplot\\bin\\gnuplot -persist"
#else
#define GNUPLOT_NAME "gnuplot -persist"
#endif
using namespace std;
int main() {
#ifdef WIN32
    FILE* pipe = _popen(GNUPLOT_NAME,"w");
#else
    FILE* pipe = popen(GNUPLOT_NAME,"w");
#endif
    double v0, k0,a1,b1,a2,b2,T,N,maximumV=0, maximumK = 0;
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
        maximumV = max(maximumV,vs[i]);
    }
    cout<<endl<<"k:"<<endl;
    for(int i=0;i<=N;i++){
        cout<<ks[i]<<" ";
        maximumK = max(maximumK,ks[i]);
    }
    cout<<endl;
    //gnu
    fprintf(pipe,"%s\n","set multiplot");
    fprintf(pipe,"set xrange [0:%f]\n",max(maximumV,maximumK)+max(maximumV,maximumK)*0.1);
    fprintf(pipe,"set yrange [0:%f]\n",max(maximumV,maximumK)+max(maximumV,maximumK)*0.1);
    //define colors
    fprintf(pipe,"%s\n","set style line 1 lt rgb \"blue\" lw 1");
    fprintf(pipe,"%s\n","set style line 2 lt rgb \"red\" lw 2");
    fprintf(pipe,"%s\n","set style line 3 lt rgb \"yellow\" lw 3");
    fprintf(pipe,"%s\n","set style line 4 lt rgb \"green\" lw 4");
    //v(k(t))
    fprintf(pipe,"%s\n","plot '-' using 1:2 ls 1 title 'v(k(t))' with points ");
    for(int i=0;i<=N;i++){
        fprintf(pipe,"%f\t%f\n",ks[i],vs[i]);
    }
    fprintf(pipe,"%s\n","e");
    //k(v(t))
    fprintf(pipe,"%s\n","plot '-' using 1:2 ls 2 title 'k(v(t))' with points");
    for(int i=0;i<=N;i++){
        fprintf(pipe,"%f\t%f\n",vs[i],ks[i]);
    }
    fprintf(pipe,"%s\n","e");
    //victims
    fprintf(pipe,"%s\n","plot '-' using 1:2 ls 3 title 'victims' with points ");
    for(int i=0;i<=N;i++){
        fprintf(pipe,"%f\t%f\n",ts[i],vs[i]);
    }
    fprintf(pipe,"%s\n","e");
    //killers
    fprintf(pipe,"%s\n","plot '-' using 1:2 ls 4 title 'killers' with points");
    for(int i=0;i<=N;i++){
        fprintf(pipe,"%f\t%f\n",ts[i],ks[i]);
    }
    fprintf(pipe,"%s\n","e");
    fprintf(pipe,"%s\n","unset multiplot");
    fflush(pipe);

    return 0;
}
