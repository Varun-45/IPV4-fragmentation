#include <iostream>
#include <climits>
#include <bits/stdc++.h>
using namespace std;


int fragmentation()
{
    int payload, mtu, header = 20;
    cout << "Enter the payload size (include header):" << endl;
    cin >> payload;
    cout << "Enter the mtu size:" << endl;
    cin >> mtu;
    int packets = ceil((payload - header) / (mtu - header));
    return packets;
}
int minimumDist(int dist[], bool Tset[], int n)
{
    int min = INT_MAX, index;
    for (int i = 0; i < n; i++)
    {
        if (Tset[i] == false && dist[i] <= min)
        {
            min = dist[i];
            index = i;
        }
    }
    return index;
}

void printPath(int parent[], int j)
{
    // Base Case : If j is source
    if (parent[j] == -1)
        return;
    printPath(parent, parent[j]);
    cout << "->" << j;
}

void Dijkstra(vector<vector<int>> graph, int src, int n, int dest)
{
    int dist[n];
    bool Tset[n];
    int parent[n];

    for (int i = 0; i < n; i++)
    {
        dist[i] = INT_MAX;
        Tset[i] = false;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int i = 0; i < n; i++)
    {
        int m = minimumDist(dist, Tset, n);
        Tset[m] = true;
        for (int j = 0; j < n; j++)
        {
            if (!Tset[j] && graph[m][j] && dist[m] != INT_MAX && dist[m] + graph[m][j] < dist[j])
            {
                dist[j] = dist[m] + graph[m][j];
                parent[j] = m; // update parent of j
            }
        }
    }

    for (int i = 0; i < n; i++)
    { // Printing

        if (i == dest)
        {
            if (dist[i] > 1000000)
            {
                cout << "No path available" << endl;
            }
            else
            {
                cout << "Vertex\t\tDistance from source\tShortest Path" << endl;
                char str = 65 + i; // Ascii values for pritning A,B,C..
                cout << str << "\t\t" << dist[i] << "\t\t\t" << src;
                printPath(parent, i);
                cout << endl;
            }
        }
    }
}

int main()
{
    int edges, size;

    cout << "What is number of nodes:" << endl;
    cin >> size;
    vector<vector<int>> graph(size, vector<int>(size));

    cout << "Enter the adjacency matrix for the graph:" << endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cin >> graph[i][j];
        }
    }
    cout << "Adjacency Matrix:" << endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << graph[i][j] << "  ";
        }
        cout << endl;
    }
    int packets = fragmentation();

    int flag;
    for (int k = 0; k < packets; k++)
    {

        cout << "1) Create new topology (press 1):" << endl;
        cout << "2) Continue with previous topology (press 0):" << endl;
        cin >> flag;
        char str = 65 + k;
        cout << "\t\t\tFor packet" << str << endl;
        if (flag == 1)
        {
            int source, dest;
            int newsize;

            cout << "What is number of nodes:" << endl;
            cin >> newsize;

            vector<vector<int>> newgraph(size, vector<int>(size));
            cout << "Enter the adjacency matrix for the graph:" << endl;
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    cin >> newgraph[i][j];
                }
            }
            cout << "Adjacency Matrix:" << endl;
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    cout << graph[i][j] << "  ";
                }
                cout << endl;
            }
            cout << "Enter the source of the packet:" << endl;
            cin >> source;
            cout << "Enter the destination for the packet:" << endl;
            cin >> dest;
            Dijkstra(newgraph, source, newsize, dest);
            graph = newgraph;
            size = newsize;
        }
        else
        {
            int source, dest;
            cout << "Enter the source of the packet:" << endl;
            cin >> source;
            cout << "Enter the destination for the packet:" << endl;
            cin >> dest;
            Dijkstra(graph, source, size, dest);
        }
    }

    return 0;
}
