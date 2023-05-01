#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

struct Edge {
    int node1;
    int node2;
};

class Graph {
public:
    Graph(int n) : adj_list(n) {}

    void add_edge(int u, int v) {
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    vector<int> &neighbors(int u) {
        return adj_list[u];
    }

    double global_clustering_coefficient() {
        double sum_cc = 0.0;
        for (int u = 0; u < adj_list.size(); u++) {
            vector<int> nbrs = neighbors(u);
            int num_nbrs = nbrs.size();
            int num_edges = 0;
            for (int i = 0; i < num_nbrs; i++) {
                for (int j = i + 1; j < num_nbrs; j++) {
                    int v = nbrs[i];
                    int w = nbrs[j];
                    if (is_edge(v, w)) {
                        num_edges++;
                    }
                }
            }
            if (num_nbrs >= 2) {
                double cc = (double) 2 * num_edges / ((double) num_nbrs * (num_nbrs - 1));
                sum_cc += cc;
            }
        }
        return sum_cc / adj_list.size();
    }

private:
    vector<vector<int>> adj_list;

    bool is_edge(int u, int v) {
        for (int w: neighbors(u)) {
            if (w == v) {
                return true;
            }
        }
        return false;
    }
};

ifstream read_file() {
    string filepath;
    cout << "Enter the file path: ";
    cin >> filepath;

    ifstream input_file(filepath);

    return input_file;
}

void print_set(set<int> input) {
    cout << "Vertices: ";
    for (auto it = begin(input); it != end(input); ++it) {
        cout << *it << ", ";
    }
    cout << endl;
}

int main() {
    Edge edge{};

    vector<Edge> edges;
    set<int> vertices;

    ifstream input_file = read_file();

    if (!input_file.is_open()) {
        cerr << "Couldn't open file" << endl;
        return -1;
    }

    while (input_file >> edge.node1 >> edge.node2) {
        edges.push_back(edge);
        vertices.insert(edge.node1);
        vertices.insert(edge.node2);
    }

    int num_vertices = vertices.size();
//    print_set(vertices);

    Graph g(num_vertices);

    for (auto it = begin(edges); it != end(edges); ++it) {
        g.add_edge(it->node1, it->node2);
        g.add_edge(it->node2, it->node1);
    }

    double global_cc = g.global_clustering_coefficient();

    cout << "Global clustering coefficient: " << global_cc << endl;

    return 0;
}
