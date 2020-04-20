//
// Created by 李文达 on 2020/4/8.
//
#include <stdio.h>
#include <string.h>
#define STRING_ALLOC_SIZE       (256)



char * crb_create_identifier(char *str)
{
    char *new_str;
    strcpy(new_str, str);

    return new_str;
}


static char *st_string_literal_buffer = NULL;
static int st_string_literal_buffer_size = 0;
static int st_string_literal_buffer_alloc_size = 0;


void
crb_add_string_literal(int letter)
{
    if (st_string_literal_buffer_size == st_string_literal_buffer_alloc_size) {
        st_string_literal_buffer_alloc_size += STRING_ALLOC_SIZE;

    }
    st_string_literal_buffer[st_string_literal_buffer_size] = letter;
    st_string_literal_buffer_size++;
}

void crb_reset_string_literal_buffer(void)
{
    st_string_literal_buffer = NULL;
    st_string_literal_buffer_size = 0;
    st_string_literal_buffer_alloc_size = 0;
}

char *
crb_close_string_literal(void)
{
    char *new_str;


    memcpy(new_str, st_string_literal_buffer, st_string_literal_buffer_size);
    new_str[st_string_literal_buffer_size] = '\0';

    return new_str;
}







