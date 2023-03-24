#include <tuple>
#include <vector>
#include <limits>
#include <queue>
#include <iostream>
#include <list>
#include <random>

using namespace std;

const double MAX_DOUBLE = numeric_limits<double>::max();

class Graph
{
public:
    Graph(int v) :
        v_(v),
        e_(),
        adj_matrix_(new double* [v])
    {
        for (int i = 0; i < v; i++)
        {
            double* matrix_row = new double[v];
            fill(matrix_row, matrix_row + v, 0);
            adj_matrix_[i] = matrix_row;
        }
    }

    int V() { return v_; }
    int E() { return e_; }

    bool adjacent(int x, int y)
    {
        return get_edge_value(x, y) > 0;
    }

    vector<int> neighbors(int x)
    {
        vector<int> result;

        for (int i = 0; i < v_; i++)
            if (get_edge_value(x, i) > 0)
                result.push_back(i);

        return result;
    }

    void add(int x, int y, double weight)
    {
        if (get_edge_value(x, y) > 0)
            ++e_;

        set_edge_value(x, y, weight);
        set_edge_value(y, x, weight);
    }

    void remove(int x, int y)
    {
        --e_;
        set_edge_value(x, y, 0);
        set_edge_value(y, x, 0);
    }

    int get_edge_value(int x, int y)
    {
        check_out_of_range(x, y);
        return adj_matrix_[x][y];
    }

    void set_edge_value(int x, int y, double weight)
    {
        check_out_of_range(x, y);
        adj_matrix_[x][y] = weight;
    }

private:
    int e_;
    const int v_;
    double** adj_matrix_;

    bool check_out_of_range(int x, int y)
    {
        if (x >= v_ || x < 0 || y >= v_ || y < 0)
            throw out_of_range("Index out of range!");
    }
};

template <class T>
class PriorityQueue
{
public:
    void insert(T el)
    {
        if (queue.empty()) queue.push_front(el);

        auto it = queue.begin();

        while (it != queue.end() && el > *it)
            ++it;

        queue.insert(it, el);
    }

    int size()
    {
        return queue.size();
    }

    bool empty()
    {
        return queue.empty();
    }

    bool contains(T el)
    {
        auto findIter = find(queue.begin(), queue.end(), el);

        return findIter != queue.end();
    }

    void pop()
    {
        if (queue.empty()) return;
        queue.pop_front();
    }

    T top()
    {
        return queue.front();
    }

private:
    list<T> queue;
};

class ShortestPath
{
public:
    ShortestPath(Graph g, int s = 0) :
        s_(s),
        g_(g),
        dist_(new double[g.V()])
    {
        fill(dist_, dist_ + g.V(), MAX_DOUBLE);
        calculate();
    }

    double path_size(int d)
    {
        return dist_[d];
    }

private:
    int s_;
    Graph g_;
    double* dist_;

    void calculate()
    {
        int v;
        double distance;
        PriorityQueue<tuple<double, int>> vertices;

        dist_[0] = 0;
        vertices.insert(make_tuple(0., s_));

        while (!vertices.empty()) {
            tie(distance, v) = vertices.top();
            vertices.pop();

            for (const int& w : g_.neighbors(v)) {
                double new_dist = dist_[v] + g_.get_edge_value(v, w);
                if (new_dist < dist_[w]) {
                    dist_[w] = new_dist;
                    vertices.insert(make_tuple(new_dist, w));
                }
            }
        }
    }
};

class Simulation
{
public:
    Simulation(
        int vertices_number,
        double density,
        double min_weight,
        double max_weight) :
        vertices_num_(vertices_number),
        density_(density),
        random_engine_(time(NULL)),
        existence_distribution_(0.0, 1.0),
        weight_distribution_(min_weight, max_weight) {}

    double run_simulation(int iterations_number)
    {
        double average_path_sum = 0;
        Graph graph = generate_graph();
        ShortestPath shortestPath(graph, 0);

        for (int i = 0; i < iterations_number; i++)
        {
            int path_tally = 0;
            double path_size_sum = 0;

            for (int j = 1; j < vertices_num_; j++)
            {
                double path_size = shortestPath.path_size(j);
                if (path_size < MAX_DOUBLE)
                {
                    path_tally++;
                    path_size_sum += path_size;
                }
            }

            double average_path = path_size_sum / path_tally;
            average_path_sum += average_path;
        }

        return average_path_sum / iterations_number;
    }

private:
    Graph generate_graph()
    {
        Graph graph(vertices_num_);

        for (int i = 0; i < vertices_num_; i++)
            for (int j = 0; j < vertices_num_; j++)
                if (existence_distribution_(random_engine_) < density_)
                    graph.add(i, j, weight_distribution_(random_engine_));

        return graph;
    }

    double density_;
    int vertices_num_;
    default_random_engine random_engine_;
    uniform_real_distribution<double> weight_distribution_;
    uniform_real_distribution<double> existence_distribution_;
};

int main()
{
    Simulation simulation_20(50, 0.2, 1., 10.);
    Simulation simulation_40(50, 0.4, 1., 10.);

    cout << "Result for 20% density : "
        << simulation_20.run_simulation(50)
        << endl;
    cout << "Result for 40% density : "
        << simulation_40.run_simulation(50)
        << endl;

    return 0;
}