
#include <stdio.h>

#include <string.h>



#include "object.h"

#include "memory.h"
#include "value.h"

void ValueArray :: initValueArray() {
    this->values = NULL;
    this->capacity = 0;
    this->count = 0;
}

void ValueArray :: writeValueArray(Value value) {
    if (this->capacity < this->count + 1) {
        int oldCapacity = this->capacity;
        this->capacity = GROW_CAPACITY(oldCapacity);
        this->values = GROW_ARRAY(Value, this->values,
            oldCapacity, this->capacity);
    }

    this->values[this->count] = value;
    this->count++;
}

void ValueArray :: freeValueArray() {
    FREE_ARRAY(Value, this->values, this->capacity);
    initValueArray();
}

void printValue(Value value) {

#ifdef NAN_BOXING
    if (IS_BOOL(value)) {
        printf(AS_BOOL(value) ? "true" : "false");
    }
    else if (IS_NIL(value)) {
        printf("nil");
    }
    else if (IS_NUMBER(value)) {
        printf("%g", AS_NUMBER(value));
    }
    else if (IS_OBJ(value)) {
        printObject(value);
    }
#else

    switch (value.type) {
    case VAL_BOOL:
        printf(AS_BOOL(value) ? "true" : "false");
        break;
    case VAL_NIL: printf("nil"); break;
    case VAL_NUMBER: printf("%g", AS_NUMBER(value)); break;
        
    case VAL_OBJ: printObject(value); break;
        
    }
    
#endif

}

bool valuesEqual(Value a, Value b) {
  
#ifdef NAN_BOXING

    if (IS_NUMBER(a) && IS_NUMBER(b)) {
        return AS_NUMBER(a) == AS_NUMBER(b);
    }
  
    return a == b;
#else

    if (a.type != b.type) return false;
    switch (a.type) {
    case VAL_BOOL:   return AS_BOOL(a) == AS_BOOL(b);
    case VAL_NIL:    return true;
    case VAL_NUMBER: return AS_NUMBER(a) == AS_NUMBER(b);
        
    case VAL_OBJ:    return AS_OBJ(a) == AS_OBJ(b);
        
    default:         return false;
    }
    
#endif

}

