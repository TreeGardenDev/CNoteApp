#include <stdio.h>
#include <stdlib.h>

struct node {
  char *data;
  struct node *next;
  struct node *prev;
};

struct LinkedList {
  struct node *head;
  struct node *tail;
  int size;
};

struct node *createNode(char *data) {
  struct node *newNode = malloc(sizeof(struct node));
  newNode->data = data;
  newNode->next = NULL;
  newNode->prev = NULL;
  return newNode;
}

struct LinkedList *createLinkedList() {
  struct LinkedList *list = malloc(sizeof(struct LinkedList));
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
  return list;
}
struct LinkedList *add_at_end(struct LinkedList *list, char *data) {
  struct node *newNode = createNode(data);
  struct node *tail = list->tail;
  tail->next = newNode;
  list->tail = newNode;
  newNode->prev = tail;
  list->size++;
  return list;
}
struct LinkedList *add_at_beginning(struct LinkedList *list, char *data) {
  struct node *newNode = createNode(data);
if (list->head == NULL) {
    list->head = newNode;
    list->tail = newNode;
    list->size++;
    return list;
}
  struct node *head = list->head;
  
  head->prev = newNode;
  list->head = newNode;
  newNode->next = head;
  list->size++;
  return list;
}
struct LinkedList *add_at_index(struct LinkedList *list, char *data,
                                int index) {
  struct node *newNode = createNode(data);
  struct node *current = list->head;
  int i = 0;
  while (i < index) {
    current = current->next;
    i++;
  }
  struct node *prev = current->prev;
  prev->next = newNode;
  newNode->prev = prev;
  newNode->next = current;
  current->prev = newNode;
  list->size++;
  return list;
}
void print_reverse(struct LinkedList *list) {
  struct node *current = list->tail;
  while (current != NULL) {
    printf("%d\n", current->data);
    current = current->prev;
  }
}
void print(struct LinkedList *list) {
  struct node *current = list->head;
  while (current != NULL) {
    printf("%d\n", current->data);
    current = current->next;
  }
}
void print_at_index(struct LinkedList *list, int index) {
  struct node *current = list->head;
  int i = 0;
  while (i < index) {
    current = current->next;
    i++;
  }
  printf("%s\n", current->data);
}
struct LinkedList *delete_at_end(struct LinkedList *list) {
  struct node *tail = list->tail;
  struct node *prev = tail->prev;
  prev->next = NULL;
  list->tail = prev;
  free(tail);
  list->size--;
  return list;
}
struct LinkedList *delete_at_beginning(struct LinkedList *list) {
  struct node *head = list->head;
  struct node *next = head->next;
  next->prev = NULL;
  list->head = next;
  free(head);
  list->size--;
  return list;
}

struct LinkedList *retrieve_data_from_file() {
  // read from file
  FILE *fp;
  fp = fopen("data.txt", "r");
  int length;
  length = fscanf(fp, "%d", &length);
   
  for (int i = 1; i < length; i++) {
    char *data;
    fscanf(fp, "%s", &data);
    // add to linked list
    struct node *newNode = createNode(data);
  }
}
void save_data_to_file(struct LinkedList *list) {
  // write to file
  FILE *fp;
  fp = fopen("data.txt", "w");
  // erase previous data
  fprintf(fp, "%s", "");
  fprintf(fp, "%d\n", list->size);
  struct node *current = list->head;
  while (current != NULL) {
    fprintf(fp, "%s\n", current->data);
    current = current->next;
  }
}

int main() {
    struct LinkedList *list = createLinkedList();
    list= add_at_beginning(list, "Head");
    list= add_at_end(list, "Taily");
    list= add_at_index(list, "Index", 1);

    save_data_to_file(list);


  return 0;
}
