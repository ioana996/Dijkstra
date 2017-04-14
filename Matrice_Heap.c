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


typedef struct heap{
	int size;
	struct priority *vector;
}Heap;

void initHeap(Heap* heap){
	heap->size=0;
	a++;
}

void swap(Heap* heap,struct priority* p1,struct priority* p2){
	struct priority aux=*p1;
	a++;
	*p1=*p2;
	a++;
	*p2=aux;
	a++;
}

void heapify(Heap* heap,int i){
	int st=2*i;
	a++;
	int dr=2*i+1;
	a++;
	int m;
	if(st<=heap->size-1 && heap->vector[st].prior <= heap->vector[i].prior){
		a++;
		m=st;
		a++;
	}
	else{
		a++;
		m=i;
		a++;
	}
	if(dr<=heap->size-1 && heap->vector[dr].prior <= heap->vector[m].prior){
		a++;
		m=dr;
		a++;
	}
	if(m!=i){
		a++;
		swap(heap,(&heap->vector[i]),(&heap->vector[m]));
		a++;	
		heapify(heap,m);
		a++;
	}
}

void insert(Heap* heap,int valoare,int prioritate){
	int i;
	if(heap->size==0){
		a++;
		heap->vector=(Priority)malloc(sizeof(struct priority));
		a++;
	}
	else{
		a++;
		heap->vector=(Priority)realloc(heap->vector,(heap->size+1)*sizeof(struct priority));
		a++;
	}
	i=(heap->size)++;
	a++;
	while(i>0 && heap->vector[i].prior > heap->vector[i/2].prior){
		a++;
		swap(heap,(&heap->vector[i]),(&heap->vector[i/2]));
		a++;
		i=i/2;
		a++;
	}
	heap->vector[i].nod=valoare;
	a++;
	heap->vector[i].prior=prioritate;
	a++;
}

void deleteHeap(Heap *heap) {
	free(heap->vector) ;
	a++;
}


void delete(Heap* heap){
	if(heap->size <= 0){
		a++;
		deleteHeap(heap);
		a++;
		return ;
	}
	else{	a++;
		heap->vector[0]=heap->vector[heap->size-1];
		a++;
		heap->size--;	
		a++;
		heap->vector=realloc(heap->vector,heap->size*sizeof(struct priority));
		a++;
		heapify(heap,0);
		a++;
	}
} 

void makeHeap(Heap* heap){
	int i;
	for(i = (heap->size - 1) / 2; i >= 0; i--) {
	a++;
        heapify(heap, i) ;
	a++;
    }
}



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


void Dijkstra(Graph g,int s, int d,Heap* heap){
	int i,ct,min;
	g->selectat[s]=1;
	a++;
	for(i=0;i<g->V;i++){
			a++;
			if(g->adjMat[s][i]==1){
				a++;
				g->distance[i]=g->cost[s][i];
				a++;
				insert(heap,i,g->distance[i]);
				a++;
				g->parent[i]=s;
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
	makeHeap(heap);
	a++;
	while(heap->size!=0){
		a++;
		min=heap->vector[0].nod;
		a++;
		g->selectat[min]=1;
		a++;
		delete(heap);
		a++;
		for(ct=0;ct<g->V;ct++){
			a++;
			if(g->selectat[ct]==0 && g->distance[ct] > g->distance[min] + g->cost[min][ct]){
				a++;
				g->distance[ct]=g->distance[min] + g->cost[min][ct];
				a++;
				g->parent[ct]=min;
				a++;
				insert(heap,ct,g->distance[ct]);
				a++;
			}
		}
		makeHeap(heap);
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

void readFile(Graph g, FILE *fp){
	
	int j=0,i;
	a++;
	int contor,legatura,valoare;
	int m,n;
	int s,d;
	int k,q;
	Heap* heap = (Heap *)malloc(sizeof *heap) ;
	a++;
	fscanf(fp,"%d %d",&m,&n);
	a++;
	fscanf(fp,"%d %d",&s,&d);
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
	initHeap(heap);
	a++;
	Dijkstra(g,s,d,heap);
	
	deleteHeap(heap);
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
