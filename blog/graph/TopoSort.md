#拓扑排序 :smile: :smirk:

##定义
		在有向无环图(directed acycline graph) G=(V,E)中,生成一个访问序列,对于图中的任意弧i->j, 必有i在j之前被访问.

##算法
		拓扑排序主要有两种做法(其实本质是一样的).

###迭代做法
####过程描述
		0.根据G的顶点集合V和边集合E,构造出Indegree数组,`Indegree[i]表示顶点i的入度`.
		1.从Indegree[]中选出入度为0且未被访问过的顶点k,输出该顶点k,将顶点k标记为已访问顶点.
		2.将k所有的出边所关联的顶点的入度Indegree值都减1: 即若有k->p,则Indegree[p]--.
		3.不断的重复1,2过程,直到所有顶点都被输出.
		通过这个过程输出的前后顺序就是图G的拓扑排序.

####性能分析
		邻接矩阵存储的G: 时间复杂度为O(E*E),空间复杂度为O(E*E).
		邻接表存储的G: 时间复杂度为O(V+E),空间复杂度为O(E).

###递归DFS做法
		递归的DFS做法其实实质上和迭代做法是一样的,也是先构造出Indegree数组,数组初始方式于上面相同.

		1.从Indegree[]中选出入度为0且未被访问过的顶点k,然后以k为入口点进行DFS.
		2.在DFS中,首先输出当前访问的节点k,并且设置为已访问,
		  再将k所有出边想关联的点的入度Indegree值都减1,即若有k->p,则Indegree[o]--,
		  然后,选取k的相邻顶点中Indegree为0的顶点继续DFS.
		3.不断的重复1,2过程,直到所有顶点都被输出,则此输出前后顺序就是图G的拓扑排序.

```C++
// ****************** Topological sort  ****************************
//Topological sort using dfs. With the help of adjlist, time Complex is O(V + E)

//Method 1.
//Sosohu came up with this method, 
//	   which being found out is hard to search all topological sort using backtrack.
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

//Method 2:
//Another method with seems convient for search whole topoligcal sort.
void dfs_topo(int curr,vector<int> &path,vector<vector<int> > &res,
		vector<int> &visited,vector<int> &indegree){
	if(//we don't have node with 0 in-degree){
		res.push(curr);
		return ;
	}

	visited[curr] = true;
	for(int i=1;i<=vectorNum;i++){
		if(matrix[dest][i]->exist){
			indegree[i]--;
		}
	}

	for(int i=1;i<=vectorNum;i++){
		if(!visited[i] && !indegree[i]){
			dfs(i,path,res,visited,indegree);
		}
	}

	for(int i=1;i<=vectorNum;i++){
		if(matrix[dest][i]->exist){
			indegree[i]++;
		}
	}
}

vector<vector<int> > topoSort(){
	vector<bool> visited(vectorNum, false);
	vector<int> indegree(vectorNum, 0);
	vector<int> path;
	vector<vector<int> > res;

	//calculate in-degree
	for(int i=1;i<=vectorNum;i++){
		for(int j=1;j<=vectorNum;j++){
			if(matrix[i][j]->exist){
				indegree[j] ++;
			}
		}
	}

	for(int i=1;i<=vectorNum;i++){
		if(!indegree[i] && !visited[i]){
			dfs_topo(i,path,res,visited,indegree);
		}
	}
}


//topo sort    -----------------------------------------------
```

####Method 1与Method 2对比分析
		在Method 1中,每发现一个入度为0的点x,就处理其指向的某个顶点y,之后开始下次递归.
			在下次递归中,x指向的其它顶点的入度都不可能为0,因此不可能被访问到.

		在Method 2中,每发现一个入度为0的点x,处理其所指向的全部顶点y,之后开始下次递归.
			在下次递归中,x指向的顶点的入度都可能为0.

####性能分析
		邻接矩阵存储的G: 时间复杂度为O(E*E),空间复杂度为O(E*E).
		邻接表存储的G: 时间复杂度为O(V+E),空间复杂度为O(E).

##拓展
		一个有向图G=(V,E)是无环的,当且仅当对其进行DFS不产生回边.
		对一个有向图G=(V,E)进行拓扑排序,当完成时,若访问的节点少于|E|,则图中存在环.
