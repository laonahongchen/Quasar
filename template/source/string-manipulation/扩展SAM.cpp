#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int son[maxn][26],len[maxn],fa[maxn];
int root=1,last=1,tot=1;
int newnode(int x){
	len[++tot]=x;
	return tot;
}
void add(int w){
	if(son[last][w]){
		int p=last;
		int q=son[last][w];
		if(len[p]+1==len[q])last=q;
		else{
			int nq=newnode(len[p]+1);
			memcpy(son[nq],son[q],sizeof son[nq]);
			fa[nq]=fa[q];fa[q]=nq;
			while(p&&son[p][w]==q)son[p][w]=nq,p=fa[p];	
			last=nq;		
		}
	}else{
		int p=last;
		int np=newnode(len[p]+1);
		while(p&&!son[p][w])son[p][w]=np,p=fa[p];
		if(!p)fa[np]=root;
		else{
			int q=son[p][w];
			if(len[p]+1==len[q])fa[np]=q;
			else{
				int nq=newnode(len[p]+1);
				memcpy(son[nq],son[q],sizeof son[nq]);
				fa[nq]=fa[q];
				fa[q]=fa[np]=nq;
				while(p&&son[p][w]==q)son[p][w]=nq,p=fa[p];
			}
		}last=np;
	}
}
void deb(){
	for(int i=1;i<=tot;i++){
		fprintf(stderr,"id:%d fa:%d\n",i,fa[i]);
		for(int j=0;j<26;j++)if(son[i][j])
			fprintf(stderr,"%d--%c--%d\n",i,j+'a',son[i][j]);
	}fprintf(stderr,"\n");
}
int n,K,now,vis[maxn],cnt[maxn],f[maxn];
string s[int(1e5+1)];
char str[maxn];
void make(int u){
	while(u&&vis[u]!=now){
		vis[u]=now;
		cnt[u]++;
		u=fa[u];
	}
}
void up(int u){
	if(u==1||vis[u])return;
	vis[u]=1;
	up(fa[u]);
	f[u]+=f[fa[u]];
}
int main(){
	freopen("bzoj3473.in","r",stdin);
	scanf("%d%d",&n,&K);
	for(int i=1;i<=n;i++){
		scanf("%s",str);s[i]=string(str);
		for(int j=0;j<s[i].length();j++)
			add(s[i][j]-'a');
		last=root;
//		deb();
	}
//	deb();
	for(int i=1;i<=n;i++){
		int u=root;now=i;
		for(int j=0;j<s[i].length();j++){
			u=son[u][s[i][j]-'a'];
			make(u);
		}
	}
	memset(vis,0,sizeof vis);
	for(int i=1;i<=tot;i++)f[i]=(cnt[i]>=K)*(len[i]-len[fa[i]]);
	
	for(int i=1;i<=tot;i++)up(i);
	
	for(int i=1;i<=n;i++){
		int u=root;now=i;
		long long ans=0;
		for(int j=0;j<s[i].length();j++){
			u=son[u][s[i][j]-'a'];
			ans+=f[u];
		}
		printf("%lld%c",ans," \n"[i==n]);
	}	
	
	return 0;
}
