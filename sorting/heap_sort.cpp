#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <functional>
#include <iterator>

using namespace std;

// heep array [1, 2, 3, 4, 5] (do not use index 0)
// left child = index*2
// right child = index*2+1
// parent = floor(index/2)

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

// top-down heapify
void max_heapify(vector<int> &v, int root, int length){
    int left_child = root*2;
    int right_child = root*2+1;
    int largest = root;
    if(left_child <= length && v[left_child] > v[largest]){
        largest = left_child;
    }
    if (right_child <= length && v[right_child] > v[largest]){
        largest = right_child;
    }
    
    if(largest != root){
        swap(&v[root], &v[largest]);
        max_heapify(v, largest, length);
    }
}

void build_max_heap(vector<int> &v){
    // build from first bottom root (index at size()/2)
    // do not bother i == 0 because of dumy 0 at index 0
    for(int i=(int)v.size()/2; i >= 1; i--){
        max_heapify(v, i, (int)v.size()-1);
    }
}

void heap_sort(vector<int> &v){
    v.insert(v.begin(), 0);  // do not use index 0
    build_max_heap(v);

    int size = (int)v.size()-1;
    for(int i=(int)v.size()-1; i >= 2; i--){
        swap(&v[i], &v[1]);
        size--;
        max_heapify(v, 1, size);
    }
    v.erase(v.begin());
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
    heap_sort(v);
    auto diff = chrono::steady_clock::now() - st;
    //////////////

    cout << "sorted: \n";
    copy(begin(v), end(v), ostream_iterator<int>(cout, " "));
    cout << endl;

    cout << chrono::duration <double, milli> (diff).count() << " ms" << endl;
}