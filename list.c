#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {

  List * new = (List *)malloc(sizeof(List));
  return new;
  
}

void * firstList(List * list) {
  if(list->head == NULL) return NULL;
  list->current = list->head;
  return list->head->data;

}

void * nextList(List * list) {
  if(list->current == NULL) return NULL;
  if(list->current->next == NULL) return NULL;
  
  list->current = list->current->next;
  return list->current->data;
 
}

void * lastList(List * list) {
  if(list->tail == NULL) return NULL;
  list->current = list->tail;
  return list->tail->data;
   
}

void * prevList(List * list) {
  if(list->current == NULL) return NULL;
  if(list->current->prev == NULL) return NULL;
  list->current = list->current->prev;
  return list->current->data;   
}

void pushFront(List * list, void * data) {
  Node * new = createNode(data);
  if(list->head == NULL){
    list->head = new;
    list->tail = new;
  }
  else
  {
    new->next = list->head;
    list->head->prev = new;
    list->head = new;
  }
  
}


void pushBack(List * list, void * data) {
  list->current = list->tail;
  Node * new = createNode(data);
  if(list->tail == NULL){
    list->head = new;
    list->tail = new;
    
  }
  else{
    new->prev = list->tail;
    list->tail->next = new;
    list->tail = new;
  }
}



void pushCurrent(List * list, void * data) {
  if(list->current == NULL) return;
  Node * new = createNode(data);
  if(list->current->next == NULL){
    new->prev = list->current;
    list->current->next = new;
    list->tail = new;
  }
  else{
    new->prev = list->current;
    new->next = list->current->next;
    list->current->next->prev = new;
    list->current->next = new;
  }
}


void * popFront(List * list) {
  if(list->head == NULL) return NULL;
  list->current = list->head;
  Node * aux = list->head;
  list->head = list->head->next;
  if(list->head == NULL) list->tail = NULL;
  else list->head->prev = NULL;
  void * data = aux->data;
  free(aux);
  return data;

  
}

void * popBack(List * list) {
  if(list->tail == NULL) return NULL;
  list->current = list->tail;
  Node * aux = list->tail;
  list->tail = list->tail->prev;
  if(list->tail == NULL) list->head = NULL;
  else list->tail->next = NULL;
  void * data = aux->data;
  free(aux);
  return data;
  
}

void * popCurrent(List * list) {
  if(list->current == NULL) return NULL;
  list->current = list->current->next;
  Node * aux = list->current;
  list->current->prev->next = list->current->next;
  if(list->current->next == NULL) list->tail = list->current->prev;
  else list->current->next->prev = list->current->prev;
  void * data = aux->data;
  free(aux);
  return data;
  
}

void cleanList(List * list) {
  while(list->head != NULL){
    
    popFront(list);
  }
  
}