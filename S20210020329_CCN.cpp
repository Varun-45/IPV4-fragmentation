#include <bits/stdc++.h>
using namespace std;

int fragmentation()
{
    float pl, mtu, header = 20;
    cout << "Enter the payload size (include header) (in bits):" << endl;
    cin >> pl;
    cout << "Enter the mtu size(with header) (in bits):" << endl;
    cin >> mtu;
    int packets = ceil((pl - header) / (mtu - header));
    return packets;
}


void displayshortestpath(int root[], int j)
{
    if (root[j] == -1)
        return;
    displayshortestpath(root, root[j]);
    cout << "->" << j;
}

void Dijkstra(vector<vector<int>> cost_matrix, int start, int n, int end)
{
    int len[n];
    bool Ps[n];
    int root[n];

    for (int i = 0; i < n; i++)
    {
        len[i] = INT_MAX;
        Ps[i] = false;
        root[i] = -1;
    }

    len[start] = 0;

    for (int i = 0; i < n; i++)
    {
          int min = INT_MAX, key;
    for (int i = 0; i < n; i++)
    {
        if (Ps[i] == false && len[i] <= min)
        {
            min = len[i];
            key = i;
        }
    }
        int m = key;
        Ps[m] = true;
        for (int j = 0; j < n; j++)
        {
            if (!Ps[j] && cost_matrix[m][j] && len[m] != INT_MAX && len[m] + cost_matrix[m][j] < len[j])
            {
                len[j] = len[m] + cost_matrix[m][j];
                root[j] = m; // update root of j
            }
        }
    }

    for (int i = 0; i < n; i++)
    { // Printing

        if (i == end)
        {
            if (len[i] > 1000000)
            {
                cout << "No path available" << endl;
            }
            else
            {
                cout << "Vertex\t\tdistance from source\tShortest Path" << endl;
                char str = 65 + i; // Ascii values for pritning A,B,C..
                cout << str << "\t\t" << len[i] << "\t\t\t" << start;
                displayshortestpath(root, i);
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
    vector<vector<int>> cost_matrix(size, vector<int>(size));

    cout << "Enter the adjacency matrix for the cost_matrix:" << endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cin >> cost_matrix[i][j];
        }
    }
    cout << "Adjacency Matrix:" << endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << cost_matrix[i][j] << "  ";
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
            int source, end;
            int newsize;

            cout << "What is number of nodes:" << endl;
            cin >> newsize;
            cout<< newsize;

            vector<vector<int>> newcost_matrix(newsize, vector<int>(newsize));
            cout << "Enter the adjacency matrix for the cost_matrix:" << endl;
            for (int i = 0; i < newsize; i++)
            {
                for (int j = 0; j < newsize; j++)
                {
                    cin >> newcost_matrix[i][j];
                }
            }
            cout << "Adjacency Matrix:" << endl;
            for (int i = 0; i < newsize; i++)
            {
                for (int j = 0; j < newsize; j++)
                {
                    cout << newcost_matrix[i][j] << "  ";
                }
                cout << endl;
            }
            cout << "Enter the source of the packet:" << endl;
            cin >> source;
            cout << "Enter the destination for the packet:" << endl;
            cin >> end;
            Dijkstra(newcost_matrix, source, newsize, end);
            cost_matrix = newcost_matrix;
            size = newsize;
        }
        else
        {
            int source, end;
            cout << "Enter the source of the packet:" << endl;
            cin >> source;
            cout << "Enter the destination for the packet:" << endl;
            cin >> end;
            Dijkstra(cost_matrix, source, size, end);
        }
    }

    return 0;
}
