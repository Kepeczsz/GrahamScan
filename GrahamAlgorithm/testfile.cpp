// GrahamAlgorithm.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <random>
using namespace std::chrono;

float randomFloat() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(1, 15);

    return dist(gen);
}
class GrahamAlgorithm {
public:
    struct Point {
        float x, y;
        Point(float _x, float _y) : x(_x), y(_y) {}
        Point() : x(0), y(0) {};

        bool operator > (Point p) {    //Lowest Y
            if (y != p.y) { return y < p.y; }
            return x < p.x;
        };
    };
    std::vector<Point> Points_;
    std::vector<Point> convexHull_;
    Point pivotPoint_;
    int howManyPoints_;

public:
    std::vector<Point> generatePoints() {
        for (int i = 0; i < howManyPoints_; i++) {
            Points_[i] = (Point(randomFloat(), randomFloat()));
        }
        return Points_;
    };
    double furtherAway(Point p1, Point p2) {
        return (p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y);
    };
    int findRotation(Point p1, Point p2, Point p3) {
        double ar = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
        if (ar < 0) return 1; //Clockwise
        if (ar > 0) return -1; //CounterClockWise
        return 0; //Collinear
    };

    GrahamAlgorithm(int howManyPoints) {
        howManyPoints_ = howManyPoints;
        this->Points_.resize(howManyPoints_);
    };
    bool compareToPivotPoint(const Point& p1, const Point& p2, const Point& pivotPoint)
    {
        int returned = findRotation(pivotPoint, p1, p2);
        if (returned == 0)
        {
            return furtherAway(pivotPoint, p1) < furtherAway(pivotPoint, p2);
        }
        else
        {
            return returned == -1;
        }
    };
    
    std::vector<Point> convexHull() {
        if (howManyPoints_ < 2)
            return {};

        // set up minimal value at the start of vector of points
       

        // sort points in ascending order looking at pivotPoint
        
       
        //cout << "\nNajnizszy lewy dolny: " << endl;
        //cout << "(" << p0.x << ", " << p0.y << ")" << endl;
       


        convexHull_.push_back(Points_[0]);
        convexHull_.push_back(Points_[1]);
        convexHull_.push_back(Points_[2]);
        for (int i = convexHull_.size(); i < Points_.size(); i++) {
            auto ps = convexHull_.size();
            while (convexHull_.size() > 1 && findRotation(convexHull_[ps - 2], convexHull_[ps - 1], Points_[i]) != -1) {
                convexHull_.pop_back();
                ps = convexHull_.size();
            };
            convexHull_.push_back(Points_[i]);
        };
        return convexHull_;
    }

    int findLowestPoint() {
        int idx = 0;
        Point lowest = Points_[0];
        for (int i = 1; i < Points_.size(); i++) {
            if (Points_[i].y < lowest.y || (Points_[i].y == lowest.y && Points_[i].x < lowest.x)) {
                lowest = Points_[i];
                idx = i;
            }
        }
        int minValue = findLowestPoint();
        std::swap(Points_[0], Points_[minValue]);
        return idx;
    };
    void printPoints() {
        for (Point points : Points_) {
            std::cout << points.x << ",";
        }
        std::cout << "\nEnd of x coordinates" << "\n";
        for (Point points : Points_) {
            std::cout << points.y << ",";
        }
        std::cout << "\nEnd of y coordinates" << "\n";
    };

    void printConvexHull() {
        for (Point points : convexHull_) {
            std::cout << points.x << ",";
        }
        std::cout << "\nEnd of x coordinates" << "\n";
        for (Point points : convexHull_) {
            std::cout << points.y << ",";
        }
        std::cout << "\nEnd of y coordinates" << "\n";
    };
};


int main()
{
    GrahamAlgorithm graham(10);

    auto start = high_resolution_clock::now();
    graham.generatePoints();
    graham.pivotPoint_ = graham.Points_[0];
    std::sort(graham.Points_.begin(), graham.Points_.end(), &GrahamAlgorithm::compareToPivotPoint);
    graham.convexHull();
    graham.printConvexHull();

    graham.printPoints();
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(stop - start);

    std::cout << "Time taken by function: "
        << duration.count() << " miliseconds" << std::endl;
    getchar();
}
