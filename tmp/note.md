1.	最小生成树，贪心算法,每次新增一个点一个边，所以肯定没有环.
2.	Prime算法，使用堆可以做到ElgE，但是如果是稠密图就不行了.
3.	DAG上的单源最短路径,一次拓扑排序访问过程就可以了.
4.	Dij算法其实操作过程和Prim过程很相似. Dij使用堆和哈希可能实现ElgV时间复杂度.
5.	有环有负数的图没有最短路径，bellman可以判断是否是这种情况,即第V次Relax还会变化,因为对于一个图如果有最终稳定的最短距离状态,那么必在|V| - 1次达到.
6.	Bellman 提前终止判断,比如每次更新与上次没有任何变化时候就可以提前结束,不需要一定左|V| - 1次.
7.	SPFA立足于Bellman,也是O(VE)时间复杂度,但是比Bellman快一点.每次都至松弛队列中的后继节点.
