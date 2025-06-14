#define HASHTABLE_H
#include <stddef.h>

typedef struct HashElem HashElem;
typedef struct HashTable HashTable;

struct HashElem {
  char const *key;
  void *value;
  HashElem *next;
};

struct HashTable {
  size_t capacity;
  size_t size_of_value;
  HashElem **buckets;
  struct PoolAllocator *allocator;
};

unsigned int MurmurHash2(const char *key, unsigned int len);
void hashtable_init(HashTable *table, size_t capacity,
                    struct PoolAllocator *allocator, size_t size_of_value);
void hashtable_insert(HashTable *table, const char *key, void *value);
void *hashtable_get(HashTable *table, const char *key);
void hashtable_del(HashTable *table, const char *key);
void hashtable_free(HashTable *table);
