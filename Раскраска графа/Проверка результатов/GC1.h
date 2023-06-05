#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <string> 
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <set>
using namespace std;

namespace global {
  int N1 ;
  int k1;
}

struct vertex{
    int f; //-1 - не окрашена, иначе номер цвета
    int fcol; //количество допустимых цветов
    int n_adjvertex; //количество смежных вершин 
    int n_forbidden_colors;
    vector <int> adjvertex; //вектор смежных вершин
    vector <int> forbidden_colors; //вектор запрещенных цветов
} ver;

//считываем из файла
int** reading(string name){
    ifstream file(name);
    
    int N, k;
    file >> N;
    file >> k;
    global::N1 = N;
    global::k1 = k;
 //   cout <<N<<" "<<k<< endl;
    
    int** A = new int *[N]; 
    for (int i=0; i < N; i++)
        A[i] = new int [N];

    for(int i=0; i < N; i++){
        for(int j=0; j < N; j++){
            A[i][j] = 0;
        }
    }
    int a;
    int b;
    
    for(int i=0; i < k; i++){
        file >> a;
        file >> b;
        A[a][b]=1;
        A[b][a]=1;
    }
    
/*    for(int i=0; i < N; i++){
        for(int j=0; j < N; j++){
            cout << A[i][j] << "\t";
        }
        cout << endl;
    }*/
    
    file.close();

	return A;
}

void zamena(int i, int j, int** p){
    int a = p[i][0];
    int b = p[i][1];
    int c = p[i][2];
    p[i][0] = p[j][0];
    p[i][1] = p[j][1];
    p[i][2] = p[j][2];
    p[j][0] = a;
    p[j][1] = b;
    p[j][2] = c;
    return;   
}

void sort_prior(int l, int N, int** p){
    bool sort = true;
    while (sort){
        sort = false;
        for(int i = 0; i < l -1; i++)
            if (p[i][1] > p[i + 1][1] || (p[i][1] == p[i + 1][1] && p[i][2] < p[i + 1][2]))
            {
                zamena(i, i+1, p);
                sort = true;
            }
    }
    return;
}

// пытаемся раскрасить в K цветов
int k_construction(int k, vertex* ver){

    int N = global::N1;
    int E = global::k1;

    int** prioretetes = new int *[N];
    for (int i=0; i < N; i++)
        prioretetes[i] = new int [3];
    int col[k][2]; //массив с количеством вершин окрашенных в каждый цвет

    for (int i = 0; i<N; i++){
        prioretetes[i][0] = i;
        prioretetes[i][1] = k; //количество допустимых цветов
        prioretetes[i][2] = ver[i].n_adjvertex;
    }  
    int l = N; //количество неокрашеных вершин  
    sort_prior(l, N, prioretetes);

    for (int i = 0; i<k; i++){
        col[i][0] = i; //номер цвета
        col[i][1] = 0; // сколько в него уже окрашено
    }  

/*    for (int i = 0; i<N; i++){
        cout<<prioretetes[i][0]<<" "<<prioretetes[i][1]<<" "<<prioretetes[i][2]<<endl;
    }*/    

    for (int g=0; g<N; g++){
        int n = prioretetes[0][0];
        if (prioretetes[0][1] == 0) return 1;
        int j = 0;
        bool f = true;
        while (f && j<k){
            f = false;
            for (int i=0; i<ver[n].fcol; i++)
                if (col[j][0] == ver[n].forbidden_colors[i])
                    f = true;
            if (f) j = j+1;
        }

        col[j][1] ++;
        int c = col[j][0];
        while (col[j][1]>col[j+1][1] && j+1<k){
            int a = col[j][0];
            int b = col[j][1];
            col[j][0] = col[j+1][0];
            col[j][1] = col[j+1][1];
            col[j+1][0] = a;
            col[j+1][1] = b;
            j++;
        }
        prioretetes[0][0] = -1;
        if (l>0) l = l-1;
        zamena(0, l, prioretetes);

        ver[n].f = c;
        for (int i=0; i<ver[n].n_adjvertex; i++){
            int t = ver[n].adjvertex[i];
            f = true;
            for (int j=0; j<ver[t].fcol; j++)
                if (c == ver[t].forbidden_colors[j])
                    f = false;
            if (f){
                ver[t].fcol++;
                ver[t].forbidden_colors.push_back(c);
            }
        }
        for (int i = 0; i<l; i++){
            prioretetes[i][1] = k - ver[prioretetes[i][0]].fcol;
        }   
        sort_prior(l, N, prioretetes);
    }

    return 0;
}

void graph_coloring(string name){

    int** A = reading(name);

//    cout<<global::N1<<endl;

    vertex ver[global::N1];
    for(int i = 0; i<global::N1; i++){
        ver[i].n_adjvertex = 0;
        ver[i].fcol = 0;
        ver[i].f = -1;
        for(int j = 0; j<global::N1; j++)
            if (A[i][j] == 1){
                ver[i].n_adjvertex++;
                ver[i].adjvertex.push_back(j);
            }
    }

    
   int flag = 1;
    int k = 1;
    while (flag){
        flag = k_construction(k, ver);
        if (flag){
            k++;
            for(int i = 0; i<global::N1; i++){
                ver[i].fcol = 0;
                ver[i].forbidden_colors.clear();
                ver[i].f = -1;
            }    
        }
    }

    cout<<k<< endl;
/*    for(int i=0; i < global::N1; i++){
        cout << ver[i].f<<" "<< "\t";
    }*/

	return;
}