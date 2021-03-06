namespace suffix_array{
	int wa[MAXN], wb[MAXN], ws[MAXN], wv[MAXN];
	bool cmp(int *r, int a, int b, int l) {
		return r[a] == r[b] && r[a + l] == r[b + l];
	}
	void DA(int *r, int *sa, int n, int m) {
		int *x = wa, *y = wb, *t;
		for (int i = 0; i < m; i++) ws[i] = 0;
		for (int i = 0; i < n; i++) ws[x[i] = r[i]]++;
		for (int i = 1; i < m; i++) ws[i] += ws[i - 1];
		for (int i = n - 1; i >= 0; i--) sa[--ws[x[i]]] = i;
		for (int i, j = 1, p = 1; p < n; j <<= 1, m = p) {
			for (p = 0, i = n - j; i < n; i++) y[p++] = i;
			for (i = 0; i < n; i++) if (sa[i] >= j) y[p++] = sa[i] - j;
			for (i = 0; i < n; i++) wv[i] = x[y[i]];
			for (i = 0; i < m; i++) ws[i] = 0;
			for (i = 0; i < n; i++) ws[wv[i]]++;
			for (i = 1; i < m; i++) ws[i] += ws[i - 1];
			for (i = n - 1; i >= 0; i--) sa[--ws[wv[i]]] = y[i];
			for (t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; i++)
				x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
		}
	}
	void getheight(int *r, int *sa, int *rk, int *h, int n) {
		for (int i = 1; i <= n; i++) rk[sa[i]] = i;
		for (int i = 0, j, k = 0; i < n; h[rk[i++]] = k)
			for (k ? k-- : 0, j = sa[rk[i] - 1]; r[i + k] == r[j + k]; k++);
	}
};
