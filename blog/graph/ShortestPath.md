#最短距离问题

##单源最短距离

###定义

	图G中顶点v到其他任意顶点的最短距离.

###算法

单源最短距离主要算法有三个:`Dijstra`, `Bellman-Ford`和`SPFA`算法.

####Dijstra算法

设图G的顶点集合为V,已选顶点集合为H,单源点为v,各顶点到v的距离为Dist[]

初始: V = V - {v}, H = {v}, 若存在顶点i到v的边,则Dist[i] = W(i,v), 否则为INT_MAX;

1. 	从V中根据Dist数组选取距离v最近的顶点p,将p加入H,并从V中删除.
2.	使用p更新Dist[i]数组,Dist[i] = min(Dist[i], Dist[p] + W[p, i]).
3.	不断重复1,2直到V为空集,最终Dist[i]就是v到i的最短距离.

上面算法你也可以在更新的时候保存路径,这样就不仅仅可以求出最短距离还可以求出最短距离相应的路径.

代码:
```C++
struct Node{
	int index;
	int weight;
	Node(int index = 0, int weight = 0):index(index),weight(weight){}
};

int findMin(vector<int> &cost, vector<bool> &visited){
	int min = INT_MAX;
	int pos = -1;
	for(int i = 0; i < cost.size(); i++){
		if(!visited[i] && min > cost[i]){
			min = cost[i];
			pos = i;
		}
	}
	return pos;
}

int minPath(vector<vector<Node> > &data, int S, int  T){
	int vecnum = data.size();
	vector<int> cost(vecnum, INT_MAX);
	vector<bool> visited(vecnum, false);
	visited[S] = true;
	for(int i = 0; i < data[S].size(); i++){
		cost[data[S][i].index] = min(cost[data[S][i].index],data[S][i].weight);
	}
	int count = 0;

	while(count++ < vecnum - 1){
		int cur = findMin(cost, visited);
		if(cur == T)	return cost[cur];
		visited[cur] = true;
		for(int i = 0; i < data[cur].size(); i++){
			int index = data[cur][i].index;
			if(!visited[index] && cost[cur] + data[cur][i].weight < cost[index]){
				cost[index] = cost[cur] + data[cur][i].weight;
			}
		}	
	}
}
```

时间复杂度O(V^2).

####Bellman-Ford算法


####SPFA算法


##多源最短距离

上面讨论的是求出图G中每个顶点到指定的某个顶点的最短距离,下面我们要求求出图中任意两点之间的最短距离.

当然,你一开始会想到调用O(V)次Dijstra求出各顶点的单源最短距离不就得了,这种方法的时间复杂度是O(V^3),似乎也是可以的,但是我们将要介绍一个同为O(V^3)时间复杂度的但是更好一些的算法.

###Floyd多源最短距离算法

我们可以想象一下,求顶点i到j的最短距离,这个最短的路径中所包含的中间节点的标号最大值设为k,那么这个k属于[1~V],我们知道,k有可能为V也有可能小于V,那么这个最短路径是不是在过V点与不过V点取较小值?

我们设D(V)[i,j]表示i到j的最短距离，其中V表示，可以最短路径的最大标号可以为V.

那么D(V)[i,j] = min(D(V-1)[i,j], D(V-1)[i, V] + D(V-1)[V, j])

所以，可以看出来是一个动态规划问题，初始DO就是图G的邻接矩阵.

代码：
```C++
int FloydAdd(int a, int b){
	if(a == INT_MAX || b == INT_MAX)	return INT_MAX;
	return a+b;
}

vector<vector<int> > floyd(vector<vector<int> > &data){
	vector<vector<int> > DO = data;
	vector<vector<int> > DN = data;
	int vecnum = data.size();
	int count = 0;
	while(count < vecnum){
		for(int i = 0; i < vecnum - 1; i++){
			for(int j = i + 1; j < vecnum; j++){
				DN[i][j] = min(DO[i][j], FloydAdd(DO[i][count], DO[count][j]));
				DN[j][i] = DN[i][j];
			}
		}
		DO = DN;
		count++;
	}
	return DN;
}
```
时间复杂度O(V^3)
