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
     List * local = (List *) malloc(sizeof(List));
     local->current=NULL;
     local->tail=NULL;
     local->head=NULL;
     return local;
}

void * firstList(List * list) {
    if(list->head==NULL)
      return NULL;
    list->current = list->head;
    return list->current->data;
}

void * nextList(List * list) {
    if(list->current == list->tail || list->current == NULL || list->head == NULL || list->head->next == NULL)
      return NULL;
    list->current = list->current->next;
    return list->current->data;
}

void * lastList(List * list) {
    if(list->tail->data == NULL)
      return NULL;
    list->current = list->tail;
    return list->tail->data;
}

void * prevList(List * list) {
    if(list->current == list->head || list->current == NULL || list->head == NULL)
      return NULL;
    list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) {
  Node *dato = createNode(data);
  if(list->head==NULL)
  {
    list->head = dato;
    list->tail = dato;
  }
  dato->next = list->head;
  list->head = dato;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  list->current->next = createNode(data);
  list->current->next->prev = list->current;
  list->tail = list->current->next;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    Node *copia = list->current->data;
    if(list->current == list->tail)
    {
      list->tail = list->tail->prev;
      list->current->prev = list->tail;
      list->tail->next = NULL;
    }
    else
      list->current->next->prev = list->current->prev;
  
  
    if(list->current == list->head)
    {
      list->head = list->head->next; 
      list->current->next = list->head;
      list->head->prev = NULL;
    }
    else
      list->current->prev->next = list->current->next;
    
    list->current = list->current->next;
    return copia;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}