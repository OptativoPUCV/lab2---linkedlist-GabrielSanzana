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

/*Programe la función `void* popCurrent(List * list)`, la cual elimina el nodo que está en la posición del current de la lista enlazada, y además retorna el **dato** del nodo eliminado.
> **Nota**: El current debe quedar apuntando al nodo siguiente del eliminado.

Las funciones `pushBack`, `popFront` y `popBack` se pueden implementar usando `popCurrent` y `pushCurrent` (búsquelas en el código).
  */

void * popCurrent(List * list) {
    Node *copia = list->current;
    if(list->current == list->tail)
      list->tail = list->current->prev;
    return copia;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}