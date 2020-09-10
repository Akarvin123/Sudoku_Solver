#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <chrono> 
#include <climits>
#define  ui uint8_t
using namespace std;
int check_fill(vector<vector<int> > &v){
    for(int i = 0;i<9;i++)
        for(int j = 0;j<9;j++)
            if(v[i][j]==0) return 0;
    
    return 1;
}
map<int,set<int> > get_row(vector<vector<int> > &v){
    map<int,set<int> > m;
    for(int i = 0;i<9;i++)
        for(int j = 0;j<9;j++)
            if(v[i][j]!=0)
            m[v[i][j]].insert(i);
    return m;
}
map<int,set<int> > get_column(vector<vector<int> > &v){
    map<int,set<int> > m;
    for(int i = 0;i<9;i++)  
        for(int j = 0;j<9;j++)
            if(v[i][j]!=0)
            m[v[i][j]].insert(j);
    return m;
}

map<int,set<int> > get_block(vector<vector<int> > &v){
    map<int,set<int> > m;
    for(int i = 0;i<9;i++)
        for(int j = 0;j<9;j++)
            if(v[i][j]!=0)
            m[(((int)(i/3))*3 + j/3)].insert(v[i][j]);
    return m;
}
map<pair<int,int>,vector<int> > get_domain(vector<vector<int> > &v){
    map<int,set<int> > column = get_column(v), block = get_block(v), row = get_row(v);
    map<pair<int,int> ,vector<int> > m;
    for(int i = 0;i<9;i++){
        for(int j = 0;j<9;j++){
            int x = i;
            int y = j;
            int pos_block = (((int)(x/3))*3 + y/3);
            if(v[i][j]==0)
            for(int fill = 1;fill<=9;fill++){
                if(binary_search(block[pos_block].begin(),block[pos_block].end(),fill)) continue;
                if(binary_search(row[fill].begin(),row[fill].end(),x)) continue;
                if(binary_search(column[fill].begin(),column[fill].end(),y)) continue;
                m[make_pair(i,j)].push_back(fill);
            }
        }
    }
    return m;
}


int print(vector<vector<int> > &v){
    for(int i = 0;i<9;i++){
        for(int j = 0;j<9;j++)
            cout << v[i][j] << " ";
        cout << endl;
    }
    return 1;
}

pair<int,int> get_min(map<pair<int,int>,vector<int> > &domain){
    int min1 = 20;
    for(int i = 0;i<9;i++){
        for(int j = 0;j<9;j++){
            if(domain.count(make_pair(i,j))!=0)
            min1 = min((int)domain[make_pair(i,j)].size(),min1);
        }
    }
    for(int i = 0;i<9;i++){
        for(int j = 0;j<9;j++){
            if(domain.count(make_pair(i,j))!=0)
            if(min1 == domain[make_pair(i,j)].size())
                return make_pair(i,j);
        }
    }
    
}

int solve(vector<vector<int> > v){
    if(check_fill(v)){
        print(v);
        return 1;
    }
    map<pair<int,int>,vector<int> > domain = get_domain(v);
    pair<int,int> p = get_min(domain);
    for(auto i:domain[p]){
        vector<vector<int> > temp  = v;
        temp[p.first][p.second] = i;
        int p  = solve(temp); 
        if(p==1) return 1;
    }

}
int main(){
    vector<vector<int> > v(9);
    cout << "Enter {0, [1-9]: filled} \n";
    for(int i = 0;i<9;i++){
        v[i].resize(9);
        for(int j =0 ;j<9;j++){
            cin >> v[i][j];
        }

    }
    cout << endl << endl;
    auto start_time = chrono::high_resolution_clock::now();
    solve(v);
    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time-start_time).count();
    cout << duration/1000000.00;
    exit(0);

}

/*
9 2 0 8 0 0 0 4 0 
0 0 1 3 4 0 0 0 6
4 0 3 0 5 6 8 0 0 
2 1 0 0 6 4 5 0 0
0 0 4 5 0 0 0 0 0 
6 0 5 1 0 2 4 7 0
0 0 8 0 2 0 0 1 3
0 4 0 0 1 0 0 0 0 
0 9 7 6 0 3 2 0 4

0 0 0 6 0 8 9 1 0
0 9 0 4 3 2 6 8 7
0 6 3 9 0 0 2 0 4
9 0 0 3 0 4 0 0 2
3 1 0 0 0 0 0 7 9
0 7 0 0 0 9 5 0 0
0 0 1 0 9 6 3 0 0
0 0 0 0 0 1 0 2 0
0 0 6 7 4 0 8 0 1

2 0 0 0 7 0 3 0 0
7 0 3 9 1 6 0 0 0
0 0 6 0 8 0 1 5 0
0 0 1 0 9 4 0 0 0 
0 0 0 1 0 0 0 0 0 
0 0 0 0 2 0 8 0 0
0 6 2 0 0 0 4 0 5
0 7 0 0 5 0 0 2 8
0 8 0 0 0 9 7 6 0

0 0 8 0 0 0 4 0 2
0 0 0 3 2 0 7 8 0
7 0 2 5 0 6 0 0 0
0 0 3 0 5 0 0 0 4
0 0 9 7 4 0 2 0 0 
0 0 6 2 0 0 0 0 0
0 0 0 0 0 0 5 0 0
9 0 0 0 0 5 6 0 0
6 2 0 0 0 0 1 9 0
*/
