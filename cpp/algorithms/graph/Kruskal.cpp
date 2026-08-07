#include <vector>
#include <unordered_map>
#include <algorithm>

struct Edge
{
    int v1;
    int v2;
    int cost;
};

bool operator<(const Edge &a, const Edge &b)
{
    return a.cost < b.cost;
}

int Find(int v, std::unordered_map<int, int> &parent)
{
    while (v != parent[v])
        v = parent[v];
    return v;
}

void Union(int g1, int g2, std::unordered_map<int, int> &parent)
{
    parent[g2] = g1;
}

std::vector<Edge> Kruskal(std::vector<Edge> edges)
{
    std::unordered_map<int, int> parent;
    for (auto &e : edges)
        parent[e.v2] = e.v2, parent[e.v1] = e.v1;

    int count = parent.size();
    std::sort(edges.begin(), edges.end());
    std::vector<Edge> mst;
    for (auto &e : edges)
    {
        auto g1 = Find(e.v1, parent);
        auto g2 = Find(e.v2, parent);
        if (g1 != g2)
        {
            mst.push_back(e);
            Union(g1, g2, parent);
            if (--count == 1)
                break;
        }
    }

    return mst;
}

#include <iostream>
int main()
{
    std::vector<Edge> edges = {
        {0, 1, 1},
        {0, 2, 3},
        {2, 3, 4},
        {3, 4, 2},
        {1, 4, 2},
        {4, 5, 3},
        {4, 6, 4},
        {5, 6, 2},
    };

    std::vector<Edge> mst = Kruskal(edges);
    for (auto &e : mst)
        std::cout << e.v1 << " --" << e.cost << "-- " << e.v2 << std::endl;
    return 0;
}
