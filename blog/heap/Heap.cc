#include <cstdio>
#include <vector>
using namespace std;

struct Cmp {
    bool operator() (const int &a, const int &b) { return a < b; }
};

template<typename Comp>
class Heap {
public:
    void sort_heap() {
        while(!h.empty()) {
            printf("%d\n", h[0]);
            pop_heap();
        }
    }
    void pop_heap () {
        if(h.empty()) return;
        swap(h[0], h[h.size() - 1]);
        h.pop_back();
        heap_adjust(0);
    }
    void push_heap(int v) {
        h.push_back(v);
        int index = h.size() - 1;
        int tmp = h[index];
        for(int i = (index - 1) >> 1; i >= 0; i = (i - 1) >> 1)
            if(!cmp(tmp, h[i])) break;
            else { h[index] = h[i]; index = i; }
        h[index] = tmp;
    }
    void make_heap() {
        int k = (h.size() - 2) >> 1;
        for(int i = k; i >= 0; i--)
            heap_adjust(i);
    }
    int top() {
        if(!h.empty())
            return h[0];
    }
private:
    vector<int> h;
    Comp cmp;
    void inline heap_adjust(int index) {
        int n = h.size() - 1;
        int tmp = h[index];

        for(int i = 2 * index + 1; i <= n; i = i * 2 + 1) {
            if(i < n && !cmp(h[i], h[i + 1])) i++;
            if(cmp(tmp, h[i])) break;
            h[index] = h[i]; index = i;
        }
        h[index] = tmp;
    }
};
int main(int argc, char *argv[]) {
    Heap<Cmp> h;
    h.pop_heap();
    h.push_heap(5);
    h.push_heap(3);
    h.pop_heap();
    h.push_heap(1);
    h.push_heap(4);
    h.push_heap(2);
    h.sort_heap();
    return 0;
}
