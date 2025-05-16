#include "hashtable.h"
#include "pool_alloc.h"
#include <stdlib.h>
#include <string.h>

unsigned int MurmurHash2(const char *key, unsigned int len) {
  const unsigned int m = 0x5bd1e995;
  const unsigned int seed = 0;
  const int r = 24;

  unsigned int h = seed ^ len;
  const unsigned char *data = (const unsigned char *)key;
  unsigned int k = 0;

  while (len >= 4) {
    k = data[0];
    k |= data[1] << 8;
    k |= data[2] << 16;
    k |= data[3] << 24;

    k *= m;
    k ^= k >> r;
    k *= m;

    h *= m;
    h ^= k;

    data += 4;
    len -= 4;
  }

  switch (len) {
  case 3:
    h ^= data[2] << 16;
  case 2:
    h ^= data[1] << 8;
  case 1:
    h ^= data[0];
    h *= m;
  };

  h ^= h >> 13;
  h *= m;
  h ^= h >> 15;

  return h;
}

void hashtable_init(HashTable *table, size_t capacity, PoolAllocator *allocator,
                    size_t size_of_value) {
  table->capacity = capacity;
  table->allocator = allocator;
  table->buckets = calloc(capacity, sizeof(HashElem *));
  table->size_of_value = size_of_value;
}

void hashtable_insert(HashTable *table, const char *key, void *value) {
  unsigned int hash = MurmurHash2(key, strlen(key));
  size_t index = hash % table->capacity;

  HashElem *elem = table->buckets[index];
  while (elem != NULL) {
    if (elem->key == key) {
      memcpy(elem->value, value, table->size_of_value);
      return;
    }
    elem = elem->next;
  }

  HashElem *new_elem = pool_alloc(table->allocator);
  new_elem->key = key;
  new_elem->value = value;
  new_elem->next = table->buckets[index];
  table->buckets[index] = new_elem;
}

void *hashtable_get(HashTable *table, const char *key) {
  unsigned int hash = MurmurHash2(key, strlen(key));
  size_t index = hash % table->capacity;

  HashElem *elem = table->buckets[index];
  while (elem != NULL) {
    if (elem->key == key) {
      return elem->value;
    }
    elem = elem->next;
  }
  return NULL;
}

void hashtable_del(HashTable *table, const char *key) {
  unsigned int hash = MurmurHash2(key, strlen(key));
  size_t index = hash % table->capacity;

  HashElem *prev = NULL;
  HashElem *elem = table->buckets[index];

  while (elem != NULL) {
    if (elem->key == key) {
      if (prev == NULL) {
        table->buckets[index] = elem->next;
      } else {
        prev->next = elem->next;
      }
      pool_free(table->allocator, elem);
      return;
    }
    prev = elem;
    elem = elem->next;
  }
}

void hashtable_free(HashTable *table) {
  for (size_t i = 0; i < table->capacity; i++) {
    HashElem *elem = table->buckets[i];
    while (elem != NULL) {
      HashElem *next = elem->next;
      pool_free(table->allocator, elem);
      elem = next;
    }
  }
  free(table->buckets);
  table->allocator = NULL;
  table->buckets = NULL;
  table->capacity = 0;
  table->size_of_value = 0;
}
