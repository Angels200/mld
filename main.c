#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stddef.h>

#define MAX_STRUCTURE_NAME_SIZE 128
#define MAX_FIELD_NAME_SIZE 128

/*
(struct name *)0 is casting 0 to pointer to struct name.
&((struct name *)0)->member) is getting the address of member member.
(char *) &((struct name *)0)->member) is casting that address to char *

The idea is that if a is a structure of type A then &a.b is equal to the address of a plus the offset of b in a. 
Since here NULL is used instead of the address of a, the result is just the offset of b in structures of type A.

The expression (unsigned int) & ( (struct name *)0 )->b)) calculates offset of b in struct name as described above 
and casts the result to an integer. The result should be equal to sizeof(long) on most platforms.
*/

#define OFFSETOF(struct_name, fld_name)     \
    (long)&(((struct_name *)0)->fld_name)

#define SIZEOF(struct_name, fld_name) \
    (long) sizeof(((struct_name *)0)->fld_name)

#define STRINGIZE(var) #var

#define FIELDINFO(struct_name, fld_name, dtype, size,offset) \
    {#fld_name, dtype, SIZEOF(struct_name, fld_name), OFFSETOF(struct_name, fld_name)}

typedef enum data_type_{
    UINT8,
    UINT32,
    INT32,
    CHAR,
    OBJ_PTR,
    FLOAT,
    DOUBLE,
    OBJ_STRUCT
} dtype_t;

typedef struct field_info_t{
    char fname[MAX_FIELD_NAME_SIZE];
    dtype_t dtype;
    unsigned int size;
    unsigned int offset;
} fi_t;


typedef struct emp_ {
    unsigned int emp_id;
    char emp_name[30];
    unsigned int age;
    struct emp_ *mgr;
    float salary;
} emp_t;

typedef struct data_rec_{
    char name[20];
    unsigned int n_field;
    fi_t *fields;
} dr_t;

int main(){

}

/*
int main(){
    
    emp_t emps;
    dr_t drs;

    printf("%s\n",STRINGIZE(emp_name));

    fi_t fields[]={
        
    };

    fi_t fields[5];
    fields[0].size = SIZEOF(emp_t, emp_name);
    fields[0].offset = OFFSET(emp_t, emp_name);

    fields[1].size = SIZEOF(emp_t, emp_id);
    fields[1].offset =  offsetof(emp_t, emp_id);  //OFFSET(emp_t, emp_id);

    fields[2].size = SIZEOF(emp_t, age);
    fields[2].offset = OFFSET(emp_t, age);
    

    fields[3].size = SIZEOF(emp_t, mgr);
    fields[3].offset = OFFSET(emp_t, mgr);

    fields[4].size = SIZEOF(emp_t, salary);
    fields[4].offset = OFFSET(emp_t, salary);;

    drs.fields = fields;
    drs.n_field = 5;
    strcpy(drs.name, "emp_t\0");

    for(int i=0; i<5; i++){
        printf("Record %s has %u fields\n", drs.name, drs.n_field);
        printf("Size of field %u : %u\n", i, drs.fields[i].size);
        printf("Offset of field %u : %u\n", i, drs.fields[i].offset);
    }
    
}
*/