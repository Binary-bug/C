#include<stdio.h>
#include<stdlib.h>
#define MAX 20000

typedef struct vertices{
	int n;
	struct vertices *next;
}vertex;

typedef struct queue{
	vertex *head;
	vertex *tail;
}queue;

int queue_empty(queue *);

void push(vertex **head,int k){
	vertex *temp=(vertex *)malloc(sizeof(vertex));
	temp->n=k;
	temp->next=(*head);
	(*head)=temp;
}

int pop(vertex **head){
	vertex *temp=(*head);
	(*head)=(*head)->next;
	int x=temp->n;
	free(temp);
	return x;
}


void enqueue(queue *q,int k){
	 vertex *temp=(vertex *)malloc(sizeof(vertex));
	 temp->n=k;
	 temp->next=NULL;
	 if(q->tail!=NULL)q->tail->next=temp;
	 q->tail=temp;
	 if(q->head==NULL)q->head=q->tail;
}

int dequeue(queue *q){
	vertex *temp=q->head;
	int x=temp->n;
	q->head=q->head->next;
	free(temp);
	if(q->head==NULL)q->tail=NULL;
	return x;
}
	
int queue_empty(queue *q){
	return (q->head==NULL)?1:0;
}

void main(int argc, char *argv[]){
	FILE *input=fopen("input","r");
	FILE *output=fopen("output","w");
	int i,j,k,n=0;
	char p=' ';
	fscanf(input,"%d",&n);
	int *visited=(int *)calloc(n,sizeof(int));
	int *dist=(int *)malloc(n*sizeof(int));
	queue *q=(queue *)malloc(sizeof(queue));
	q->head=q->tail=NULL;
	for(i=0;i<n;i++) dist[i]=MAX;

	vertex *s=NULL;
	int graph[500][500]={{0}};
	for(i=0;i<n;i++){
		while(fscanf(input,"%d%c",&k,&p)!= -1){
			graph[i][k-1]=1;
			if(p=='\n')
				break;
		}
		p=' ';
	}

	if(argv[1][0]=='1'){
	for(j=0;j<n;j++){
	if(!visited[j]){	
		push(&s,j+1);
		while(s!=NULL){
		int x=pop(&s);
		if(!visited[x-1]){
		visited[x-1]=1;
		fprintf(output,"%d ",x);
		for(i=0;i<n;i++)if(graph[x-1][i] ==1)push(&s,i+1);
		}}
		fprintf(output,"\n");
	 }			
	}
	}
	if(argv[1][0]=='2'){
	dist[0]=0;
	j=1;
	enqueue(q,1);
	while(!queue_empty(q)){
		int t=dequeue(q);
		if(t>1 && dist[t-1]==j)fprintf(output,"%d ",t);
		else if(t>1 && dist[t-1]==j+1){fprintf(output,"\n%d ",t);j=dist[t-1];}
		else;
		for(i=0;i<n;i++){
			if(graph[t-1][i] && !visited[i]){
				visited[i]=1;
				enqueue(q,i+1);
			   dist[i]=dist[t-1]+1;
			}
		}
	}
	fprintf(output,"\n");
	for(i=1;i<n;i++)if(dist[i]==MAX)fprintf(output,"%d ",i+1);
	fprintf(output,"\n");
	}
	return ;
}
	


