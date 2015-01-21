#关键路径

##定义

实际情形:

工程中有很多项目,每个项目相当于图的一个顶点,项目之间有先后顺序相当于有向图的弧,而一个项目转移到另一个项目称为`活动`,每个活动需要花费一些时间,相当于图的边的权值,而且不相干的活动(边)可以同时进行.

		那么关键路径就是一系列的边,这些边的开工与否能够直接影响到整个工程的进度.

##算法

为了求关键路径上的这些边,可以对每条边w设定两个变量,分别是ee[w]和el[w]分别表示边w在不影响整个工程进度的条件下最早和最迟开工时间,如果ee[w] == el[w], 则w为关键路径.

那么如何求得ee[w]和el[w]呢? 假设w的两个端点分别是i和j,即w: i->j. 定义两个变量分别是ve[i],vl[i]表示在不影响整个工程进度情况下到达i的最早时间和最迟时间,同样有两个变量ve[j],vl[j].

那么ee[w] = ve[i],  el[w] = vl[j] - |w|.    |w|表示活动w的花费时间.

所以,问题变成了求ve和vl问题上了, 而对于顶点i,我们有:

ve[i] = max{ve[q], ...},      存在i->q的边,即ve[i]是所有i的出边相关联的顶点的ve值的最大值.

vl[i] = min{ve[p], ...},      存在p->i的边,即vl[i]是所有i的入边相关联的顶点的vl值的最小值.

仔细想想,还真是真么回事....

所以算法可以描述成如下:

1.	使用拓扑排序,将所有顶点排序好.
2.	ve[start] = 0, 然后根据拓扑排序的顺序访问对应顶点的ve值,并更新其出边关联顶点的ve值,直到所有顶点ve值都被确定下来.
3.	vl[end] = ve[end], 然后根据逆拓扑排序的书按需访问对应顶点的vl值,并更新其入边关联顶点的vl值,直到所有顶点vl值都被确定下来.
4.	根据ve和vl值确定ee和el值.
5.	根据ee和el值确定关键路径.

代码:
```C++
//criticalPath -----------------------------------------------
//assume that only one point without in diraction edge and one point without out diraction edge
//Time Complex O(V + E)
void criticalDfs(vector<vector<Node> > &data, vector<int> &order, 
				vector<int> &Indegree, int start){
	int index;
	order.push_back(start);
	for(int i = 0; i < data[start].size(); i++){
		index = data[start][i].index;
		Indegree[index]--;
		if(Indegree[index] == 0)
			criticalDfs(data, order, Indegree, index);
	}
}

vector<Edge> criticalPath(vector<vector<Node> > &data, int start, int end){
	int vecnum = data.size();
	// point eariest start time, lastest start time
	vector<int> ve(vecnum, INT_MIN), vl(vecnum, INT_MAX); 
	vector<int> order; // ianput by the topo sort order
	vector<int> Indegree(vecnum, 0);

	//topo sort
	for(int i =0; i < data.size(); i++){
		for(int j = 0; j < data[i].size(); j++){
			Indegree[data[i][j].index]++;
		}
	}
	criticalDfs(data, order, Indegree, start);
	//compute ve and vl
	ve[start] = 0;
	int index;
	for(int i = 0; i < vecnum - 1; i++){
		index = order[i];
		for(int j = 0; j < data[index].size(); j++){
			ve[data[index][j].index] = max(ve[data[index][j].index], 
										ve[index] + data[index][j].weight);
		}
	}
	vl[end] = ve[end]; // 因为最后一个节点vl与ve相等,同理开始节点vl与ve也相等.
	for(int i = vecnum - 2; i >= 0; i--){
		index = order[i];
		for(int j = 0; j < data[index].size(); j++){
			vl[index] = min(vl[index], vl[data[index][j].index] - data[index][j].weight);
		}
	}

	//compute ee and el
	vector<Edge> ret;
	for(int i = 0; i < vecnum; i++){
		for(int j = 0; j < data[i].size(); j++){
			int index = data[i][j].index;
			// ee[k] == el[k], k is the edge of i -> index
			if(ve[i] == vl[index] - data[i][j].weight){
				ret.push_back(Edge(i, index, data[i][j].weight));
			}
		}
	}
	return ret;
}
//criticalPath -----------------------------------------------
```
时间复杂度O(V + E)
