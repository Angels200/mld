#include "mld.h"
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

//Application Data structures

typedef struct emp_t_ emp_t;

struct emp_t_{
    char name[30];
    unsigned int emp_id;
    unsigned int age;
    emp_t *mng;
    float salary;

};

typedef struct student_t_ student_t;
struct student_t_{
    char name[30];
    unsigned int rollno;
    unsigned int age;
    float aggregate;
    student_t *best_collegue;
};

int main(int argc, char **argv){

    //Database structure creation and registration
    struct_db_t *struc_db = calloc(1,sizeof(struct_db_t)); 
    //return 0;
    
    static field_info_t emp_fields[] = {
        FIELD_INFO(emp_t,name,CHAR,0),
        FIELD_INFO(emp_t,emp_id,UINT32,0),
        FIELD_INFO(emp_t,age, UINT32,0),
        FIELD_INFO(emp_t,mng, OBJ_PTR,emp_t),
        FIELD_INFO(emp_t,salary,FLOAT,0)
    };

    REGISTER_STRUCT(struc_db, emp_t,emp_fields);

    static field_info_t stud_fields[]={
        FIELD_INFO(student_t, name, CHAR, 0),
        FIELD_INFO(student_t, rollno, UINT32, 0),
        FIELD_INFO(student_t, age, UINT32, 0),
        FIELD_INFO(student_t,aggregate, FLOAT,0),
        FIELD_INFO(student_t,best_collegue,OBJ_PTR,student_t)
    };

    REGISTER_STRUCT(struc_db, student_t, stud_fields);

    //return 0;

    print_struct_db(struc_db);

    struct_rec_t *search = struct_db_look_up(struc_db, "student_t");

    printf("|--------------|%s\n","");
    printf("|%-20s\n",search->struct_name);
    printf("|--------------|%s\n","");

    struct_rec_t *current = struc_db->head;
    struct_rec_t *next;
    while(current){
        next = current->next;
        free(current);
        current = next;
    }

    free(struc_db);
    return 0;
    
}