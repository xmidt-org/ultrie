/*
 * Copyright 2019 Comcast Cable Communications Management, LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>

#include "ultrie.h"
#include "internal.h"

/*----------------------------------------------------------------------------*/
/*                                   Macros                                   */
/*----------------------------------------------------------------------------*/
/* none */

/*----------------------------------------------------------------------------*/
/*                               Data Structures                              */
/*----------------------------------------------------------------------------*/
/* none */

/*----------------------------------------------------------------------------*/
/*                            File Scoped Variables                           */
/*----------------------------------------------------------------------------*/
/* none */

/*----------------------------------------------------------------------------*/
/*                             Function Prototypes                            */
/*----------------------------------------------------------------------------*/
static void __print_node( struct ultrie *u );
static void __print_all_nodes( struct ultrie *u );

/*----------------------------------------------------------------------------*/
/*                             External Functions                             */
/*----------------------------------------------------------------------------*/

/* See ultrie.h for details. */
void ultrie_print( ultrie_t _u )
{
    struct ultrie *u = (struct ultrie*) _u;

    printf( "\n\ndigraph structs {\n    node [shape=record];\n" );
    __print_all_nodes( u );
    printf( "}\n\n" );
}


/*----------------------------------------------------------------------------*/
/*                             Internal functions                             */
/*----------------------------------------------------------------------------*/

/**
 *  Print out the individual node in graphviz dot notation.
 */
static void __print_node( struct ultrie *u )
{
    if( NULL == u->value ) {
        printf( "struct%p [label=\"{<p> string | token | value | child | next } | { '%s' | %s |  | <child> %s | <next> %s }\"];\n",
                (void*) u, u->string, ((0 == u->token) ? "false" : "true"),
                ((NULL == u->child) ? "NULL" : " "),
                ((NULL == u->next) ? "NULL" : " ") );
    } else {
        printf( "struct%p [label=\"{<p> string | token | value | child | next } | { '%s' | %s | %p | <child> %s | <next> %s }\"];\n",
                (void*) u, u->string, ((0 == u->token) ? "false" : "true"), u->value,
                ((NULL == u->child) ? "NULL" : " "),
                ((NULL == u->next) ? "NULL" : " ") );
    }

    if( NULL != u->child ) {
        printf( "struct%p:child -> struct%p:p;\n", (void*) u, (void*) u->child );
    }
    if( NULL != u->next ) {
        printf( "struct%p:next -> struct%p:p;\n", (void*) u, (void*) u->next );
    }
}

/**
 *  Print out the entire trie recursively.
 */
static void __print_all_nodes( struct ultrie *u )
{
    __print_node( u );
    if( NULL != u->child ) {
        __print_all_nodes( u->child );
    }
    if( NULL != u->next ) {
        __print_all_nodes( u->next );
    }
}
