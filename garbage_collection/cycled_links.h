#include <stdbool.h>

typedef struct Object {
  int id;
  struct Object *link;
  bool is_used;
} Object;

typedef struct Object_system {
  Object **objects;
  int object_count;
  int capacity;
} Object_system;

void init_object_system(Object_system *os, int initial_capacity);

Object *init_object(Object_system *os, int id);

void add_object(Object_system *os, Object *obj);

void deinit_object(Object *obj);

void set_link(Object *from, Object *to);

void detect_cycles(Object_system *os);

void cycles_collect(Object_system *os);

void deinit_object_system(Object_system *os);
