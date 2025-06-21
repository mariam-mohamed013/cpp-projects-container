#include <iostream>
using namespace std;

const int MAX = 100; 


void BFS(int adj[MAX][MAX], int n, int startX, bool visited[MAX]) {
    int queue[MAX], front = 0, back = 0; 

    visited[startX] = true; 
    queue[back] = startX; 
    back++; 

    while (front < back) {
        int node = queue[front];
        front++; 
        cout << "Visited: " << node << endl;

        for (int i = 0; i < n; i++) {
            if (adj[node][i] == 1 && !visited[i]) {
                visited[i] = true; 
                queue[back] = i; 
                back++; 
            }
        }
    }
}

void DFSRecursive(int adj[MAX][MAX], int n, int node, bool visited[MAX]) {
    visited[node] = true; 
    cout << "Visited: " << node << endl;
    for (int i = 0; i < n; i++) {
        if (adj[node][i] == 1 && !visited[i]) {
            DFSRecursive(adj, n, i, visited); 
        }
    }
}


void DFSStack(int adj[MAX][MAX], int n, int startX, bool visited[MAX]) {
    int stack[MAX], top = -1; 

    stack[++top] = startX; 

    while (top >= 0) {
        int node = stack[top--]; 

        if (!visited[node]) {
            visited[node] = true; 
            cout << "Visited: " << node << endl;
        }

        for (int i = n - 1; i >= 0; i--) { 
            if (adj[node][i] == 1 && !visited[i]) {
                stack[++top] = i; 
            }
        }
    }
}

int main() {
    int m; 
    cout << "Enter the number of edges: ";
    cin >> m;

    int adj[MAX][MAX] = { 0 }; 
    bool visited[MAX] = { false }; 

    int startNodes[MAX] = { 0 };
    bool isChild[MAX] = { false }; 

    int root = -1;
    int maxNode = -1; 
  
    cout << "Enter the edges (s e) where s and e are node indices (can be any values):\n";
    for (int i = 0; i < m; i++) {
        int s, e;  
        cin >> s >> e;
        adj[s][e] = 1; 
        adj[e][s] = 1; 

        isChild[e] = true; 
       
        if (i == 0 && root == -1) {
            root = s;
        }

        if (s > maxNode) maxNode = s;
        if (e > maxNode) maxNode = e;
    }

   
    int n = maxNode + 1;

    cout << "The root node is: " << root << endl;

    for (int i = 0; i < n; i++) visited[i] = false;

    
    cout << "\nBFS Traversal:\n";
    BFS(adj, n, root, visited); 

    for (int i = 0; i < n; i++) visited[i] = false;

    cout << "\nDFS Recursive Traversal:\n";
    DFSRecursive(adj, n, root, visited); 
    for (int i = 0; i < n; i++) visited[i] = false;

    cout << "\nDFS Stack Traversal:\n";
    DFSStack(adj, n, root, visited); 

    return 0;
}