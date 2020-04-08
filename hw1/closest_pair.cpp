#include <iostream>
#include <iomanip>
#include <climits>
#include <cmath>
using namespace std;
 
struct Point {double x, y;};
 
// sort by x coordinate
inline int compare_x(const void* a, const void* b)
{
    Point *p1 = (Point *)a, *p2 = (Point *)b;
    return (p1->x - p2->x);
}

// sort by y coordinate
inline int compare_y(const void* a, const void* b)
{
    Point *p1 = (Point *)a, *p2 = (Point *)b;
    return (p1->y - p2->y);
}
 
// compute the euclidean distance without square root between two points
inline double dist_nosqrt(Point p1, Point p2)
{
    return (p1.x - p2.x)*(p1.x - p2.x)+(p1.y - p2.y)*(p1.y - p2.y);
}
 
double brute_force(Point P[], int n)
{
    // sqrt(20000^2+20000^2) = 89442
    double min = INFINITY;
    for (int i = 0; i < n; ++i)
        for (int j = i+1; j < n; ++j) {
            double d = dist_nosqrt(P[i], P[j]);
            if (d < min)
                min = d;
        }
    return min;
}
 
// returns minimum of two values
inline double min(double x, double y)
{
    return (x < y)? x : y;
}
 
 
// find the distance beween the closest points of
// strip of given size. All points in strip[] are sorted by y. 
double strip_points(Point strip[], int size, double d)
{
    double min = d;  // Initialize the minimum distance as d
    qsort(strip, size, sizeof(Point), compare_y);

    // Pick all points one by one and try the next points 
    // till the difference between y's is smaller than d.
    for (int i = 0; i < size; ++i)
        for (int j = i+1; j < size && (strip[j].y - strip[i].y) < min; ++j) {
            double d = dist_nosqrt(strip[i], strip[j]);
            if (d < min)
                min = d;
        }
    return min;
}
 
// find the smallest distance recursively. 
// All point in array P are sorted by x
double closest(Point P[], Point strip[], int n)
{
    // use brute force when there are not enough points
    if (n <= 50)
        return brute_force(P, n);
 
    // mid point
    int mid = n/2;
    Point midPoint = P[mid];
 
    // calculate the smallest distance 
    // dl: left of mid point 
    // dr: right side of the mid point
    double dl = closest(P, strip, mid);
    double dr = closest(P + mid, strip, n-mid);
    double dmin = min(dl, dr);
 
    int j = 0;
    for (int i = 0; i < n; i++)
        if (fabs(P[i].x - midPoint.x) < dmin)
            strip[j++] = P[i];
 
    double dmin_strip = strip_points(strip, j, dmin);
    double final_dmin = dmin;
    if(dmin_strip < dmin)
		final_dmin = dmin_strip;
    return final_dmin;
}
 
int main()
{
    // the number of test cases
    int num_t;
    cin >> num_t;
    for (int t=0; t<num_t; t++) {
        // the number of points
        int num_p;
        cin >> num_p;
        Point P[num_p];
        
        // input points
        for (int p=0; p<num_p; p++) {
            cin >> P[p].x >> P[p].y;
        }
        
        // begin closest pairs algorithm
        int n = sizeof(P) / sizeof(P[0]);
        qsort(P, n, sizeof(Point), compare_x);

        // array to store points in a strip
        Point *strip = new Point[n];

        // get the distance and pair of points
        double final_dmin = closest(P, strip, n);
        cout << fixed << setprecision(6) << sqrtl(final_dmin) << endl;
    }
    return 0;
}