#拓扑排序

##定义

		有向无环图G中,生成一个访问的顺序,使得任意弧i->j, 有i在j之前被访问.

##算法

拓扑排序主要有两种做法(其实本质是一样的).

###迭代做法

所谓迭代的做法很简单,就是首先根据G的顶点集合V和边集合E,构造出Indegree[]数组,`Indegree[i]表示顶点i的入度`.

1.	从Indegree[]中选出入度为0且未被访问过的顶点k,输出该顶点k,设置该顶点k为已访问顶点.
2.	将k所有的出边所关联的顶点的入度Indegree值都减1,即若有k->p,则Indegree[p]--.
3.	不断的重复1,2过程,直到所有顶点都被输出,则此输出前后顺序就是图G的拓扑排序.

此算法比较简单,在数据结构书中有现成代码,时间复杂度是同DFS的时间复杂度.

###递归DFS做法

递归的DFS做法其实实质上和迭代做法是一样的,也是先构造出Indegree数组,数组初始方式于上面相同.

1.	从Indegree[]中选出入度为0且未被访问过的顶点k,然后以k为入口点进行DFS.
2.	在DFS中,首先输出当前访问的节点k,并且设置为已访问,再将k所有出边想关联的点的入度Indegree值都减1,即若有k->p,则Indegree[o]--,然后,选取k的相邻顶点中Indegree为0的顶点继续DFS.
3.	不断的重复1,2过程,直到所有顶点都被输出,则此输出前后顺序就是图G的拓扑排序.

代码:
```C++
//topo sort    -----------------------------------------------
//使用dfs方式进行topo排序
//Time Complex O(V + E)
void topoDfs(vector<vector<Node> > &data, vector<int> &inDegree,
			 vector<bool> &visited, vector<int> &ret, int v){
	ret.push_back(v);
	visited[v] = true;
	for(int i = 0; i < data[v].size(); i++){
		inDegree[data[v][i].index]--;
		if(inDegree[data[v][i].index] == 0){
			topoDfs(data, inDegree, visited, ret, data[v][i].index);
		}
	}
}

vector<int> topoSort(vector<vector<Node> > &data){
	int vecnum = data.size();
	vector<int> inDegree(vecnum, 0);
	vector<bool> visited(vecnum, false);
	vector<int> ret;

	//compute in degree
	for(int i = 0; i < vecnum; i++){
		for(int j = 0; j < data[i].size(); j++){
			inDegree[data[i][j].index]++;
		}
	}
	//dfs
	int count = 0;
	for(int i = 0; i < vecnum; i++){
		if(!visited[i] && inDegree[i] == 0){
			topoDfs(data, inDegree, visited, ret, i);
		}
	}
	return ret;
}
//topo sort    -----------------------------------------------
```

算法时间复杂度为O(V + E)
