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
    vector <int> things; //вещи в рюкзаке
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
            ks[i][0].things.push_back(0);
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
                    for(int k=0; k < ks[i-th[j].v][j-1].things.size(); k++){
                        ks[i][j].things.push_back(ks[i-th[j].v][j-1].things[k]);
                    }
                    ks[i][j].things.push_back(j);
                    //cout<<i<< " " <<j <<" "<<i-th[j].v<< " " << th[j].cost<< "  "<<ks[i-th[j].v][j-1].cost << endl;
                }
                else{
                ks[i][j].cost = ks[i][j-1].cost;
                for(int k=0; k < ks[i][j-1].things.size(); k++){
                    ks[i][j].things.push_back(ks[i][j-1].things[k]);
                }
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

    int i = 0;
    for(int k=0; k < N; k++){
        if (i<ks[V_max-1][N-1].things.size()){
            if (ks[V_max-1][N-1].things[i] == k){
                cout<<1<<" "<<"\t";
                i++;
            }
            else{
            cout<<0<<" "<<"\t";
            } 
        }
        else{
            cout<<0<<" "<<"\t";
        }
            
    }
    cout<< endl;
    

    return;
}   

int main(){

    string name = "ks_100_0";
    solution(name);

    return 0;
}