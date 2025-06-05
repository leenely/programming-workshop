// Обнаружение циклических ссылок
#include "../cycled_links.h"
#include <assert.h>

void test1() {
  Object_system os;
  init_object_system(&os, 3);

  Object *obj1 = init_object(&os, 1);
  Object *obj2 = init_object(&os, 2);
  Object *obj3 = init_object(&os, 3);
  Object *obj4 = init_object(&os, 4);
  Object *obj5 = init_object(&os, 5);

  set_link(obj1, obj4);
  set_link(obj4, obj1);
  set_link(obj2, obj3);
  set_link(obj3, obj5);

  assert(os.object_count == 5);

  detect_cycles(&os);
  cycles_collect(&os);

  assert(os.object_count == 3);

  deinit_object_system(&os);
}

void test2() {
  Object_system os;
  init_object_system(&os, 3);

  Object *obj1 = init_object(&os, 1);
  Object *obj2 = init_object(&os, 2);
  Object *obj3 = init_object(&os, 3);
  Object *obj4 = init_object(&os, 4);
  Object *obj5 = init_object(&os, 5);
  Object *obj6 = init_object(&os, 6);
  Object *obj7 = init_object(&os, 7);
  Object *obj8 = init_object(&os, 8);

  set_link(obj1, obj3);
  set_link(obj3, obj6);
  set_link(obj6, obj5);
  set_link(obj2, obj8);
  set_link(obj8, obj2);
  set_link(obj4, obj7);
  set_link(obj7, obj4);

  assert(os.object_count == 8);

  detect_cycles(&os);
  cycles_collect(&os);

  assert(os.object_count == 4);

  deinit_object_system(&os);
}

int main() {
  test1();
  test2();
  return 0;
}
