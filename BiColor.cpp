#include <limits.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
//
struct Queue { 
	int front, rear, size; 
	unsigned capacity; 
	int* array; 
}; 

//
struct Queue* createQueue(unsigned capacity) 
{ 
	struct Queue* queue = (struct Queue*)malloc( 
		sizeof(struct Queue)); 
	queue->capacity = capacity; 
	queue->front = queue->size = 0; 
	queue->rear = capacity - 1; 
	queue->array = (int*)malloc( 
		queue->capacity * sizeof(int)); 
	return queue; 
} 
//
int isFull(struct Queue* queue) 
{ 
	return (queue->size == queue->capacity); 
} 
//
int isEmpty(struct Queue* queue) 
{ 
	return (queue->size == 0); 
} 
// 
void enqueue(struct Queue* queue, int item) 
{ 
	if (isFull(queue)) 
		return; 
	queue->rear = (queue->rear + 1) 
				% queue->capacity; 
	queue->array[queue->rear] = item; 
	queue->size = queue->size + 1; 
	//printf("%d enqueued to queue\n", item); 
} 
//
int dequeue(struct Queue* queue) 
{ 
	if (isEmpty(queue)) 
		return INT_MIN; 
	int item = queue->array[queue->front]; 
	queue->front = (queue->front + 1) 
				% queue->capacity; 
	queue->size = queue->size - 1; 
	return item; 
} 
//
int front(struct Queue* queue) 
{ 
	if (isEmpty(queue)) 
		return INT_MIN; 
	return queue->array[queue->front]; 
} 
//
int rear(struct Queue* queue) 
{ 
	if (isEmpty(queue)) 
		return INT_MIN; 
	return queue->array[queue->rear]; 
} 
//
int isBipartiteUtil(int *G, int src, int colorArr[], int V) 
{ 
	colorArr[src] = 1; 

	struct Queue* q = createQueue(200); 
	enqueue(q, src);

	while (!isEmpty(q)) { 

		int u = front(q); 
		dequeue(q); 

		for (int v = 0; v < V; ++v) { 

			if (*((G+u*V) + v) && colorArr[v] == -1) { 
 
				colorArr[v] = 1 - colorArr[u]; 
				enqueue(q,v); 
			} 

			else if (*((G+u*V) + v) && colorArr[v] == colorArr[u]) 
				return 0; 
		} 
	} 

	return 1; 
} 
// 
int isBiColorable(int *G, int V) 
{ 
 
	int colorArr[V]; 
	for (int i = 0; i < V; ++i) 
		colorArr[i] = -1; 

	for (int i = 0; i < V; i++) 
		if (colorArr[i] == -1) 
			if (isBipartiteUtil(G, i, colorArr,V) == 0) 
				return 0; 
				
	return 1; 
} 
//
int main() 
{ 
	int n=0,L,row,col, count=0;
	int Resl[1000];
	while(1)
	{
	count++;
	scanf("%d",&n);
	if(n==0) break;
	
	scanf("%d",&L);
	int G[n][n];
	memset(G, 0, sizeof(G[0][0]) * n * n);
	for(int r=0;r<L;r++)
	{
		scanf("%d",&row);
		scanf("%d", &col);
		G[row][col]=1;
		G[col][row]=1;
	}

	Resl[count]=isBiColorable((int *)G, n);
	}
	for(int y=1;y<count;y++)
	{
	if(Resl[y]==1) printf("BICOLORABLE.\n");
	else printf("NOT BICOLORABLE.\n"); 	
	}
	
	return 0; 
}
