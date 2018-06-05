#include<stdio.h>
#include<stdlib.h>

typedef struct vertices{
	int n;
	struct vertices *next;
}vertex;

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


void main(int argc, char *argv[]){
	FILE *input=fopen("input","r");
	FILE *output=fopen("output","w");
	int i,j,k,n=0;
	char p=' ';
	fscanf(input,"%d",&n);
	int *visited=(int *)calloc(n,sizeof(int));
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
#if 0

	for(j=0;j<n;j++){

#endif

	return ;
}
	


