#include <stdio.h>
#include "InterP.h"

// 先把整体流程弄完了
int main(int argc, char **argv)
{


    struct MyInterpreter  *interpreter;
    FILE *fp;

    if (argc != 2) {
        fprintf(stderr, "usage:%s filename", argv[0]);
        exit(1);
    };
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        fprintf(stderr, "%s not found.\n", argv[1]);
        exit(1);
    }
    interpreter = CRB_create_interpreter();
    CRB_compile(interpreter, fp);
    CRB_interpret(interpreter);
    CRB_dispose_interpreter(interpreter);
//    MEM_dump_blocks(stdout);
    return 0;
}


