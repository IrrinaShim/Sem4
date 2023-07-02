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
}

struct points{
    int f; //-1 - не пройдена, 1 - пройдена
    int next; //слледующая точка 
    vector <int> nearver; //вектор отсортированых по растоянию вершин 
} ver;

int* sort_prior(int l, int N, double* m){

    double p[N-1][2];

    for (int i=0; i<l; i++){
        p[i][0] = m[i];
        p[i][1] = i;
    }
    for (int i=l+1; i<N; i++){
        p[i-1][0] = m[i];
        p[i-1][1] = i;
    }

    bool sort = true;
    while (sort){
        sort = false;
        for(int i = 0; i < N - 2; i++)
            if (p[i][0] > p[i + 1][0]){
                int a = p[i][0];
                int b = p[i][1];
                p[i][0] = p[i+1][0];
                p[i][1] = p[i+1][1];
                p[i+1][0] = a;
                p[i+1][1] = b;
                sort = true;
            }
    }

    int* p1 = new int [N];
    for (int i=0; i<N-1; i++){
        p1[i] =  round(p[i][1]);
    }
    

    return p1;
}

double** reading(string name){
    ifstream file(name);
    
    int N;
    file >> N;
    global::N1 = N;
    
    double** A = new double *[N]; 
    for (int i=0; i < N; i++)
        A[i] = new double [N];

    double R[N][2];
    for(int i=0; i < N; i++){
        file >> R[i][1];
        file >> R[i][2];
    }

    file.close();
    
    for(int i=0; i < N; i++){
        for(int j=0; j < N; j++){
            A[i][j] = sqrt((R[i][1]-R[j][1])*(R[i][1]-R[j][1])+(R[i][2]-R[j][2])*(R[i][2]-R[j][2]));
        }
    }

	return A;
}

void solution(string name){
    double** A = reading(name);
    int N = global::N1;
    points ver[N];
    for (int i=0; i<N; i++){
        ver[i].f = 0;

        int* p = sort_prior(i, N, A[i]);
        for (int j = 0; j < N-1; j++){
        }   

        for (int j=0; j<N-1; j++){
            ver[i].nearver.push_back(p[j]);
        }
    }

    int way[N];
    way[0] = 0;
    ver[0].f = 1;
	
    double s = 0;
    //int s; //при прогоне через тестытип s был int, за счет округления результаты немного другие 

    for (int n = 1; n < N; n++){
        int k = 0;
        while(ver[ver[way[n-1]].nearver[k]].f == 1)
            k++;
        way[n] = ver[way[n-1]].nearver[k];
        ver[way[n]].f = 1;
        s = s+A[way[n-1]][way[n]];
    }
    s = s+A[way[0]][way[N-1]];
    int mins = s;

    int way1[N];
    for (int l = 1; l<N; l++){
        for (int i=0; i<N; i++)
            ver[i].f = 0;
        way1[0] = l;
        ver[l].f = 1;
        double s = 0;

        for (int n = 1; n < N; n++){
            int k = 0;
            while(ver[ver[way1[n-1]].nearver[k]].f == 1)
                k++;
            way1[n] = ver[way1[n-1]].nearver[k];
            ver[way1[n]].f = 1;
            s = s + A[way1[n-1]][way1[n]];
        }
        s = s + A[way1[0]][way1[N-1]];

        if (s<mins){
            mins = s;
            for (int i = 1; i < N; i++)
                way[i] = way1[i];
        }
        
    }

    cout<<mins<<endl;
   for (int i = 0; i < N; i++){
        cout<<way[i]+1<<" "<<"\t"; 
    }   

    return;
}

int main(){
/*   string S[74] = {"tsp_100_1", "tsp_100_2", "tsp_100_3", "tsp_100_4", "tsp_100_5", "tsp_100_6", "tsp_1000_1", "tsp_101_1", "tsp_105_1", "tsp_1060_1", "tsp_107_1",
"tsp_1084_1", "tsp_1173_1", "tsp_11849_1", "tsp_124_1", "tsp_127_1", "tsp_1291_1", " tsp_1304_1", " tsp_1323_1", " tsp_136_1", " tsp_1379_1", " tsp_1400_1", " tsp_14051_1", 
"tsp_1432_1", "tsp_144_1", "tsp_150_1", "tsp_150_2", "tsp_152_1", "tsp_1577_1", "tsp_159_1", "tsp_1655_1", "tsp_1748_1", "tsp_1817_1", " tsp_18512_1",
"tsp_1889_1", "tsp_195_1", "tsp_198_1", "tsp_200_1", " tsp_200_2", " tsp_2103_1", " tsp_2152_1", " tsp_225_1", " tsp_226_1", " tsp_2319_1", "tsp_2392_1",
"tsp_262_1", "tsp_264_1", " tsp_299_1", "tsp_3038_1", " tsp_318_1", " tsp_318_2", " tsp_33810_1", " tsp_3795_1", " tsp_400_1", " tsp_417_1", " tsp_439_1", 
"tsp_442_1", "tsp_4461_1", "tsp_493_1", "tsp_5_1", "tsp_51_1", "tsp_574_1", "tsp_575_1", "tsp_5915_1", "tsp_5934_1", " sp_654_1", " tsp_657_1", "tsp_70_1", 
"tsp_724_1", "tsp_7397_1", "tsp_76_1", "tsp_76_2", "tsp_783_1", "tsp_99_1"};
    for (int i=0; i<74; i++){
        cout<<S[i]<<"  "<< "\t";
        solution(S[i]);
    }*/

    string name = "tsp_100_4";
    solution(name);

    return 0;
}
