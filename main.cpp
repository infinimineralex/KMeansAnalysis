#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <sciplot/sciplot.hpp>

using namespace std;
using namespace sciplot;

// calculate the euclidean distance between two points
double euclidean_distance(const vector<double> &a, const vector<double> &b)
{
    double sum = 0.0;
    for (int i = 0; i < a.size(); i++)
    {
        sum += pow(a[i] - b[i], 2);
    }
    return sqrt(sum);
}

// randomly initialize the centroids
vector<vector<double>> init_centroids(const vector<vector<double>> &data, int K)
{
    vector<vector<double>> centroids(K);
    for (int i = 0; i < K; i++)
    {
        int index = rand() % data.size();
        centroids[i] = data[index];
    }
    return centroids;
}

// assign each data point to its nearest centroid
vector<int> assign_clusters(const vector<vector<double>> &data, const vector<vector<double>> &centroids)
{
    vector<int> cluster_assignments(data.size());
    for (int i = 0; i < data.size(); i++)
    {
        double min_distance = numeric_limits<double>::max();
        for (int j = 0; j < centroids.size(); j++)
        {
            double distance = euclidean_distance(data[i], centroids[j]);
            if (distance < min_distance)
            {
                min_distance = distance;
                cluster_assignments[i] = j;
            }
        }
    }
    return cluster_assignments;
}

// compute the new centroids for each cluster
vector<vector<double>> compute_centroids(const vector<vector<double>> &data, const vector<int> &cluster_assignments, int K)
{
    vector<vector<double>> centroids(K, vector<double>(data[0].size()));
    vector<int> cluster_sizes(K, 0);
    for (int i = 0; i < data.size(); i++)
    {
        int cluster = cluster_assignments[i];
        for (int j = 0; j < data[i].size(); j++)
        {
            centroids[cluster][j] += data[i][j];
        }
        cluster_sizes[cluster]++;
    }
    for (int i = 0; i < K; i++)
    {
        for (int j = 0; j < centroids[i].size(); j++)
        {
            centroids[i][j] /= cluster_sizes[i];
        }
    }
    return centroids;
}

// perform the K-Means clustering algorithm
void kmeans_clustering(const vector<vector<double>> &data, int K)
{
    int tNum = 1; // default
    cout << "What test number is this? " << endl;
    cin >> tNum;
    // randomly initialize the centroids
    vector<vector<double>> centroids = init_centroids(data, K);

    // repeat until convergence
    bool converged = false;
    while (!converged)
    {
        // assign each data point to its nearest centroid
        vector<int> cluster_assignments = assign_clusters(data, centroids);

        // compute the new centroids for each cluster
        vector<vector<double>> new_centroids = compute_centroids(data, cluster_assignments, K);

        // check for convergence
        converged = true;
        for (int i = 0; i < centroids.size(); i++)
        {
            if (euclidean_distance(centroids[i], new_centroids[i]) > 0.001) // error constant
            {
                converged = false;
                break;
            }
        }

        // update the centroids
        centroids = new_centroids;
    }

    // plot the data points and the centroids
    // create the plot object
    Plot2D plot;
    plot.palette("rdgy");

    // add the data points
    std::vector<double> x(data.size()), y(data.size());
    for (int i = 0; i < data.size(); i++) {
        x[i] = data[i][0];
        y[i] = data[i][1];
    }
    plot.drawPoints(x, y).label("<- POINTS");
    cout << "The centroid coordinates are: " << endl;
    // add the centroids
    std::vector<double> cx(centroids.size()), cy(centroids.size());
    for (int i = 0; i < centroids.size(); i++) {
        cout << "Centroid #" << (i+1) << ": " << endl;
        cx[i] = centroids[i][0];
        cout << "X: " << centroids[i][0] << endl;
        cy[i] = centroids[i][1];
        cout << "Y: " << centroids[i][1] << endl;
    }
    plot.drawPoints(cx, cy).label("<- CENTROIDS");
    plot.legend()
        .atOutsideBottom()
        .fontSize(5)
        .displayHorizontal()
        //.displayExpandWidthBy(10)
        ;
    // show the plot
    Figure figure = {{plot}};
    string testb4 = "test";
    testb4 = testb4 + to_string(tNum);
    string testres = testb4 + ".svg";
    figure.title(testb4);
    figure.palette("dark2");
    Canvas canvas = {{figure}};
    canvas.show();
    canvas.save(testres);

    }
    int main()
    {
        int clusterNums = 1; // these three vars are defaults
        int pointCount = 0; 
        string fileName = "data.txt";
        
        cout << "How many clusters should there be? (Write below)" << endl;
        cin >> clusterNums;
        cout << "What's the name of the file we're using?" << endl;
        cin >> fileName;
        // read in the data points
        vector<vector<double>> data;
        ifstream file(fileName);
        double x, y;
        while (file >> x >> y)
        {
            // enable this if you want to see each and every point I added (your terminal will not survive)
            //cout << "Point to add: " << x << ", " << y << endl;
            pointCount++;
            data.push_back({x, y});
        }
        cout << "Running the algorithm with this many data points: " << pointCount << endl;
        // perform K-Means clustering with K = 3 for now.
        kmeans_clustering(data, clusterNums);
        return 0;
    }