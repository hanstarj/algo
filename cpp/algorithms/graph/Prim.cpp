#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <queue>
#include <cassert>

class Graph
{
public:
    struct Edge
    {
        int from;
        int to;
        int cost;
    };

public:
    Graph()
        : _bi(false)
    {
    }

    Graph(const std::vector<Edge> &edges, int N, bool bi = false)
        : _bi(bi)
    {
        _adjList.resize(N);
        for (const auto &e : edges)
        {
            AddEdge(e);
            if (bi)
                AddEdge({e.to, e.from, e.cost});
        }
    }

    Graph(Graph &&rhs)
        : _bi(rhs._bi), _adjList(std::move(rhs._adjList)), _edges(std::move(rhs._edges))
    {
    }

    int GetVertexCount() const
    {
        return _adjList.size();
    }

    const std::unordered_map<int, int> &GetEdges(int v) const
    {
        assert(v < _adjList.size());
        return _adjList[v];
    }

    const std::vector<Graph::Edge> &GetEdges() const
    {
        return _edges;
    }

    void AddEdge(const Graph::Edge &e)
    {
        assert(e.from != e.to);
        assert(e.from >= 0 && e.from < _adjList.size());
        assert(e.to >= 0 && e.to < _adjList.size());
        _edges.push_back(e);
        _adjList[e.from][e.to] = e.cost;
    }

private:
    bool _bi;
    std::vector<Edge> _edges;
    std::vector<std::unordered_map<int, int>> _adjList;
};

bool operator<(const Graph::Edge &a, const Graph::Edge &b)
{
    return a.cost > b.cost;
}

Graph Prim(const Graph &graph)
{
    int vertexCount = graph.GetVertexCount();
    if (vertexCount == 0)
        return Graph();

    std::unordered_set<int> toVisit;
    toVisit.reserve(vertexCount);
    for (int i = 0; i < vertexCount; ++i)
        toVisit.insert(i);

    Graph mst({}, vertexCount);
    std::priority_queue<Graph::Edge> q;
    do
    {
        int start = *toVisit.begin();
        toVisit.erase(start);
        const auto &outEdges = graph.GetEdges(start);
        for (auto &e : outEdges)
            q.push({start, e.first, e.second});

        while (!q.empty())
        {
            auto e = q.top();
            auto v = e.to;
            q.pop();
            if (toVisit.find(v) != toVisit.end())
            {
                toVisit.erase(v);
                mst.AddEdge(e);

                const auto &outEdges = graph.GetEdges(v);
                for (auto &outE : outEdges)
                {
                    if (toVisit.find(outE.first) != toVisit.end())
                        q.push({v, outE.first, outE.second});
                }
            }
        }
    } while (!toVisit.empty());

    return mst;
}

#include <iostream>
int main()
{
    const int vertexCount = 7;
    std::vector<Graph::Edge> edges = {
        {0, 1, 1},
        {0, 2, 3},
        {2, 3, 4},
        {3, 4, 2},
        {1, 4, 2},
        {4, 5, 3},
        {4, 6, 4},
        {5, 6, 2},
    };
    Graph graph(edges, vertexCount, true);

    Graph mst = Prim(graph);

    const auto &mstEdges = mst.GetEdges();
    for (auto &e : mstEdges)
        std::cout << e.from << " --" << e.cost << "-- " << e.to << std::endl;
    return 0;
}
