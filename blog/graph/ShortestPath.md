#最短距离问题 :smirk:

##单源最短距离

###定义

	图G=(V,E)中顶点v到其他任意顶点的最短距离.

###算法 

####DAG上的单源最短路径

	在DAG图上求某个节点x作为源点的最短路径时,可以先计算出整个图的拓扑排序.在节点x之前的顶点都是无法从x开始可达的.
	
	1.计算图的拓扑序列.
	2.按照拓扑序列,对每个顶点的邻接节点(拓扑序中,一定位于它的后面)做收缩操作.

####Dijstra算法

	Dijstra可以处理图中存在回路,但是没有负边权的单元最短路径问题.
	设图G的顶点集合为V,已选顶点集合为H,单源点为v,各顶点到v的距离为Dist[]

	初始: V = V - {v}, H = {v}, 若存在顶点i到v的边,则Dist[i] = W(i,v), 否则为INT_MAX;

	1. 	从V中根据Dist数组选取距离v最近的顶点p,将p加入H,并从V中删除.
	2.	使用p更新Dist[i]数组,Dist[i] = min(Dist[i], Dist[p] + W[p, i]).
	3.	不断重复1,2直到V为空集,最终Dist[i]就是v到i的最短距离.

	上面算法你也可以在更新的时候保存路径,这样就不仅仅可以求出最短距离还可以求出最短距离相应的路径.
	(可以记录每个每个节点的前驱节点,这样在做完一次Dijistra调整后,可以反推处任意点的最短路径)

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

####注意
	已经被访问过的节点(某次循环中,具有最小值),不会被再次访问.

####Bellman-Ford算法
对于图中存在负边权的问题,Dijkstra就无计可施了,此时Bellman-Ford算法就大显身手了:smirk:

####算法描述
	1. 对图G中所有的边进行Relax操作:
		若图中存在某条边e,其边权值为l,并且左端点距离目标节点的距离为x,右端点距离目标节点的距离为y,
		若x + l < y,则将右边端点距离目标节点的距离更新为x + l.
	2. 重复1操作,进行|V| -1次.
	3. 查看图中任意边,若Relax操作仍然能在边上产生操作(x + l < y),则可以断定图中存在负权值的边.

	Bellman-Ford在发现图中存在负权值的边时,会输出提示信息;
		对于不存在负权值的边的图,则可以确定其最短路径信息.

####简单说明
为什么要做|V|-1次全图Relax操作?

对于图中任一的顶点,其到达目标顶点的路径上最多间隔|V|-1个边,<img src="http://www.forkosh.com/mathtex.cgi?  F=\{v_i_1, v_i_2, ... , v_i_l \}">.
每次Relax操作,都能帮助更多的顶点取得最短路径(设想退化为单链表的情况). 则,只需要等先前的每个顶点都计算出最短路径时,本节点的最短路径也就自然获得.

####代码
```C++

void bellman_ford(int dest,vector<int> &minDis){
	for(int i=1;i<=vertexNum;i++){
		minDis[i] = INT_MAX;
	}
	minDis[dest] = 0;

	for(int i=1;i<edgeNum;i++){
		for(int i=1;i<=vertexNum;i++){
			for(int j=1;j<=vertexNum;j++){
				if(matrix[i][j]->exist && matrix[i][j]->weight + nodeWeight[i] < nodeWeight[j]){
					nodeWeight[j] = matrix[i][j]->weight + nodeWeight[i];
				}else if(matrix[i][j]->exist && matrix[i][j]->weight + nodeWeight[j] < nodeWeight[i]){
					nodeWeight[i] = matrix[i][j]->weight + nodeWeight[j];
				}
			}
		}
	}

	for(int i=1;i<=vertexNum;i++){
		for(int j=1;j<=vertexNum;j++){
			if(matrix[i][j]->exist && (matrix[i][j]->weight + nodeWeight[i] < nodeWeight[j]) 
					|| (matrix[i][j]->weight + nodeWeight[j] < nodeWeight[i])){
				return  false;
			}
		}
	}

	return true;
}
```

####SPFA算法
	
	SPFA算法就是使用队列来优化Bellman-Ford的松弛过程.因为有效的松弛操作必定发生已经松弛成功的顶点.
	所以可以用一个队列来记录已经松弛的顶点,每次都使用队列中的点来进行松弛操作.

	1.设置dis数组来表征各个点到源节点的最短路径,初始为INT_MAX;设置visited数组,表征各个节点是否在队列中;
	2.从源节点开始访问,如果其某个邻接的节点收到松弛操作的影响(x > y + l),
		且这个节点还不在队列中,就把它压入队列,否则,直接更新位于队里中的这个节点的值.
	3.重复进行2操作,直到队列为空.
		

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
