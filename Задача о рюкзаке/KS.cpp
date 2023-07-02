#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <string> 
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <math.h>
using namespace std;

namespace global {
  int N1;
  int V1;
}

struct кnapsacks{
    int cost; //общая стоимость
//    vector <int> things; //вещи в рюкзаке
} ks;

struct things{
    int v; //объем
    int cost; //ценность
} th;

int** reading(string name){
    ifstream file(name);
    
    int N, V;
    file >> N;
    file >> V;
    global::N1 = N;
    global::V1 = V;
    
    int** A = new int *[N]; 
    for (int i=0; i < N; i++)
        A[i] = new int [2];

    for(int i=0; i < N; i++){
        file >> A[i][1]; //ценность
        file >> A[i][0]; //вес
    }

    file.close();

	return A;
}

void solution(string name){
    int** A = reading(name);


    int V_max = global::V1;
    int N = global::N1;

    things th[N];
    for (int i=0; i<N; i++){
        th[i].v = A[i][0];
        th[i].cost = A[i][1];
    }
    
    кnapsacks** ks = new  кnapsacks *[V_max];
    for (int i=0; i < V_max; i++)
        ks[i] = new кnapsacks [N];

/*    for (int i=0; i<V_max; i++){
        for (int j=0; j<N; j++){
            for (int n=0; n<N; n++){
                ks[i][j].things[0] = 1;
            }
        }
    }*/

    for (int i=0; i<V_max; i++){
        if (th[0].v <= i+1){
            ks[i][0].cost = th[0].cost;
//            ks[i][0].things[0] = 1;
        }
        else{
            ks[i][0].cost = 0;
        }
//       cout << ks[i][0].cost << "  " << "\t";
    }
//    cout<<endl;

    for (int j=1; j<N; j++){
        for (int i=0; i<V_max; i++){
            if (i-th[j].v >= 0){
                if (ks[i][j-1].cost < th[j].cost + ks[i-th[j].v][j-1].cost){
                    ks[i][j].cost = th[j].cost + ks[i-th[j].v][j-1].cost;
                    //cout<<i<< " " <<j <<" "<<i-th[j].v<< " " << th[j].cost<< "  "<<ks[i-th[j].v][j-1].cost << endl;
                }
                else{
                ks[i][j].cost = ks[i][j-1].cost;
                //cout<<i<< " " <<j <<" "<<i-th[j].v<< " " << ks[i][j-1].cost<< endl;
                }
            }
            else{
                ks[i][j].cost = ks[i][j-1].cost;
                //cout<<i<< " " <<j <<" "<<i-th[j].v<< " " << ks[i][j-1].cost<< endl;
//            cout << ks[i][j].cost << "  " << "\t";
            }
//        cout << endl;
        }
    }

    cout<<ks[V_max-1][N-1].cost<<endl;

    return;
}   

int main(){

    string S[18] = {"ks_4_0","ks_19_0","ks_30_0", "ks_40_0","ks_45_0", "ks_50_0","ks_50_1",
    "ks_60_0","ks_100_0","ks_100_1","ks_100_2","ks_200_0","ks_200_1","ks_300_0","ks_400_0","ks_500_0","ks_1000_0","ks_10000_0"};

    for (int i=14; i<18; i++){
       cout<<S[i]<<"  "<< "\t";
       solution(S[i]);
    }

//    string name = "ks_19_0";
//    solution(name);

    return 0;
}
