#include <iostream>

using namespace std;

#define MAXN 100005
#define K 22


int sizeSet[MAXN], parent[MAXN];

void initSet(int n) {
    for(int i = 1; i<=n; i++){
        parent[i] = i;
        sizeSet[i] = 1;
    }
}
 
int findSet(int i) {
    if(parent[i] == i) return i;

    return parent[i] = findSet(parent[i]);
}
 
bool isSameset(int i, int j) {
    return (findSet(i)==findSet(j));
}
 
void unionSet(int i, int j) {
    int a = findSet(j);
    int b = findSet(i);

    if(a==b) return;
 
    if(sizeSet[a] >= sizeSet[b]){
        sizeSet[a]+=sizeSet[b];
        parent[b] = a;
    } else{
        sizeSet[b]+=sizeSet[a];
        parent[a] = b;
    }
}