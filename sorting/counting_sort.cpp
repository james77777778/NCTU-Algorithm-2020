#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <functional>
#include <iterator>

using namespace std;

void counting_sort(vector<int> &v, int range, int min){
    vector<int> count(range);
    // count array
    for(int i=0; i<v.size(); i++){
        count[v[i]-min] += 1;
    }
    // accumulated count array
    for(int i=1; i<count.size(); i++){
        count[i] += count[i-1];
    }
    vector<int> output(v.size());
    // stable sorting needs iterate from last element
    for(int i=v.size()-1; i>=0; i--){
        //need additional -1 for output indexing
        output[count[v[i] - min] - 1] = v[i];
        count[v[i]-min]--;
    }
    v.swap(output);
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
    // counting sort
    auto st = chrono::steady_clock::now();
    // need to specify the range of data in array (range, minimum)
    int range = abs(-100) + 1 + abs(100);
    int min = -100;
    counting_sort(v, range, min);
    auto diff = chrono::steady_clock::now() - st;
    //////////////

    cout << "sorted: \n";
    copy(begin(v), end(v), ostream_iterator<int>(cout, " "));
    cout << endl;

    cout << chrono::duration <double, milli> (diff).count() << " ms" << endl;
}