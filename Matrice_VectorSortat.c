#include<stdio.h>
#include<stdlib.h>
#define M 9999

int a=0;

typedef struct priority{
	int nod;
	int prior;
}*Priority;

typedef struct graph{
	int V;
	int **adjMat;
	int **cost;
	int *selectat;
	int *distance;
	int *parent;
}*Graph;

typedef struct stack
{
	int node;
	struct stack *next;
}Stack;

Stack* initStack(int nod) 
{
	Stack* node;
	node=(Stack*)malloc(sizeof(Stack));
	a++;
	node->node=nod;
	a++;
	node->next=NULL;
	a++;
	return node;
}

Stack* addStack(Stack* stack,int nod)
{
	if(stack==NULL){
		a++;
		return initStack(nod);
	}
	else
		{
			a++;
			Stack* node;
			node=initStack(nod);
			a++;
			node->next=stack;
			a++;
			return node;
		 }
	
}

void exitStack(Stack* stack)
{
	Stack* nod=stack;
	while(nod!=NULL)
	{
		a++;
		stack=stack->next;
		a++;
		free(nod);
		a++;
		nod=stack;
		a++;
	}
}

void printStack(Stack* stack,FILE* fp)
{
	while(stack!=NULL && stack->next!=NULL )
	{	
		a++;
		fprintf(fp,"%d ",stack->node);
		a++;
		stack=stack->next;
		a++;
	 }
	if(stack->next==NULL )
	{	
		a++;
		fprintf(fp,"%d\n",stack->node);
		a++;
		stack=stack->next;
		a++;
	 }
}


void Sortare(struct priority *vector,int n,Graph g){
	int i,j;
	struct priority aux;
	for(i=0;i<n-1;i++){
		a++;
		for(j=0;j<n-i-1;j++){
			a++;
			if(vector[j].prior > vector[j+1].prior){
				a++;
				aux.prior=vector[j].prior;
				a++;
				aux.nod=vector[j].nod;
				a++;
				vector[j].prior=vector[j+1].prior;
				a++;
				vector[j].nod=vector[j+1].nod;
				a++;
				vector[j+1].prior=aux.prior;
				a++;
				vector[j+1].nod=aux.nod;
				a++;
				}
			else if(vector[j].prior == vector[j+1].prior){
				a++;
				if(vector[j].nod > vector[j+1].nod){
				a++;
				aux.prior=vector[j].prior;
				a++;
				aux.nod=vector[j].nod;
				a++;
				vector[j].prior=vector[j+1].prior;
				a++;
				vector[j].nod=vector[j+1].nod;
				a++;
				vector[j+1].prior=aux.prior;
				a++;
				vector[j+1].nod=aux.nod;
				a++;
				}
			}
		}
	}

}

void Dijkstra(Graph g,int s, int d,struct priority* v_drum){
	int i,ct,min;
	int k=0;
	a++;
	g->selectat[s]=1;
	a++;
	for(i=0;i<g->V;i++){
			a++;
			if(g->adjMat[s][i]==1){
				a++;
				g->distance[i]=g->cost[s][i];
				a++;
				v_drum[k].nod=i;
				a++;
				v_drum[k].prior=g->distance[i];
				a++;
				g->parent[i]=s;
				a++;
				k++;
				a++;
				}
			else{	
				a++;
				g->distance[i]=M;
				a++;
				g->parent[i]=M;
				a++;
			}
	}
	Sortare(v_drum,k,g);
	a++;
	while(v_drum[0].prior!=M){
		a++;
		min=v_drum[0].nod;
		a++;
		g->selectat[min]=1;
		a++;
		for(ct=0;ct<g->V;ct++){		
			a++;
			if(g->selectat[ct]==0 && g->distance[ct] > g->distance[min] + g->cost[min][ct]){
				a++;
				g->distance[ct]=g->distance[min] + g->cost[min][ct];
				a++;
				g->parent[ct]=min;
				a++;
				v_drum[k].nod=ct;
				a++;
				v_drum[k].prior=g->distance[ct];
				a++;
				k++;
				a++;
			}
		}
		v_drum[0].prior=M;
		a++;
		Sortare(v_drum,k,g);
		a++;
	}

	Stack* stack=initStack(d);
	a++;
	int node=g->parent[d];
	a++;
	while(node!=s){
		a++;
		stack=addStack(stack,node);
		a++;
		node=g->parent[node];
		a++;
	}
	FILE* fp;
	fp = fopen("dijkstra.out", "w");
	a++;
	fprintf(fp,"%d\n",g->distance[d]);
	a++;
	fprintf(fp,"%d ",s);
	a++;
	printStack(stack,fp);
	a++;
	exitStack(stack);
	a++;
	fprintf(fp,"%d",a);
	fclose(fp);
}

void readFile(Graph g, FILE* fp){
	
	int j=0,i;
	a++;
	int contor,legatura,valoare;
	int m,n;
	int s,d;
	int k,q;
	struct priority *v_drum;
	
	fscanf(fp,"%d %d",&m,&n);
	a++;
	fscanf(fp,"%d %d",&s,&d);
	a++;
	v_drum=(Priority)malloc(m*sizeof(struct priority));
	a++;
	g->adjMat=(int**)malloc(n*sizeof(int*));
	a++;
	for(i=0;i<n;i++){
		a++;
		g->adjMat[i]=(int*)malloc(n*sizeof(int));
		a++;
	}	
	g->cost=(int**)malloc(n*sizeof(int*));
	a++;
	for(i=0;i<n;i++){
		a++;
		g->cost[i]=(int*)malloc(n*sizeof(int));
		a++;
	}
	g->selectat=(int*)malloc(n*sizeof(int));
	a++;
	g->distance=(int*)malloc(n*sizeof(int));
	a++;
	g->parent=(int*)malloc(n*sizeof(int));
	a++;
	g->V=n;
	a++;

	for(i=0;i<n;i++){
		a++;
		for(k=0;k<n;k++){
			a++;
			g->adjMat[i][k]=0;
			a++;
		}
	}

	while(j<m){
		a++;
		fscanf(fp,"%d %d %d",&contor,&legatura,&valoare);
		a++;
		g->adjMat[contor][legatura]=1;
		a++;
		g->cost[contor][legatura]=valoare;
		a++;
		j++;
		a++;
	}
	for(k=0;k<n;k++){
		a++;
		for(q=0;q<n;q++){
			a++;
			if(g->cost[k][q]!=0){
				a++;
				continue;
			}
			else{
				a++;
				g->cost[k][q]=M;
				a++;
			}
		}
	}
	for(i=0;i<n;i++){
		a++;
		g->selectat[i]=0;
		a++;
	}

	Dijkstra(g,s,d,v_drum);

	free(v_drum);
	free(g->adjMat);
	free(g->cost);
	free(g->selectat);
	free(g->distance);
	free(g->parent);
	free(g);
	
}


int main(int argc,char **argv){
	FILE *data;
	data=fopen("dijkstra.in","r");
	Graph g;
	g=(Graph)malloc(sizeof(struct graph));
	readFile(g, data);	
	fclose(data);

	return 0;
}	
