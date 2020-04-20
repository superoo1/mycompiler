//
// Created by 李文达 on 2020/4/2.
//

#ifndef UNTITLED3_INTERP_H
#define UNTITLED3_INTERP_H

#endif //UNTITLED3_INTERP_H

// todo 先搞字符串 跟数字 布尔，等逻辑走通了  再搞函数跟指针  内存回收

typedef struct MEM_Storage_tag *MEM_Storage;


typedef enum {
    CRB_FALSE = 0,
    CRB_TRUE = 1
} CRB_Boolean;


typedef struct River_String_tag CRB_String;



typedef enum {
    CRB_BOOLEAN_VALUE = 1,
    CRB_INT_VALUE,
    CRB_DOUBLE_VALUE,
    CRB_STRING_VALUE,
    CRB_NATIVE_POINTER_VALUE,      # 原生指针
    CRB_NULL_VALUE
} CRB_ValueType;


typedef struct {
    CRB_ValueType type;
    union {
        CRB_Boolean boolean_value;
        int int_value;
        double double_value;
        CRB_String *string_value;
    } u;
} CRB_Value;


typedef struct Variable_tag {
    char *name;
    CRB_Value value;
    struct Variable_tag *next;
} Variable;





struct Interpreter_tag {
//    MEM_Storage inter_storage;
//    MEM_Storage exe_storage;
    Variable *variable;
//    FunctionDefinition *function_list;
//    StatementList *state_list;
    int current_line_num;
};


typedef  struct Interpreter_tag  MyInterpreter;







MyInterpreter *CRB_create_interpreter(void);

void
CRB_compile(CRB_Interpreter *interpreter, FILE *fp)
{
    extern int yyparse(void);
    extern FILE *yyin;

    crb_set_current_interpreter(interpreter);

    yyin = fp;
    if (yyparse()) {
        /* BUGBUG */
        fprintf(stderr, "Error ! Error ! Error !\n");
        exit(1);
    }
    crb_reset_string_literal_buffer();
}

void
crb_reset_string_literal_buffer(void)
{
//    MEM_free(st_string_literal_buffer);
    st_string_literal_buffer = NULL;
    st_string_literal_buffer_size = 0;
    st_string_literal_buffer_alloc_size = 0;
}

void
crb_add_std_fp(CRB_Interpreter *inter)
{
    CRB_Value fp_value;

    fp_value.type = CRB_NATIVE_POINTER_VALUE;
    fp_value.u.native_pointer.info = &st_native_lib_info;

    fp_value.u.native_pointer.pointer = stdin;
    CRB_add_global_variable(inter, "STDIN", &fp_value);

    fp_value.u.native_pointer.pointer = stdout;
    CRB_add_global_variable(inter, "STDOUT", &fp_value);

    fp_value.u.native_pointer.pointer = stderr;
    CRB_add_global_variable(inter, "STDERR", &fp_value);
}


void
CRB_interpret(CRB_Interpreter *interpreter)
{
//    interpreter->execute_storage = MEM_open_storage(0);
    crb_add_std_fp(interpreter);
    crb_execute_statement_list(interpreter, NULL, interpreter->statement_list);
}



// 生成分析书  表达式评估





static void
release_global_strings(CRB_Interpreter *interpreter) {
    while (interpreter->variable) {
        Variable *temp = interpreter->variable;
        interpreter->variable = temp->next;
        if (temp->value.type == CRB_STRING_VALUE) {
            crb_release_string(temp->value.u.string_value);
        }
    }
}

void
CRB_dispose_interpreter(CRB_Interpreter *interpreter)
{
    release_global_strings(interpreter);

    if (interpreter->execute_storage) {
        MEM_dispose_storage(interpreter->execute_storage);
    }

    MEM_dispose_storage(interpreter->interpreter_storage);
}

// 每天一点点努力 能让生活更好一点点  那就努力一点点 ， 加油







