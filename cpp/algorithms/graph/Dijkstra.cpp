#include <queue>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <algorithm>
#include <functional>

template <typename G>
std::vector<typename G::VertexIdType> Dijkstra(
    const G &graph,
    typename G::VertexIdType start,
    typename G::VertexIdType end)
{
    struct Step
    {
        typename G::VertexIdType from;
        typename G::VertexIdType to;
        typename G::CostType accumulatedCost;

        bool operator<(const Step &step) const { return step.accumulatedCost < accumulatedCost; }
    };

    std::unordered_map<typename G::VertexIdType, typename G::VertexIdType> tracker;
    std::priority_queue<Step> pq;
    pq.push(Step{start, start, 0.f});
    while (!pq.empty())
    {
        Step step = pq.top();
        pq.pop();

        tracker[step.to] = step.from;
        if (step.to == end)
            break;

        const auto from = step.to;
        const auto edges = graph.GetEdges(from); // better if we have iterator.
        for (const auto &edge : edges)
        {
            if (tracker.find(edge.to) == tracker.end())
                pq.push({from, edge.to, step.accumulatedCost + graph.GetCost(from, edge.to)});
        }
    }

    std::vector<typename G::VertexIdType> path;
    for (auto iter = tracker.find(end); iter != tracker.end(); iter = tracker.find(iter->second))
    {
        path.push_back(iter->first);
        if (iter->first == iter->second)
            break;
    }

    std::reverse(path.begin(), path.end());
    return path;
}

template <typename V, typename VID, typename C>
class BiGraph
{
public:
    using VertexType = V;
    using VertexIdType = VID;
    using CostType = C;

    struct Edge
    {
        VertexIdType to;
        CostType cost;
    };

public:
    BiGraph() = default;

    BiGraph(std::initializer_list<std::pair<VertexType, VertexIdType>> ilist)
    {
        verts.reserve(ilist.size());
        for (auto &i : ilist)
            verts[i.second] = i.first;
    }

    void AddVertex(const VertexType &v, VertexIdType id)
    {
        verts[id] = v;
    }

    void AddVertex(VertexType &&v, VertexIdType id)
    {
        verts[id] = std::move(v);
    }

    void AddEdge(VertexIdType a, VertexIdType b, CostType cost)
    {
        adjList[a].push_back({b, cost});
        adjList[b].push_back({a, cost});
    }

    float GetCost(VertexIdType a, VertexIdType b) const
    {
        auto neighbors = adjList.find(a);
        if (neighbors != adjList.end())
        {
            auto found = std::find_if(
                neighbors->second.begin(),
                neighbors->second.end(),
                [b](const Edge &e) { return e.to == b; });

            if (found != neighbors->second.end())
                return found->cost;
        }
        return std::numeric_limits<CostType>::max();
    }

    std::vector<Edge> GetEdges(VertexIdType v) const
    {
        auto edges = adjList.find(v);
        if (edges != adjList.end())
            return edges->second;
        return {};
    }

private:
    std::unordered_map<VertexIdType, VertexType> verts;
    std::unordered_map<VertexIdType, std::vector<Edge>> adjList;
};

enum class ECity
{
    Bellevue,
    Redmond,
    Kirkland,
    Seattle,
    MercerIsland,
    Kent,
    FederalWay,
    Lynwood,
    Everett,
    Renton
};

bool operator<(ECity a, ECity b) { return static_cast<int>(a) < static_cast<int>(b); }

namespace std
{
template <>
struct hash<ECity>
{
    using underlying_type = std::underlying_type<ECity>::type;
    size_t operator()(const ECity &value) const
    {
        return std::hash<underlying_type>()(static_cast<underlying_type>(value));
    }
};
} // namespace std

#include <iostream>

std::ostream &operator<<(std::ostream &os, ECity v)
{
    static const char *kCityNames[] = {
        "Bellevue",
        "Redmond",
        "Kirkland",
        "Seattle",
        "MercerIsland",
        "Kent",
        "FederalWay",
        "Lynwood",
        "Everett",
        "Renton"};
    return os << kCityNames[static_cast<int>(v)];
}

void PrintPath(const std::vector<ECity> &path)
{
    if (path.empty())
    {
        std::cout << "no path" << std::endl;
        return;
    }

    std::cout << "From " << path.front() << " To " << path.back() << ": " << path.front();
    for (auto point = path.begin() + 1; point != path.end(); ++point)
        std::cout << " -> " << *point;
    std::cout << std::endl;
}

int main()
{
    BiGraph<ECity, ECity, float> graph{
        {ECity::Bellevue, ECity::Bellevue},
        {ECity::Redmond, ECity::Redmond},
        {ECity::Kirkland, ECity::Kirkland},
        {ECity::Seattle, ECity::Seattle},
        {ECity::MercerIsland, ECity::MercerIsland},
        {ECity::Kent, ECity::Kent},
        {ECity::FederalWay, ECity::FederalWay},
        {ECity::Lynwood, ECity::Lynwood},
        {ECity::Everett, ECity::Everett},
        {ECity::Renton, ECity::Renton}};

    graph.AddEdge(ECity::Bellevue, ECity::Redmond, 1.f);
    graph.AddEdge(ECity::Bellevue, ECity::Kirkland, 0.8f);
    graph.AddEdge(ECity::Bellevue, ECity::MercerIsland, 1.f);
    graph.AddEdge(ECity::Bellevue, ECity::Kent, 1.2f);
    graph.AddEdge(ECity::Redmond, ECity::Kirkland, 0.5f);
    graph.AddEdge(ECity::Redmond, ECity::Seattle, 1.f);
    graph.AddEdge(ECity::Kirkland, ECity::Lynwood, 1.5f);
    graph.AddEdge(ECity::Seattle, ECity::Lynwood, 2.f);
    graph.AddEdge(ECity::Seattle, ECity::MercerIsland, 0.3f);
    graph.AddEdge(ECity::Seattle, ECity::FederalWay, 3.f);
    graph.AddEdge(ECity::Kent, ECity::Renton, 1.f);
    graph.AddEdge(ECity::Renton, ECity::FederalWay, 1.5f);
    graph.AddEdge(ECity::Lynwood, ECity::Everett, 1.f);

    PrintPath(Dijkstra(graph, ECity::Everett, ECity::Renton));
    PrintPath(Dijkstra(graph, ECity::Bellevue, ECity::Seattle));
    PrintPath(Dijkstra(graph, ECity::FederalWay, ECity::Lynwood));
    return 0;
}
