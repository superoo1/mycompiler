//
// Created by 李文达 on 2020/4/12.
//

#include "interface.h"



static CRB_Interpreter *st_current_interpreter;
static char *st_string_literal_buffer = NULL;
static int st_string_literal_buffer_size = 0;
static int st_string_literal_buffer_alloc_size = 0;


CRB_Interpreter *
crb_get_current_interpreter(void)
{
    return st_current_interpreter;
}

void
crb_set_current_interpreter(CRB_Interpreter *inter)
{
    st_current_interpreter = inter;
}



MyInterpreter CRB_create_interpreter(){

    CRB_Interpreter *interpreter;
//
//    interpreter = MEM_storage_malloc(storage,
//                                     sizeof(struct CRB_Interpreter_tag));
//    interpreter->interpreter_storage = storage;
//    interpreter->execute_storage = NULL;
    interpreter->variable = NULL;
//    interpreter->function_list = NULL;
//    interpreter->statement_list = NULL;
    interpreter->current_line_number = 1;
    crb_set_current_interpreter(interpreter);
//    就放一个内置函数
//    add_native_functions(interpreter);

    return interpreter;
};



// todo  内置函数待会做
//void CRB_add_native_function(CRB_Interpreter *interpreter,
//                        char *name, CRB_NativeFunctionProc *proc)
//{
//    FunctionDefinition *fd;
//
////    fd = crb_malloc(sizeof(FunctionDefinition));
//    fd->name = name;
//    fd->type = NATIVE_FUNCTION_DEFINITION;
//    fd->u.native_f.proc = proc;
//    fd->next = interpreter->function_list;
//
//    interpreter->function_list = fd;
//}
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
CRB_interpret(CRB_Interpreter *interpreter)
{
//    interpreter->execute_storage = MEM_open_storage(0);
    crb_add_std_fp(interpreter);
    crb_execute_statement_list(interpreter, NULL, interpreter->statement_list);
}