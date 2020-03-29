#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <functional>
#include <iterator>
#include <climits>

using namespace std;

int get_max(vector<int> v){
    int max = INT_MIN;
    for(int i=0; i < v.size(); i++){
        if(v[i] > max)
            max = v[i];
    }
    return max;
}

void counting_sort_with_exp(vector<int> &v, int base, int min, int exp){
    vector<int> count(base);
    // count array
    for(int i=0; i<v.size(); i++){
        count[((v[i]-min)/exp)%base] += 1;
    }
    // accumulated count array
    for(int i=1; i<count.size(); i++){
        count[i] += count[i-1];
    }
    vector<int> output(v.size());
    // stable sorting needs iterate from last element
    for(int i=v.size()-1; i>=0; i--){
        //need additional -1 for output indexing
        output[count[((v[i]-min)/exp)%base] - 1] = v[i];
        count[((v[i]-min)/exp)%base]--;
    }
    v.swap(output);
}

void radix_sort(vector<int> &v, int min){
    int max = get_max(v)-min;
    // for 64-based integer
    int base = 64;
    for(int exp=1; max/exp>0; exp*=base){
        counting_sort_with_exp(v, base, min, exp);
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
    // counting sort
    auto st = chrono::steady_clock::now();
    // need to specify the range of data in array (range, minimum)
    int min = -100;
    radix_sort(v, min);
    auto diff = chrono::steady_clock::now() - st;
    //////////////

    cout << "sorted: \n";
    copy(begin(v), end(v), ostream_iterator<int>(cout, " "));
    cout << endl;

    cout << chrono::duration <double, milli> (diff).count() << " ms" << endl;
}