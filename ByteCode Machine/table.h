#ifndef clox_table_h
#define clox_table_h

#include "common.h"
#include "value.h"

typedef struct {
    ObjString* key;
    Value value;
} Entry;

class Table {
    int count;
    int capacity;
    Entry* entries;
public :
    void initTable();
    
    void freeTable();
    bool tableGet(ObjString* key, Value* value);
    bool tableSet( ObjString* key, Value value);
    bool tableDelete( ObjString* key);
    void tableAddAll(Table* to);
    ObjString* tableFindString(const char* chars, int length, uint32_t hash);
    void tableRemoveWhite();
    void markTable();
private : void adjustCapacity(int capacity);



};
#endif