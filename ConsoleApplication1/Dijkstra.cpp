/*
*/

#include <iostream>

using namespace std;

int  matrix[100][100]; // 邻接矩阵
bool visited[100];     // 标记数组
int  dist[100];        // 源点到顶点i的最短距离
int  path[100];        // 记录最短路的路径
int  source;           // 源点
int  vertex_num;       // 顶点数
int  side_num;         // 边数

void Dijkstra(int source)
{
	memset(visited, 0, sizeof(visited));  // 初始化标记数组 将数组visited全部设为0
	visited[source] = true;  // visited数组记录该点是否遍历过
	for (int i = 0; i < vertex_num; i++)//初始化各点到起点的距离与路径
	{
		dist[i] = matrix[source][i];
		path[i] = source;
	}

	int min_cost;        // 权值最小
	int min_cost_index;  // 权值最小的下标

	for (int i = 1; i < vertex_num; i++)  // 找到源点到另外 vertex_num-1 个点的最短路径
	{
		min_cost = INT_MAX;

		for (int j = 0; j < vertex_num; j++)
		{
			if (visited[j] == false && dist[j] < min_cost)  // 找到与起点直接相连的点中权值最小的，与起点不直接相连的点权值已经初始化为 INT_MAX
			{
				min_cost = dist[j];   //更新最小的权值
				min_cost_index = j;  //更新权值最小点的坐标，
			}
		}

		visited[min_cost_index] = true;  // 该点已找到，进行标记

		for (int j = 0; j < vertex_num; j++)  // 更新 dist 数组
		{
			if (visited[j] == false &&     // 确保该点还未找到从 起点的最短路径
				matrix[min_cost_index][j] != INT_MAX &&  // 确保两点之间有边
				matrix[min_cost_index][j] + min_cost < dist[j])   //判断经过中间点到 j点的距离是否小于j点到起点的距离
			{
				dist[j] = matrix[min_cost_index][j] + min_cost;   //如果是，更新距离与路径
				path[j] = min_cost_index;
			}
		}
	}
}

int main()
{
	cout << "请输入图的顶点数（<100）：";
	cin >> vertex_num;
	cout << "请输入图的边数：";
	cin >> side_num;

	for (int i = 0; i < vertex_num; i++)
		for (int j = 0; j < vertex_num; j++)
			matrix[i][j] = (i != j) ? INT_MAX : 0;  // 初始化 matrix 数组

	cout << "请输入边的信息，并用空格隔开：\n";
	int u, v, w;						//u,v为每条边上的两点    w为边的权重，
	for (int i = 0; i < side_num; i++)
	{
		cin >> u >> v >> w;
		matrix[u][v] = matrix[v][u] = w;
	}

	cout << "请输入源点（<" << vertex_num << "）：";
	cin >> source;


	Dijkstra(source);

	for (int i = 0; i < vertex_num; i++)   //经过的路径是反向输出的，从终点逆向输出到起点
	{
		if (i != source)
		{
			cout << source << "到" << i << "最短距离是：" << dist[i] << "，路径是：" << i;
			int t = path[i];  // path[i] 存放的是 i点的最短路径中与i相连的上一个节点 
			while (t != source)
			{
				cout << "--" << t;
				t = path[t];
			}
			cout << "--" << source << endl;
		}
	}

	return 0;
}
