/* this is the header file for hashtable.c containing Binding and
hashtable abstract data types.here there are functions to 
operate on hashtable. The implimentation is hidden.
anything related to implimentation are in the header.c file.
*/
//this are the ADT used for the Hashtable and are incomplete type since no implimentation here.
struct Binding;
struct HashTable;

// this created the hashtable and returns a pointer to it.
struct HashTable* create();
// this produces a hash for a key provided and returns it.
unsigned int hash(const char* key);
/* this adds a binding with specified key and value to the hashtable provided. 
Returns a boolian based on weather it was possible to create a new binding or not.
if no binding wiht specified key exists it creates a binding and adds it to the hashtable
 and returns true.  or if the a binding with the specified key already exists it returns false.
*/
bool add(struct HashTable* table, const char* key, int value);
/* this function looks for a binding with the specified key in the hash table 
and returns it. if it was not possible it returns NULL.*/
struct Binding* find(struct HashTable* table, const char* key);
/*
This function removes a binding with key 'key' from the
HashTable. It returns true if it was able to remove/delete the
binding otherwise it returns false.*/
bool removes(struct HashTable* table, const char* key);
//This frees all dynamically allocated memory for the HashTable it also traverses the bindings and free them too.
void delete_table(struct HashTable* table);
