#include<bits/stdc++.h>
using namespace std;

typedef struct{
    int parent_i, parent_j;
    double f, g, h;
} cell;

class pathPlanner{
    public:
        pathPlanner(int tam_row, int tam_col);
        void aStar(bool **mat, pair<int, int> &ori, pair<int, int> &dest, bool isYellow, int index);
        bool isValid(int row, int col);
        bool isUnblocked(bool **mat, int row, int col);
        bool isDestination(int row, int col, pair<int, int> &dest);
        double calculateHValue(int row, int col, pair<int, int> &dest);
        void tracePath(cell **cellDetails, pair<int, int> &dest, bool isYellow, int index);
        vector<pair<int, int>> getPath(bool isYellow, int index);

    private:
        int height;
        int weight;
        vector<pair<int, int>> cells;
        vector<pair<int, int>> path_vector;
        vector<vector<pair<int, int>>> aStar_blue;
        vector<vector<pair<int, int>>> aStar_yellow;
        bool havePath;
        bool **closedList;
        cell **cellDetails;
};
