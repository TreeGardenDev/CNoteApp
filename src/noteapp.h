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
struct node *createNode(char *data);
struct LinkedList *createLinkedList();
struct LinkedList *add_at_end(struct LinkedList *list, char *data);
struct LinkedList *add_at_beginning(struct LinkedList *list, char *data);
struct LinkedList *add_at_index(struct LinkedList *list, char *data, int index);
void print_reverse(struct LinkedList *list);
void print(struct LinkedList *list);
void print_at_index(struct LinkedList *list, int index);
struct LinkedList *delete_at_end(struct LinkedList *list);
struct LinkedList *delete_at_beginning(struct LinkedList *list);
struct LinkedList *retrieve_data_from_file();
void save_data_to_file(struct LinkedList *list);
