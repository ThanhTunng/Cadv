#ifndef BFS_TRAVERSAL
#define BFS_TRAVERSAL
#define SIZE 50
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphLib.h"

typedef struct queue{
  int items[SIZE];
  int front;
  int rear;
}queue;

queue *creatQueue(){
  queue *q = (queue*)malloc(sizeof(queue));
  q->front = -1;
  q->rear = -1;
  return q;
}

int isEmptyQueue(queue *q){
  if(q->rear==-1) return 1;
  return 0;
}

void enqueue(queue *q,int value){
  if(q->rear == SIZE-1)
    printf("Queue's already full\n");
  else{
    if(q->front == -1)
      q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
  }
  return;
}

int dequeue(queue *q){
  int item;
  if(isEmptyQueue(q)==1){
    printf("Queue's empty\n");
    item = -1;
  }
  else{
    item = q->items[q->front];
    q->front++;
    if(q->front > q->rear){
      //  printf("\nresetting queue\n");
      q->front = q->rear = -1;
    }
  }
  return item;
}

void printQueue(queue *q){
  int i = q->front;
  if(isEmptyQueue(q)){
    printf("Empty queue\n");
    return;
  }
  printf("Current queue: \n");
  for(i = q->front;i<=q->rear;i++){
    printf("%d ",q->items[i]);
  }
  return;
}

void bfs(Graph g,int startVertex){
  queue *q = creatQueue();
  g.visited[startVertex] = 1;
  enqueue(q,startVertex);

  while(!isEmptyQueue(q)){
    printQueue(q);
    int currentVertex = dequeue(q);
    printf("\nVisited %d\n",currentVertex);

    int *output = (int*)malloc(sizeof(int));
    int n = getAdjacentVertices(g,currentVertex,output);

    for(int i=0;i<n;i++){
      int adjVertex = output[i];
      if(g.visited[adjVertex] == 0){
	g.visited[adjVertex] = 1;
	enqueue(q,adjVertex);
      }
    }
  }
}


#endif
