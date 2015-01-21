<script type="text/javascript" src="http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=default"></script>
#最小生成树

##定义
`生成树`: 

	设图G有vecnum个顶点,在图G中找到vecnum-1条边,使得这个vecnum个顶点连成一个连通分量,则这个
	连通分量就是生成树.

`最小生成树`:

	图G找到一颗生成树,并且要求这颗生成树的边权值之和最小.

##算法
最小生成树的算法有两个,分别是Prim算法和Kruskal算法.
###Prim算法
首先要设定边的权值都是大于0,若存在小于0的,可以边权值同时加上最小值变成正数.

设图G的顶点集合为V,边集合为E,已选顶点集合为H.

H初始为v0, V = V - H.

1.	从V中选出到H中任意点距离最近的点v,并且输出该最近的距离和两端节点.
2. 	将v加入到H中,并将v从V中删除,根据v更新V中点到H的距离.
3.	不断的重复1,2直到V为空集.

代码如下:
```C++
// Prim  -----------------------------------------------------
// assume that all the path value is greater than 0
// Time Complex O(VlgV)
int MinSpanTree_Prim(vector<vector<int> > &data){
	int n = data.size();
	if(n <= 0)  return 0;
    vector<int> closeEdge(n, 0);
    // 初始化closeEdge函数
    for(int i = 1; i < n; i++){
        closeEdge[i] = data[0][i];
    }
    int sum = 0, count = 1, min = 0, index = 0;
    while(count++ < n){
        min = INT_MAX;
        for(int i = 0; i < n; i++){
            if(closeEdge[i] != 0 && min > closeEdge[i]){
                index = i;
                min = closeEdge[i];
            }
        }
        sum = sum + min;
	        closeEdge[index] = 0; // 不用再被找
        for(int i = 0; i < n; i++){
            if(closeEdge[i] != 0 && data[index][i] < closeEdge[i])
                closeEdge[i] = data[index][i];
        }
    }
    return sum;
}
// Prim  -----------------------------------------------------
```
时间复杂度O(V^2)


###Kruskal算法
Prim算法主要适用与稠密图,而Kruskal算法主要适用与稀疏图.

Kruskal算法的大意是这样的:

设图G中顶点集合为V,边的集合为E,已选边集合为C(初始为空集).

1.	将E中的所有边放入到一个最小堆H里面.
2.  	从H中pop出最小的边,然后检测此边是否与已选出的边构成环,若是则舍弃此边,若不是将此边加入到C.
3.	不断的重复2,知道有|V| - 1条边被选出.

这里有一个问题需要注意,就是如何判定当前要选择的边与已选择的边构成环,只需要当前选择的边的两个顶点在已选择的边构成的子图中是否是输入同一个连通分量,如果是则与新选边构成环,如果不是则不会.

代码如下:
```C++
//kruskal ----------------------------------------------------
// Time Complex O(ElgE)
bool EdgeCmp(const Edge& a, const Edge& b){
    return a.w < b.w;
}

int root(int x, vector<Edge> &edges, vector<int> &father){
    if(x != father[x])
        father[x] = root(father[x], edges, father);   // 这点非常重要,能够减少很多时间
    return father[x];
}


bool join(int x, int y, vector<Edge> &edges, vector<int> &father){
    int rx = root(x, edges, father);
    int ry = root(y, edges, father);
    if(rx == ry)    return false;
    else{
        father[rx] = ry;
        return true;
    }
}


int MinSpanTree_Kruskal(vector<vector<Node> > &data){ // data是了邻接表
	vector<Edge> edges;
	for(int i = 0; i < data.size(); i++){
		for(int j = 0; j < data[i].size(); i++){
			edges.push_back(Edge(i, data[i][j].index, data[i][j].weight));
		}
	}
	sort(edges.begin(), edges.end(), EdgeCmp);
	vector<int> father(data.size(), 0);  // 表明父节点
	for(int i = 0; i < data.size(); i++){
        father[i] = i;
    }
	int vecnum = data.size(), arcnum = edges.size();
	int count = 0;
    int sum = 0;
    for(int i = 0; i < arcnum && count < vecnum - 1; i++){
        if(join(edges[i].s, edges[i].e, edges, father)){
            sum = sum + edges[i].w;
            count++;
        }
    }
    return sum;
}
//kruskal ----------------------------------------------------
```
时间复杂度为O(ElgE).
