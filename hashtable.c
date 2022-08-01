//#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hashHeader.h"
#include<assert.h>

// here constants for declaring the hash table and an intiger used for hashing is defined.
#define BUCKET_COUNT 1024
#define FOR_HASHING 112233

// this is the ADT binding declaration for holding the elements to be in the hashtable.
struct Binding
{
    const char *key;
    int value;
    struct Binding *next;
};


// this is the ADT HashTable declaration which conatains an array of pointer to bindings.
struct HashTable
{
    struct Binding* buckets[BUCKET_COUNT];
};


// This function creates and initializes a HashTable and return it.
struct HashTable *create()
{
    struct HashTable* table = (struct HashTable*) malloc(sizeof(struct HashTable));
    return table;
};


// This function hashes the key and returns an integer mod BUCKET_COUNT
unsigned int hash(const char *key)
{   
    return ((sizeof(key)*FOR_HASHING) % BUCKET_COUNT);
};

/*
This function associates the value 'value' using the key 'key'. considering
two cases as described below
Case I: The key does not already exists in the HashTable. in this case the
↪fuction creates a struct Binding with key 'key' and value 'value', hash the key
↪ and insert the binding into the table using the hash value of the key.
↪ The function then returns true.
Case II: The key already exists in the HashTable. if this is the case the fuction updates
↪ the Bindings old value to the new supplied 'value' and returns false.
*/

bool add(struct HashTable *table, const char *key, int value)
{
    int hashIndex = hash(key);
    //this checks weather binding exists with the has value of the element to be inserted.
    if (table->buckets[hashIndex] == NULL)
    {   
        struct Binding* toInsert = (struct Binding*) malloc(sizeof(struct Binding));
        toInsert->key= key;
        toInsert->value=value;
        toInsert->next=NULL;
        table->buckets[hashIndex] = toInsert;
        return true;
    }
    else // if binding exists with the hashvalue of the key this searches if a binding exists with the specified key in the linked list.
    {   
        struct Binding *search = table->buckets[hashIndex];
        while (search != NULL)
        {
            if (strcmp(search->key, key) == 0)
            {
                search->value = value;
                return false;
            }
            search = search->next;
        }
        // finally if a binding with the key is not found we add a binding at the begining of the linked list.
        struct Binding* added = (struct Binding*) malloc(sizeof(struct Binding));
        added->key = key; 
        added->value = value; 
        added->next = table->buckets[hashIndex];
        table->buckets[hashIndex] = added;
        return true;
    }
};

/**
* This function searchs for the key 'key' in the HashTable and returns
↪ the Binding if it finds one with the key. Otherwise it returns
↪ null.
*/

struct Binding *find(struct HashTable *table, const char *key)
{
    int hashIndex = hash(key);
    struct Binding *search = table->buckets[hashIndex];
    while (search != NULL)
    {
        if (strcmp(search->key, key) == 0)
        {
            return search;
        }
        search = search->next;
    }
    return NULL;
};

/**
* This function removes a binding with key 'key' from the
↪ HashTable. It returns true if it was able to remove/delete the
↪ binding otherwise it returns false.
Hint: Be sure not to leak any dynamically allocated memory for the deleted
↪ binding, you should remember to free any dynamically allocated memory
↪ for the binding.
*/

bool remove(struct HashTable *table, const char *key)
{
    int hashindex = hash(key);
    struct Binding *search;
    search = table->buckets[hashindex];

    if (search == NULL)

        return false;

    if (strcmp(search->key, key)==0)
    {
        table->buckets[hashindex] = table->buckets[hashindex]->next;
        free(search);
        return true;
    }

    while (search->next != NULL) 
    {
        if (strcmp(search->next->key, key) == 0)
        {   struct Binding* temp = search->next;
            search->next = search->next->next;
            free(temp);
            return true;
        }
        search = search->next;
    }
    
    return false;
};
/**
* This frees all dynamically allocated memory for the HashTable it also traverses the bindings and free them too.
*/
void delete_table(struct HashTable *table)
{
    struct Binding* delete;

    for (size_t i = 0; i < BUCKET_COUNT; i++)
    {
        while (table->buckets[i] != NULL)
        {
            delete = table->buckets[i];
            table->buckets[i] = table->buckets[i]->next;
            free(delete);
        }
    }
    free(table);
};