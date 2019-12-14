/***
 * Maracatronics Robotics
 * Federal University of Pernambuco (UFPE) at Recife
 * http://www.maracatronics.com/
 *
 * This file is part of Armorial project.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ***/

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
