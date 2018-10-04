#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;
int const maxn=256+5;
char s[maxn];
bool failed;
struct Node{
	bool have_value;
	int v;        //�ڵ�ֵ
	Node *left,*right;
	Node():have_value(false),left(NULL),right(NULL){}
};

Node *root;

Node* newnode(){
	return new Node();
}
void addnode(int v,char* s){
	int n=strlen(s);
	Node* u=root;
	for(int i=0;i<n;i++)
	if(s[i]=='L'){
		if(u->left==NULL) u->left=newnode();
		u=u->left;
	}
	else if(s[i]=='R'){
		if(u->right==NULL) u->right=newnode();
		u=u->right;
	}
	if(u->have_value) failed=true;
	u->v=v;
	u->have_value=true;
}
bool bfs( vector<int>& ans){
	queue<Node*> q;
	ans.clear();
	q.push(root);
	while(!q.empty()){
		Node* u=q.front(); q.pop();
		if(!u->have_value) return false;
		ans.push_back(u->v);
		if(u->left!=NULL) q.push(u->left);
		if(u->right!=NULL) q.push(u->right);
	}
	return true;
}
void remove_tree(Node* u){
	if(u==NULL) return;
	remove_tree(u->left);
	remove_tree(u->right);
	delete u;
}
bool read_input(){
	failed=false;
	remove_tree(root);
	root=newnode();
	for(;;){
		if(scanf("%s",s)!=1) return false;
		if(!strcmp(s,"()")) break;
		int v;
		sscanf(&s[1],"%d",&v);
		addnode(v,strchr(s,',')+1);
		}
	return true;
}



int main(){
	while(read_input()){
		vector<int> out;
		if(bfs(out)&&!failed)
		for(int i=0;i<out.size();i++){
			if(i!=out.size()-1) printf("%d ",out[i]);
			else printf("%d\n",out[i]);
		}
		else printf("not complete\n");
	}
}
