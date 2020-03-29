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
    // selection sort
    auto st = chrono::steady_clock::now();
    int min_index;
    for(int i=0; i<v.size()-1; i++){
        min_index = i;
        // find minimum element
        for(int j=i+1; j<v.size(); j++){
            if(v[j]<v[min_index]){
                min_index = j;
            }
        }
        // swap found minimum element to the head of sorted array
        int temp = v[i];
        v[i] = v[min_index];
        v[min_index] = temp;
    }
    auto diff = chrono::steady_clock::now() - st;
    //////////////

    cout << "sorted: \n";
    copy(begin(v), end(v), ostream_iterator<int>(cout, " "));
    cout << endl;

    cout << chrono::duration <double, milli> (diff).count() << " ms" << endl;
}