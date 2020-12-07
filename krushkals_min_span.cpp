// Kruskal's MST Algorithm
//  The edges are sorted according to their weights.
//  The edge with least cost is added to the MST if it does not create a cycle.
//  Each vertex is initially in the set of its own.
//  Thus, using a parent[] array (for each vertex that is a parent of its own) for e.g. parent[i]=i.
//  The least weighted edges are added one at a time.
//  If both end of the edges lie in the same set, then a cycle is formed and that edge is rejected. Otherwise, the edge is selected.
//  When an edge is added to the MST, all parameters are checked before adding.

#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;

//edge stores the vertices
#define edge pair< int, int>

class Graph
{
public:

    //double : The weight of the edge
    //graph : To store all the edges initially, MST: To store the final tree
    vector< pair < double, edge > > graph, MST;
    double totalCost{};

    //V : vertices and E : edges
    int V, E;

    //The parent[] array : To store the value of the root vertex for each vertex
    vector<int> parent;

    explicit Graph(int vertices)
    {
        V=vertices;
        parent.resize(V+1);
        E=0;
        //initially, the parent of a vertex is the vertex indeed!
        for(int i=0;i<=V;++i)
            parent[i]=i;
    }

    //Inserts all the edges to the graph constructor (can be added to a user-defined class easily)
    void insertEdge(int u, int v, double w)
    {
        graph.emplace_back(w, edge(u, v));
        E++;    //increment number of edges
    }

    //Returns the parent vertex of a node
    int findSet(int x)
    {
        if(x!=parent[x])
            parent[x]=findSet(parent[x]);

        return parent[x];
    }

    //MST algorithm : Kruskal's algorithm
    void kruskal()
    {
        int i, parentu, parentv, MSTsize;

        totalCost=0;

        //Sorts vertices according to weight
        sort(graph.begin(),graph.end());

        //Processes all the edges
        for(i=0; i<E;++i)
        {
            //Finds parent of each vertex
            parentu=findSet(graph[i].second.first);
            parentv=findSet(graph[i].second.second);

            //Checks if they are part of the same set or not
            if(parentu!=parentv)
            {
                MST.push_back(graph[i]);
                totalCost+=graph[i].first;

                //Parent of one vertex is made equal to the parent of the other vertex
                parent[parentu]=parent[parentv];
            }
        }

        MSTsize=MST.size();

        cout<<"Cost of MST: "<<totalCost<<endl<<endl;

        cout<<"<edge --- edge> = Weight:"<<endl;
        for(i=0; i<MSTsize; ++i)
        {
            cout<<MST[i].second.first<<"<--->"<<MST[i].second.second<<" = "<<MST[i].first<<endl;
        }


    }
};

int main()
{
    ifstream fin;
    fin.open("input.txt");                   //Opens a file name: input.txt

    int V = 0,E=0,u = 0,v = 0;              //Initializing values
    double w = 0;

    fin>>V;

    Graph G(V);

    while(!fin.eof())
    {
        fin>>u>>v>>w;
        E++;
        G.insertEdge(u,v,w);
    }

    G.kruskal();

    return 0;
}

