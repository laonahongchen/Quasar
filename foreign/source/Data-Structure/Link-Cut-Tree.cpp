struct MsgNode{
	int leftColor, rightColor, answer;
	MsgNode() {
		leftColor = -1;
		rightColor = -1;
		answer = 0;
	}
	MsgNode(int c) {
		leftColor = rightColor = c;
		answer = 1;
	}
	MsgNode operator +(const MsgNode &p)const {
		if (answer == 0) return p;
		if (p.answer == 0) return *this;
		MsgNode ret;
		ret.leftColor = leftColor;
		ret.rightColor = p.rightColor;
		ret.answer = answer + p.answer - (rightColor == p.leftColor);
		return ret;
	}
}d[MAXN], g[MAXN];
int n, m, c[MAXN][2], f[MAXN], p[MAXN], s[MAXN], flag[MAXN];
bool r[MAXN];
void init(int x, int value) {
	d[x] = g[x] = MsgNode(value);
	c[x][0] = c[x][1] = 0;
	f[x] = p[x] = flag[x] = -1;
	s[x] = 1;
}
void update(int x) {
	s[x] = s[c[x][0]] + s[c[x][1]] + 1;
	g[x] = MsgNode();
	if (c[x][0 ^ r[x]]) g[x] = g[x] + g[c[x][0 ^ r[x]]];
	g[x] = g[x] + d[x];
	if (c[x][1 ^ r[x]]) g[x] = g[x] + g[c[x][1 ^ r[x]]];
}
void makesame(int x, int c) {
	flag[x] = c;
	d[x] = MsgNode(c);
	g[x] = MsgNode(c);
}
void pushdown(int x) {
	if (r[x]) {
		std::swap(c[x][0], c[x][1]);
		r[c[x][0]] ^= 1;
		r[c[x][1]] ^= 1;
		std::swap(g[c[x][0]].leftColor, g[c[x][0]].rightColor);
		std::swap(g[c[x][1]].leftColor, g[c[x][1]].rightColor);
		r[x] = false;
	}
	if (flag[x] != -1) {
		if (c[x][0]) makesame(c[x][0], flag[x]);
		if (c[x][1]) makesame(c[x][1], flag[x]);
		flag[x] = -1;
	}
}
void rotate(int x, int k) {
	pushdown(x); pushdown(c[x][k]);
	int y = c[x][k]; c[x][k] = c[y][k ^ 1]; c[y][k ^ 1] = x;
	if (f[x] != -1) c[f[x]][c[f[x]][1] == x] = y;
	f[y] = f[x]; f[x] = y; f[c[x][k]] = x; std::swap(p[x], p[y]);
	update(x); update(y);
}
void splay(int x, int s = -1) {
	pushdown(x);
	while (f[x] != s) {
		if (f[f[x]] != s) rotate(f[f[x]], (c[f[f[x]]][1] == f[x]) ^ r[f[f[x]]]);
		rotate(f[x], (c[f[x]][1] == x) ^ r[f[x]]);
	}
	update(x);
}
void access(int x) {
	int y = 0;
	while (x != -1) {
		splay(x); pushdown(x);
		f[c[x][1]] = -1; p[c[x][1]] = x;
		c[x][1] = y; f[y] = x; p[y] = -1;
		update(x); x = p[y = x];
	}
}
void setroot(int x) {
	access(x);
	splay(x);
	r[x] ^= 1;
	std::swap(g[x].leftColor, g[x].rightColor);
}
void link(int x, int y) {
	setroot(x);
	p[x] = y;
}
void cut(int x, int y) {
	access(x); splay(y, -1);
	if (p[y] == x) p[y] = -1;
	else {
		access(y); 
		splay(x,-1);
		p[x] = -1;
	}
}
