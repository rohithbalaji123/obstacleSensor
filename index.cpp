#include <bits/stdc++.h>
#define dl double
#define vpdl vector < pair <double, double> >
#define pdd pair< double, double >

using namespace std;

/*Function to initialize coordinates for the sensors assuming bottom-left sensor as origin
    B-----C
    |     |
    |     |
    A-----D
    
    A => sensors[0]
    B => sensors[1]
    C => sensors[2]
    D => sensors[3]
*/
void fillCoordinates(vpdl &sensors, int n) {
    sensors.push_back(make_pair(0 ,0));
    sensors.push_back(make_pair(0 ,n));
    sensors.push_back(make_pair(n ,n));
    sensors.push_back(make_pair(n ,0));
}

dl distance(pdd c1, pdd c2) {
    dl x = c1.first - c2.first;
    dl y = c1.second - c2.second;
    return sqrt(x*x + y*y);
}

int findIntersection(pdd c1, pdd c2, dl r1, dl r2, pdd &i1, pdd &i2) {
    dl d = distance(c1, c2);
    if(d > r1+r2)
        return 0;
    
    dl a = (r1*r1 - r2*r2 + d*d)/(2.0 * d);
    dl h = sqrt(r1*r1 - a*a);
    
    pdd p = make_pair(c1.first+(a*(c2.first-c1.first))/d, c1.second+(a*(c2.second-c1.second))/d);
    
    i1 = make_pair(p.first+(h*(c2.second-c1.second)/d), p.second-(h*(c2.first-c1.first)/d));
    i2 = make_pair(p.first-(h*(c2.second-c1.second)/d), p.second+(h*(c2.first-c1.first)/d));
    
    if(d == r1+r2) {
        return 1;
    }
    return 2;
}

bool onCircle(pdd c, dl r, pdd p) {
    dl dist = distance(c, p);
    return dist == r;
}

pdd findObstacle(vpdl sensors, vector<dl> obstacleDistances) {
    pdd i1, i2;
    int number = findIntersection(sensors[0], sensors[1], obstacleDistances[0], obstacleDistances[1], i1, i2);
    
    if(number == 1) {
        return i1;
    }
    
    if(onCircle(sensors[2], obstacleDistances[2], i1)) {
        return i1;
    }
    return i2;
}

int main() {
    int n = 3; // nxn grid
    vpdl sensors;
    
    fillCoordinates(sensors, n);
    
    vector<dl> obstacleDistances;
    dl od[n] = {2.12132034356, 2.12132034356, 2.12132034356, 2.12132034356};
    
    for(int i=0; i<n; i++) {
        obstacleDistances.push_back(od[i]);
    }
    
    pdd obstacle = findObstacle(sensors, obstacleDistances);
    
    return 0;
}
