int bfs(){
	for (int i = 1;i <= t;i ++) d[i] = -1;
	int l,r;
	q[l = r = 0] = s, d[s] = 0;
	for (;l <= r;l ++)
		for (int k = h[q[l]]; k > -1; k = nxt[k])
			if (d[p[k]] == -1 && c[k] > 0) d[p[k]] = d[q[l]] + 1, q[++ r] = p[k];
	return d[t] > -1 ? 1 : 0;
}
int dfs(int u,int ext){
	if (u == t) return ext;
	int k = w[u],ret = 0;
	for (; k > -1; k = nxt[k], w[u] = k){      //w数组为当前弧 
		if (ext == 0) break;
		if (d[p[k]] == d[u] + 1 && c[k] > 0){
			int flow = dfs(p[k], min(c[k], ext));
			if (flow > 0){
				c[k] -= flow, c[k ^ 1] += flow;
				ret += flow, ext -= flow;     //ret累计增广量，ext记录还可增广的量 
			}
		}
	}
	if (k == -1) d[u] = -1;
	return ret;
}
void dinic() {
	while (bfs()) {
		for (int i = 1; i <= t;i ++) w[i] = h[i];
		dfs(s, inf);
	}
}
