#include<stdio.h>
#include<stdlib.h>
#define M 9999

int a=0;

typedef struct priority{
	int nod;
	int prior;
}*Priority;

typedef struct list{
	int valoare;
	struct list* next;
}*List;

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

List initList(List nod,int valoare) {
	nod = (List) malloc(sizeof(struct list));
	a++;
	nod->valoare = valoare;
	a++;
	nod->next = NULL;
	a++;
	return nod;
}

List addList(List list,int val){
	List temp=NULL;
	a++;
	if(list == NULL){
		a++;
		list=initList(list,val);
		a++;
	}
	else{
		a++;
		List aux = list;
		a++;
		while(aux->next != NULL){
			a++;
			aux = aux->next; 
			a++;
		}
		temp = initList(temp,val);
		a++;
		aux->next=temp;
		a++;
	}
	return list;
}


void exitList(List list)
{
	List nod=list;
	a++;
	while(nod!=NULL)
	{
		a++;
		list=list->next;
		a++;
		free(nod);
		a++;
		nod=list;
		a++;
	}
}

typedef struct graph{
	int V;
	List* array;
	int **cost;
	int *selectat;
	int *dist;
	int *parent;
}*Graph;

void sortare(struct priority *vector,int n,Graph g){
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
	int i,k=0;
	a++;
	int min;
	List temp=NULL;
	a++;
	g->selectat[s]=1;
	a++;
	for(i=0;i<g->V;i++){
		a++;
		temp=g->array[s];
		a++;
		while(temp!=NULL){
			a++;
			if(temp->valoare==i){
				a++;
				g->dist[i]=g->cost[s][i];
				a++;
				v_drum[k].nod=i;
				a++;
				v_drum[k].prior=g->dist[i];
				a++;
				g->parent[i]=s;
				a++;
				k++;
				a++;
				break;
				}
			else{
				a++;	
				g->dist[i]=M;
				a++;
				g->parent[i]=M;
				a++;
			}
			temp=temp->next;
			a++;
		}
	}
	sortare(v_drum,k,g);
	a++;
	while(v_drum[0].prior!=M){
		a++;
		min=v_drum[0].nod;
		a++;
		g->selectat[min]=1;
		a++;
		List vecin;
		vecin=g->array[min];
		a++;
		while(vecin!=NULL){
			a++;
			if(g->selectat[vecin->valoare]==0 && g->dist[vecin->valoare] > g->dist[min] + g->cost[min][vecin->valoare]){
				a++;
				g->dist[vecin->valoare]=g->dist[min] + g->cost[min][vecin->valoare];
				a++;
				g->parent[vecin->valoare]=min;
				a++;
				v_drum[k].nod=vecin->valoare;
				a++;
				v_drum[k].prior=g->dist[vecin->valoare];
				a++;
				k++;
				a++;
			}
			vecin=vecin->next;
			a++;
		}
		v_drum[0].prior=M;
		a++;
		sortare(v_drum,k,g);
		a++;
		}

	Stack* stack=initStack(d);
	a++;
	int node;
	node=g->parent[d];
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
	fprintf(fp,"%d\n",g->dist[d]);
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

void readFile(Graph g,FILE* fp){
	
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
	g->array=(List*)malloc((n+1)*sizeof(List));	
	a++;
	g->cost=(int**)malloc(n*sizeof(int*));
	a++;
	for(i=0;i<n;i++){
		a++;
		g->cost[i]=(int*)malloc(n*sizeof(int));
		a++;
	}
	g->selectat=(int*)malloc(n*sizeof(int));
	a++;
	g->dist=(int*)malloc(n*sizeof(int));
	a++;
	g->parent=(int*)malloc(n*sizeof(int));
	a++;
	g->V=n;
	a++;
	

	while(j<m){
		a++;
		fscanf(fp,"%d %d %d",&contor,&legatura,&valoare);
		a++;
		g->array[contor] = addList(g->array[contor],legatura);
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
	for(i=0;i<=n;i++)
		exitList(g->array[i]);
	free(g->cost);
	free(g->selectat);
	free(g->dist);
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
