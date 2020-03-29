#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <functional>
#include <iterator>
#include <climits>

using namespace std;

void merge(vector<int> &v, int front, int mid, int end){
    // Constructs a container with as many elements as the range [first,last)
    // left_sub is a subarray of [v[front], ..., v[mid], MAX] and plus a maximum value
    // right_sub is a subarray of [v[mid+1], ..., v[end], MAX] and plus a maximum value
    vector<int> left_sub(v.begin()+front, v.begin()+mid+1);
    vector<int> right_sub(v.begin()+mid+1, v.begin()+end+1);
    left_sub.insert(left_sub.end(), INT_MAX);
    right_sub.insert(right_sub.end(), INT_MAX);

    int left_idx = 0;
    int right_idx = 0;

    for(int i = front; i <= end; i++){
        if(left_sub[left_idx]<=right_sub[right_idx]){
            v[i] = left_sub[left_idx];
            left_idx++;
        }
        else{
            v[i] = right_sub[right_idx];
            right_idx++;
        }
    }
}

void merge_sort(vector<int> &v, int front, int end){
    if(front < end){
        int mid = (end-front)/2 + front;  // prevent integar overflow
        merge_sort(v, front, mid);
        merge_sort(v, mid+1, end);
        merge(v, front, mid, end);
    }
}

int main(int argc, char* argv[]){
    // array size
    int n = 10000;
    vector<int> v(n);

    // random generator within [-10, +10] integar
    default_random_engine re(chrono::system_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> dist{-100, 100};

    // random array
    generate(begin(v), end(v), bind(dist, re));

    cout << "unsorted: \n";
    copy(begin(v), end(v), ostream_iterator<int>(cout, " "));
    cout << endl;

    //////////////
    // merge sort
    auto st = chrono::steady_clock::now();
    merge_sort(v, 0, v.size()-1);
    auto diff = chrono::steady_clock::now() - st;
    //////////////

    cout << "sorted: \n";
    copy(begin(v), end(v), ostream_iterator<int>(cout, " "));
    cout << endl;

    cout << chrono::duration <double, milli> (diff).count() << " ms" << endl;
}