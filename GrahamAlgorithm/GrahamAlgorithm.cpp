// GrahamAlgorithm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <chrono>
#include <vector>

#include <algorithm>
#include "randomNumbers.h"
using namespace std::chrono;

struct point {
	float x;
	float y;
};

class ga {
public:
    std::vector<point> _points;
    int _howManyPoints = 0;
public:
    ga() {};
    ga(int howManyPoints) {
        _howManyPoints = howManyPoints;
        _points.resize(howManyPoints);
    };

    int findRotation(point p1, point p2, point p3) {
        double ar = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
        if (ar < 0) return 1; //Clockwise
        if (ar > 0) return -1; //CounterClockWise
        return 0; //Collinear
    };

    // sqr dist
    double furtherAway(point p1, point p2) {
        return (p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y);
    };

    std::vector<point> generatePoints() {
        for (int i = 0; i < _howManyPoints; ++i) {
            _points[i].x = randomFloat();
            _points[i].y = randomFloat();
        };
        return _points;
    };

    int findLowest() {
        point lowestPoint = _points[0];
        int min = 0;
        for (int i = 1; i < _points.size(); ++i) {
            if (_points[i].y < lowestPoint.y || (_points[i].y == lowestPoint.y &&
                _points[i].x < lowestPoint.x)) {
                lowestPoint = _points[i];
                min = i;
            };
        };
        return min;
    };

    std::vector<point> sortPoints(int idx) {
        std::swap(_points[0], _points[idx]);
        point p0 = _points[0];
        std::sort(_points.begin() + 1, _points.end(),
            [&](const point& a, const point& b) {
                int cw = findRotation(p0, a, b);
        if (cw == -1) return true;
        if (cw == 0 && furtherAway(p0, a) < furtherAway(p0, b)) return true;
        return false;
            });
        return _points;
    }

    void printAllPoints() {
        for (point point : _points) {
            std::cout << point.x << ",";
        }
        std::cout << "\n";
        for (point point : _points) {
            std::cout << point.y << ",";
        }
        std::cout << "\ndone printing all points\n";
    };
    std::vector<point> convexHull() {
        if (_howManyPoints <= 3)
            return {};
        int idx = findLowest();
        sortPoints(idx);
        std::vector<point> convexHull_;
        convexHull_.push_back(_points[0]);
        convexHull_.push_back(_points[1]);
        convexHull_.push_back(_points[2]);
        for (int i = 3; i < _points.size(); i++) {
            auto ps = convexHull_.size();
            while (convexHull_.size() > 2 && findRotation(convexHull_[(ps-2)],
                convexHull_[(ps-1)], _points[i]) != -1) {
                convexHull_.pop_back();
                ps = convexHull_.size();
            };
            convexHull_.push_back(_points[i]);
        }
        convexHull_.push_back(_points[0]);
        return convexHull_;
    };
};

void printHull(std::vector<point>& hull) {
    for (point point : hull) {
        std::cout  << point.x << ",";
    }
    std::cout << "\n";
    for (point point : hull) {
        std::cout << point.y << ",";
    }
    std::cout << "\ndone .. \n";
};
int main() {
    ga ga(50);
    auto start = steady_clock::now();
    ga.generatePoints();
    std::cout << "\n";
    std::vector<point> hull = ga.convexHull();
    std::cout << "printing hull .. " << "\n";
    ga.printAllPoints();

    printHull(hull);
    auto stop = steady_clock::now();
    std::cout << "It took " << duration_cast<milliseconds>(stop - start).count() << " miliseconds";
    getchar();
}