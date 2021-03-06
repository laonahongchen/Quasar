const int INF = 100000000;
const int Maxspace = 500000;
struct SplayNode{
	int ls, rs, zs, ms;
	SplayNode() {
		ms = 0;
		ls = rs = zs = -INF;
	}
	SplayNode(int d) {
		ms = zs = ls = rs = d;
	}
	SplayNode operator +(const SplayNode &p)const {
		SplayNode ret;
		ret.ls = max(ls, ms + p.ls);
		ret.rs = max(rs + p.ms, p.rs);
		ret.zs = max(rs + p.ls, max(zs, p.zs));
		ret.ms = ms + p.ms;
		return ret;
	}
}t[MAXN], d[MAXN];
int n, m, rt, top, a[MAXN], f[MAXN], c[MAXN][2], g[MAXN], h[MAXN], z[MAXN];
bool r[MAXN], b[MAXN];
void makesame(int x, int s) {
	if (!x) return;
	b[x] = true;
	d[x] = SplayNode(g[x] = s);
	t[x].zs = t[x].ms = g[x] * h[x];
	t[x].ls = t[x].rs = max(g[x], g[x] * h[x]);
}
void makerev(int x) {
	if (!x) return;
	r[x] ^= 1;
	swap(c[x][0], c[x][1]);
	swap(t[x].ls, t[x].rs);
}
void pushdown(int x) {
	if (!x) return;
	if (r[x]) {
		makerev(c[x][0]);
		makerev(c[x][1]);
		r[x]=0;
	}
	if (b[x]) {
		makesame(c[x][0],g[x]);
		makesame(c[x][1],g[x]);
		b[x]=g[x]=0;
	}
}
void updata(int x) {
	if (!x) return;
	h[x]=h[c[x][0]]+h[c[x][1]]+1;
	t[x]=t[c[x][0]]+d[x]+t[c[x][1]];
}
void rotate(int x,int k) {
	pushdown(x);pushdown(c[x][k]);
	int y = c[x][k]; c[x][k] = c[y][k^1]; c[y][k^1] = x;
	if (f[x] != -1) c[f[x]][c[f[x]][1] == x] = y; else rt = y;
	f[y] = f[x]; f[x] = y; f[c[x][k]] = x;
	updata(x); updata(y);
}
void splay(int x, int s) {
	while (f[x] != s) {
		if (f[f[x]]!=s) {
			pushdown(f[f[x]]);
			rotate(f[f[x]], (c[f[f[x]]][1] == f[x]) ^ r[f[f[x]]]);
		}
		pushdown(f[x]);
		rotate(f[x], (c[f[x]][1]==x) ^ r[f[x]]);
	}
}
void build(int &x,int l,int r) {
	if (l > r) {x = 0; return;}
	x = z[top--];
	if (l < r) {
		build(c[x][0],l,(l+r>>1)-1);
		build(c[x][1],(l+r>>1)+1,r);
	}
	f[c[x][0]] = f[c[x][1]] = x;
	d[x] = SplayNode(a[l+r>>1]);
	updata(x);
}
void init() {
	d[0] = SplayNode();
	f[rt=2] = -1;
	f[1] = 2; c[2][0] = 1;
	int x;
	build(x,1,n);
	c[1][1] = x; f[x] = 1;
	splay(x, -1);
}
int find(int z) {
	int x = rt; pushdown(x);
	while (z != h[c[x][0]] + 1) {
		if (z > h[c[x][0]] + 1) {
			z -= h[c[x][0]] + 1;
			x = c[x][1];
		}
		else x = c[x][0];
		pushdown(x);
	}
	return x;
}
void getrange(int &x,int &y) {
	y = x + y - 1;
	x = find(x);
	y = find(y + 2);
	splay(y, -1);
	splay(x, y);
}
void recycle(int x) {
	if (!x) return;
	recycle(c[x][0]);
	recycle(c[x][1]);
	z[++top]=x;
	t[x] = d[x] = SplayNode();
	r[x] = b[x] = g[x] = f[x] = h[x] = 0;
	c[x][0] = c[x][1]=0;
}
int main() {
	scanf("%d%d",&n,&m);
	for (int i = 1; i <= n; i++) scanf("%d",a+i);
	for (int i = Maxspace; i>=3; i--) z[++top] = i;
	init();
	for (int i = 1; i <= m; i++) {
		char op[10];
		int x, y, tmp;
		scanf("%s", op);
		if (!strcmp(op, "INSERT")) {
			scanf("%d%d", &x, &y);
			n += y;
			if (!y) continue;
			for (int i = 1; i <= y; i++) scanf("%d",a+i);
			build(tmp, 1, y);
			x = find(x + 1); pushdown(x);
			if (!c[x][1]) {c[x][1] = tmp; f[tmp] = x;}
			else{
				x = c[x][1]; pushdown(x);
				while (c[x][0]) {
					x = c[x][0];
					pushdown(x);
				}
				c[x][0] = tmp; f[tmp] = x;
			}
			splay(tmp, -1);
		}
		else if (!strcmp(op, "DELETE")) {
			scanf("%d%d", &x, &y); n -= y;
			if (!y) continue;
			getrange(x, y);
			int k = (c[y][0] == x);
			recycle(c[x][k]);
			f[c[x][k]] = 0;
			c[x][k] = 0;
			splay(x, -1);
		}
		else if (!strcmp(op, "REVERSE")) {
			scanf("%d%d", &x, &y);
			if (!y) continue;
			getrange(x, y);
			int k = (c[y][0]==x);
			makerev(c[x][k]);
			splay(c[x][k], -1);
		}
		else if (!strcmp(op, "GET-SUM")) {
			scanf("%d%d", &x, &y);
			if (!y) {
				printf("0\n");
				continue;
			}
			getrange(x,y);
			int k = (c[y][0] == x);
			printf("%d\n", t[c[x][k]].ms);
			splay(c[x][k], -1);
		}
		else if (!strcmp(op, "MAX-SUM")) {
			x = 1; y = n;
			getrange(x, y);
			int k = (c[y][0] == x);
			printf("%d\n", t[c[x][k]].zs);
			splay(c[x][k], -1);
		}
		else if (!strcmp(op, "MAKE-SAME")) {
			scanf("%d%d%d", &x, &y, &tmp);
			if (!y) continue;
			getrange(x, y);
			int k = (c[y][0] == x);
			makesame(c[x][k], tmp);
			splay(c[x][k], -1);
		}
	}
	return 0;
}
