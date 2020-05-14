#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mld.h"
#include "css.h"

char *DATA_TYPE[] = {"UINT8", "UINT32", "INT32",
                     "CHAR", "OBJ_PTR", "FLOAT",
                     "DOUBLE", "OBJ_STRUCT"};

/* Dumping Function */

void print_struct_rec(struct_rec_t *struct_rec){
    if(!struct_rec) return;
    int j = 0;
    field_info_t *field = NULL;
    printf(ANSI_COLOR_CYAN "|------------------------------------------------------|\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_YELLOW "| %-20s | size = %-8d | #flds = %-3d |\n" ANSI_COLOR_RESET, struct_rec->struct_name, struct_rec->size, struct_rec->nb_field);
    printf(ANSI_COLOR_CYAN "|------------------------------------------------------|------------------------------------------------------------------------------------------|\n" ANSI_COLOR_RESET);
    for(j = 0; j < struct_rec->nb_field; j++){
        field = &struct_rec->fields[j];
        printf("  %-20s |", "");
        printf("%-3d %-20s | dtype = %-15s | size = %-5d | offset = %-6d|  nstructname = %-20s  |\n",
                j, field->name, DATA_TYPE[field->type], field->size, field->offset, field->nested_struct_name);
        printf("  %-20s |", "");
        printf(ANSI_COLOR_CYAN "--------------------------------------------------------------------------------------------------------------------------|\n" ANSI_COLOR_RESET);
    }
}

void print_struct_db(struct_db_t *struct_db){
    
    if(!struct_db) return;
    printf("printing structure db\n");
    int i = 0;
    struct_rec_t *struct_rec = NULL;
    struct_rec = struct_db->head;
    printf("No of Structures Registered = %d\n", struct_db->nb_rec);
    while(struct_rec){
        printf("structure No : %d (%p)\n", i++, struct_rec);
        print_struct_rec(struct_rec);
        struct_rec = struct_rec->next;
    }
}


//Add a structure record to structure db. returns 1 for success and 0 for failure
int add_struct_rect_to_struct_db(struct_db_t *struct_db, 
                                    struct_rec_t *struct_rec){

    struct_rec_t *head = struct_db->head;

    if(!head){
        struct_db->head = struct_rec;
        struct_rec->next = NULL;
        struct_db->nb_rec++;
        return 0;
    }
    struct_rec->next = head;
    struct_db->head = struct_rec;
    struct_db->nb_rec++;
    return 0;
}

struct_rec_t* struct_db_look_up(struct_db_t *struct_db, char *struct_name){
    struct_rec_t *current  = struct_db->head;

    if(!struct_db){
        return NULL;
    }

    while(current){
        if(strcmp(current->struct_name, struct_name)==0 ){
            return current;
        }
        current = current->next;
    }

    return current;
}

