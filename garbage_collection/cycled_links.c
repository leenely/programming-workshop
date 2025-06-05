#include "cycled_links.h"
#include <stdlib.h>

void init_object_system(Object_system *os, int initial_capacity) {
  os->objects = (Object **)malloc(initial_capacity * sizeof(Object *));
  os->object_count = 0;
  os->capacity = initial_capacity;
}

void deinit_object_system(Object_system *os) {
  for (int i = 0; i < os->object_count; i++) {
    if (os->objects[i] != NULL) {
      deinit_object(os->objects[i]);
    }
  }
  os->capacity = 0;
  os->object_count = 0;
  free(os->objects);
}

void set_link(Object *from, Object *to) {
  from->link = to;
  from->is_used = true;
  to->is_used = true;
}

void detect_cycles(Object_system *os) {
  for (int i = 0; i < os->object_count; i++) {
    if (os->objects[i] != NULL && os->objects[i]->link != NULL) {
      if (os->objects[i]->link->link == os->objects[i]) {
        os->objects[i]->is_used = false;
        os->objects[i]->link->is_used = false;
      }
    }
  }
}

void cycles_collect(Object_system *os) {
  int copy_object_count = os->object_count;
  for (int i = 0; i < copy_object_count; i++) {
    if (os->objects[i] != NULL && !(os->objects[i]->is_used)) {
      free(os->objects[i]);
      os->objects[i] = os->objects[os->object_count - 1];
      os->object_count--;
    }
  }
}

Object *init_object(Object_system *os, int id) {
  if (os->object_count >= os->capacity) {
    os->capacity *= 2;
    os->objects =
        (Object **)realloc(os->objects, os->capacity * sizeof(Object *));
  }

  Object *obj = (Object *)malloc(sizeof(Object));
  obj->id = id;
  obj->link = NULL;
  obj->is_used = true;
  add_object(os, obj);
  return obj;
}

void deinit_object(Object *obj) {
  obj->id = 0;
  obj->is_used = false;
  obj->link = NULL;
  free(obj);
}

void add_object(Object_system *os, Object *obj) {
  if (os->object_count >= os->capacity) {
    os->capacity *= 2;
    os->objects =
        (Object **)realloc(os->objects, os->capacity * sizeof(Object *));
  }
  obj->is_used = true;
  os->objects[os->object_count++] = obj;
}
