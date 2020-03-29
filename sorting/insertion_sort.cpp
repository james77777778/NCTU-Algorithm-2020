#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <functional>
#include <iterator>

using namespace std;

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
    // insertion sort
    auto st = chrono::steady_clock::now();
    int key, j;
    for(int i=1; i<v.size(); i++){
        key = v[i];
        j = i-1;  // compare from last unsorted array
        while(key < v[j] && j >= 0){
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = key;
    }
    auto diff = chrono::steady_clock::now() - st;
    //////////////

    cout << "sorted: \n";
    copy(begin(v), end(v), ostream_iterator<int>(cout, " "));
    cout << endl;

    cout << chrono::duration <double, milli> (diff).count() << " ms" << endl;
}