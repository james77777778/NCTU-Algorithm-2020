#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <functional>
#include <iterator>
#include <stack>

using namespace std;

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(vector<int> &v, int front, int end){
    int pivot = v[end];
    int i = front-1;  // record the left array index
    for(int j = front; j < end; j++){
        if(v[j] < pivot){
            i++;
            swap(&v[i], &v[j]);
        }
    }
    i++;
    swap(&v[i], &v[end]);
    return i;
}

void iterative_quick_sort(vector<int> &v, int front, int end){
    vector<int> aux_stack(end-front+1);
    int top = -1;
    aux_stack[++top] = front;
    aux_stack[++top] = end;
    while(top>=0){
        // FILO
        end = aux_stack[top--];
        front = aux_stack[top--];
        int pivot = partition(v, front, end);
        // there has an unsorted array at the front of the pivot
        if(pivot-1 > front){
            aux_stack[++top] = front;
            aux_stack[++top] = pivot-1;
        }
        // there has an unsorted array at the end of the pivot
        if(pivot+1 < end){
            aux_stack[++top] = pivot+1;
            aux_stack[++top] = end;
        }
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
    // quick sort
    auto st = chrono::steady_clock::now();
    iterative_quick_sort(v, 0, v.size()-1);
    auto diff = chrono::steady_clock::now() - st;
    //////////////

    cout << "sorted: \n";
    copy(begin(v), end(v), ostream_iterator<int>(cout, " "));
    cout << endl;

    cout << chrono::duration <double, milli> (diff).count() << " ms" << endl;
}