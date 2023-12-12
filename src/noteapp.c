#include "noteapp.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  struct LinkedList *list = retrieve_data_from_file();
  struct node *current = list->head;
  if (current == NULL) {
    printf("List is empty\n");
    return 0;
  }

//infinite loop until user exits
    char *input = malloc(sizeof(char));
    int i = 0;
        //add strings for functions like reverse, delete, etc
        char *reverse = "reverse";
        char *delete = "delete";
        char *add = "add";
        char *print = "print";
    while(1){
        input = realloc(input, sizeof(char) * (i + 1));
        input[i] = getchar();
        i++;
        if (input[i] == '\n'){
            list = add_at_end(list, input);
            break;
        }
    }
    for (int i = 0; i < list->size; i++) {
      print_at_index(list, i);
    }
   save_data_to_file(list);

  return 0;
}
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
  FILE *fp;
  char c;
  int count = 0;
  fp = fopen("out/data.txt", "r");

  if (fp == NULL) {
    printf("Could not open file data.txt");
    return 0;
  }

  char **data = malloc(sizeof(char *));
  char *line = malloc(sizeof(char));
  int i = 0;

  for (c = getc(fp); c != EOF; c = getc(fp)) {
    line = realloc(line, sizeof(char) * (i + 1));

    if (count > 0 && c != '\n') {
      line[i] = c;
      i++;
    }
    if (c == '\n') { // Increment count if this character is newline
      if (count > 0) {
        i = 0;
        data = realloc(data, sizeof(char *) * (count + 1));
        data[count] = line;
        line = malloc(sizeof(char));
      }
      count++;
    }
  }

  fclose(fp);
  struct LinkedList *list = createLinkedList();
  for (int i = 1; i < count; i++) {

    struct node *newNode = createNode(data[i]);
    if (list->head == NULL) {
      list->head = newNode;
      list->tail = newNode;
      list->size++;
    } else {
      struct node *tail = list->tail;
      tail->next = newNode;
      list->tail = newNode;
      newNode->prev = tail;
      list->size++;
    }
  }

  return list;
}
void save_data_to_file(struct LinkedList *list) {
  // write to file
  FILE *fp;
  fp = fopen("out/data.txt", "w");
  // erase previous data
  fprintf(fp, "%s", "");
  fprintf(fp, "%d\n", list->size);
  struct node *current = list->head;
  while (current != NULL) {
    fprintf(fp, "%s\n", current->data);
    current = current->next;
  }
}
