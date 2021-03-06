//求字符串b[0, n)的每个后缀和a[0, m)的最长公共前缀。 
//将字符串翻转后可以求回文串。 
void ExtendedKmp(int n, int m){ 
	int i, j, k;
    for(j = 0;j + 1 < m && a[j] == a[j + 1];++j);
    nxt[1] = j;k = 1;
    for(i = 2;i < m;++i){
        int pos = k + nxt[k], len = nxt[i - k];
        if(i + len < pos)nxt[i] = len;
        else {
            for(j = max(0, pos - i);i + j < m && a[j] == a[i + j];++j);
            nxt[i] = j;k = i;
        }
    }
    for(j = 0;j < m && j < n && a[j] == b[j];++j);
    f[0] = j;k = 0;
    for(i = 1;i < n;++i){
        int pos = k + f[k], len = nxt[i - k];
        if(i + len < pos)f[i] = len;
        else {
            for(j = max(0, pos - i);j < m && i + j < n && a[j] == b[i + j];++j);
            f[i] = j;k = i;
        }
    }
}
//z[i]表示s[i..n-1]和s[0..n-1]的最长公共前缀
void exkmp(char *s, int n, int *z) {
	memset(z, 0, sizeof(z[0]) * n);
	for (int i = 1, x = 0, y = 0; i < n; ++i) {
		if (i <= y) z[i] = min(y - i, z[i - x]);
		while (i + z[i] < n && s[i + z[i]] == s[z[i]]) z[i]++;
		if (y <= i + z[i]) x = i, y = i + z[i];
	}
	z[0] = n;
}

