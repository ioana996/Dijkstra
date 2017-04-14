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
	a++;
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

typedef struct heap{
	int size;
	struct priority *vector;
}Heap;

void initHeap(Heap* heap){
	heap->size=0;
	a++;
}

void interschimbare(Heap* heap,struct priority* p1,struct priority* p2){
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
		interschimbare(heap,(&heap->vector[i]),(&heap->vector[m]));
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
		interschimbare(heap,(&heap->vector[i]),(&heap->vector[i/2]));
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
		return;
	}
	else{	
		a++;
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

void Dijkstra(Graph g,int s, int d,Heap* heap){
	int i;
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
				insert(heap,i,g->dist[i]);
				a++;
				g->parent[i]=s;
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
				insert(heap,vecin->valoare,g->dist[vecin->valoare]);
				a++;
			}
			vecin=vecin->next;
			a++;
		}
		makeHeap(heap);
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

void readFile(Graph g, FILE* fp){
	
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
	for(i=0;i<n;i++){
		a++;
		g->array[i]=NULL;
		a++;
	}

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
