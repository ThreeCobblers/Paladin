#关节点

##定义

	顶点v是关节点当且仅当,在图G中去掉v及其相关联的边之后,图的某个连通分量分裂成两个或者更多个
	连通分量.

##算法

首先,我们定义两种边:

*	树边: DFS过程中使用的边称为树边,即深度优先搜索树树边.
*	回边: 图G中除了树边之外的其他边.

然后,我们可以看到一个节点是关节点,则有且仅有以下两种情况.

*	节点是DFS搜索森林的某个根节点,如果它有多于一个深度优先搜索树孩子,则该节点必是关节点.
*	节点不是根节点,但是节点的某个深度优先搜索子树中没有连到此节点祖先的回边.

根据这个两条,我们可以定义两个数组visited[]和low[],visited[i]是DFS过程中被遍历的序号,而
low[]使用下面规则产生:

	low[i] = min{visited[i], low[w], visited[p]}, 
	其中w是i的孩子,p是i的回边连接的祖先节点.

如果节点i存在某个孩子使得 visited[i] <= low[w], 那么i必为关节点,或者若i是根节点,有多于一个孩子也为关节点.

产生visited和low数组伴随这DFS的过程.

代码:
```C++
//joint search -----------------------------------------------
// Time Complex O(V + E)
void jointDfs(vector<vector<Node> > &data, vector<int> &visited, vector<int> &low,
			 vector<int> &ret, int v, int &count, bool isRoot = false){
	visited[v] = count++;
	Node cur;
	int sons = 0;
	int l = visited[v];
	for(int i = 0; i < data[v].size(); i++){
		cur = data[v][i];
		if(visited[cur.index] == INT_MAX){
			sons++;
			jointDfs(data, visited, low, ret, cur.index, count);
			if(visited[v] <= low[cur.index] && !isRoot)	ret.push_back(v);
			l = min(low[cur.index], l);
		}else{
			l = min(visited[cur.index], l);
		}
	}
	low[v] = l;
	if(isRoot && sons > 1){
		ret.push_back(v);
	}
}

vector<int> jointPointSearch(vector<vector<Node> > &data){
	int vecnum = data.size();
	vector<int> visited(vecnum, INT_MAX);  // visited array
	vector<int> low(vecnum, INT_MAX);     // low array
	vector<int> ret;
	int count = 0;

	for(int i = 0; i < vecnum; i++){
		if(visited[i] == INT_MAX){
			jointDfs(data, visited, low, ret, i, count, true);
		}
	}
	return ret;
}
//joint search -----------------------------------------------
```
时间复杂度为O(V + E)
