#include <assert.h>

/*******************************************************************/
//Data type Definition 
/*******************************************************************/
#define FIELD_NAME_MAX_SIZE 128
#define STRUCT_NAME_MAX_SIZE 128

//Defined types of fiel
typedef enum data_type_t_{
    UINT8,
    UINT32,
    INT32,
    CHAR,
    OBJ_STRUCT,
    OBJ_PTR,
    FLOAT,
    DOUBLE
}data_type_t;


//structure of record an element of the database of structures
typedef struct struct_rec_t_  struct_rec_t; 

//Structure to store the information of the field

typedef struct field_info_t_{
    char name[FIELD_NAME_MAX_SIZE];                 //name of the field
    data_type_t type;                               //type defined of the field
    unsigned int size;                              //size of the field
    unsigned int offset;                            //offset of the field
    char nested_struct_name[STRUCT_NAME_MAX_SIZE];  //pointer to struct if the field is of type nested 
} field_info_t;

struct struct_rec_t_{
    struct_rec_t *next;                     //Pointer to the next  structure  in the database records
    char struct_name[STRUCT_NAME_MAX_SIZE]; //Name of the structure record
    unsigned int size;                      //Size of the structure record
    unsigned int nb_field;                  //Number of pointed in the structure record
    field_info_t *fields;                   //Pointer to Array of fields
};

//Stucture database that points to the new inserted structure record
typedef struct struct_db_t_ {
    struct_rec_t *head;                      //Pointer to the new insted record
    unsigned int nb_rec;                    //Number of structure record
} struct_db_t;



/*******************************************************************/
//Functions Interface
/*******************************************************************/
//Utility macro to determine the size of th field


#define  SIZEOF(struct_name, fld_name)\
               sizeof(((struct_name *)0)->fld_name)

#define OFFSETOF(struct_name, fld_name)\
                (long) &(((struct_name *)0)->fld_name)

#define FIELD_INFO(struct_rec_name, fld_name, fld_type, nested_struct_name)\
        {#fld_name, fld_type, SIZEOF(struct_rec_name, fld_name),\
            OFFSETOF(struct_rec_name, fld_name), #nested_struct_name}

void print_struct_rec(struct_rec_t *struct_rec);

void print_struct_db(struct_db_t *struct_db);

//Add a structure record to structure db. returns 0 for success and -1 for failure
int add_struct_rect_to_struct_db(struct_db_t *struct_db, struct_rec_t *struct_rec);

struct_rec_t* struct_db_look_up(struct_db_t *struct_db, char *struct_name);

#define REGISTER_STRUCT(struct_db, struct_rec_name, arr_fields)                             \
    do{                                                                                     \
            struct_rec_t *struct_rec = calloc(1,sizeof(struct_rec_t));                   \
            strncpy(struct_rec->struct_name, #struct_rec_name, STRUCT_NAME_MAX_SIZE);       \
            struct_rec->size = sizeof(struct_rec_name);                                     \
            struct_rec->nb_field = sizeof(arr_fields)/sizeof(field_info_t);                 \
            struct_rec->fields = arr_fields;                                                \
            if (add_struct_rect_to_struct_db(struct_db, struct_rec)){                        \
                    assert(0);                                                              \
            }                                                                               \
    }while (0);                                                                             
    

