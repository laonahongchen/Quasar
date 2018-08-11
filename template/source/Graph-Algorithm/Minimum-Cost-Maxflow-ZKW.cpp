namespace zkw{
  struct eglist{
    int other[maxM], succ[maxM], last[maxM], cap[maxM], cost[maxM], sum;
    void clear() {
      memset(last, -1, sizeof last);
      sum = 0;
    }
    void _addEdge(int a,int b,int c,int d) {
      other[sum] = b, succ[sum] = last[a], last[a] = sum, cost[sum] = d, cap[sum++] = c;
    }
    void addEdge(int a,int b,int c,int d) {
      _addEdge(a, b, c, d);
      _addEdge(b, a, 0, -d);
    }
  }e;

  int n, m, S, T, tot, totFlow, totCost;
  int dis[maxN], slack[maxN], visit[maxN], cur[maxN];

  int modlable() {
    int delta = inf;
    for (int i = 1; i <= T; ++i) {
      if (!visit[i] && slack[i] < delta)
	delta = slack[i];
      slack[i] = inf;
     // cur[i] = e.last[i];
    }
    if (delta == inf)
      return 1;
    for (int i = 1; i <= T; ++i)
      if (visit[i]) dis[i] += delta;
    return 0;
  }

  int dfs(int x,int flow) {
    if (x == T) {
      totFlow += flow;
      totCost += flow * (dis[S] - dis[T]);
      return flow;
    }
    visit[x] = 1;
    int left = flow;
    for (int i = e.last[x]; ~i; i = e.succ[i])
      if (e.cap[i] > 0 && !visit[e.other[i]]) {
	int y = e.other[i];
	if (dis[y] + e.cost[i] == dis[x]) {
	  int delta = dfs(y, std::min(left, e.cap[i]));
	  e.cap[i] -= delta;
	  e.cap[i ^ 1] += delta;
	  left -= delta;
	  if (!left) {visit[x] = 0;return flow;}
	}else {
	  slack[y] = std::min(slack[y], dis[y] + e.cost[i] - dis[x]);
	}
      }
    return flow - left;
  }

  std::pair<int,int> minC() {
    totFlow = totCost = 0;
    std::fill(dis + 1, dis + T + 1, 0);
    for (int i = 1; i <= T; ++i) cur[i] = e.last[i];
    do {
      do {
	std::fill(visit + 1, visit + T + 1, 0);
      }while(dfs(S, inf));
    }while(!modlable());
    return std::make_pair(totFlow, totCost);
  }
}
