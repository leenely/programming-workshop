#define SUCCESS_CODE 0
#define NULLPOINTEREXCEPTION_ERRCODE -1
#define MEMORYALLOCATIONEXCEPTION_ERRCODE -2
#define AMPTYLISTEXCEPTION_ERRCODE -3

typedef struct node {
  struct node *link;
  int item;
} node;

typedef struct single_list {
  node *head;
} single_list;

int init_single_list(single_list *list);

int add_to_beginning(single_list *list, int number);

int add_to_end(single_list *list, int number);

int add_to_middle(single_list *list, int position, int number);

int find_element(single_list *list, int position);

int delete_last(single_list *list);

int count_elements(single_list *list);
