#include <queue>
#include <vector>
#include <cstdio>

using namespace std;

const int INF = 0x4fffffff;
typedef pair<int, int> PII;

class Solution {
public:
    void dijkstra(vector<vector<PII> > &edge, int s, int t) {
        vector<int> dad(edge.size(), -1);
        vector<int> dist(edge.size(), INF);
        priority_queue<PII, vector<PII>, greater<PII> > pqueue;

        dist[s] = 0;
        pqueue.push(make_pair(0, s));
        while(!pqueue.empty()) {
            PII curr = pqueue.top();
            if(curr.second == t) break;
            pqueue.pop();
            int midv = curr.second; /* curr vertex */
            for(vector<PII>::iterator it = edge[midv].begin(); it != edge[midv].end(); it++)
                if(dist[midv] + it->first < dist[it->second]) { /* pass curr */
                    dist[it->second] = dist[midv] + it->first;
                    pqueue.push(make_pair(dist[it->second], it->second));
                    dad[it->second] = midv; /* record path */
                }
        }

        printf("\n%d -> %d : %d\n", s, t, dist[t]);
        printPath(dad, dist, s, t);
        printf("\n");
    }
private:
    void printPath(vector<int> &dad, vector<int> &dist, int s, int t) {
        if(-1 == t || dist[t] >= INF) return;
        printPath(dad, dist, s, dad[t]);
        printf("%d ", t);
    }
};

int main(int argc, char *argv[]) {
    int n;
    int m;
    int s;
    int t;
    int vertex;
    int distance;

    #ifdef DEBUG
    freopen("input", "r", stdin);
    #endif

    scanf("%d %d %d", &n, &s, &t);
    vector<vector<PII> > edge(n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &m);
        for(int j = 0; j < m; j++) {
            scanf("%d %d", &vertex, &distance);
            edge[i].push_back(make_pair(distance, vertex));
        }
    }

    (new Solution)->dijkstra(edge, s, t);

    return 0;
}
