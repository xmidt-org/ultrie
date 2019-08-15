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

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

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
static struct ultrie* __new( const char *k, uint64_t v, bool token );

/*----------------------------------------------------------------------------*/
/*                             External Functions                             */
/*----------------------------------------------------------------------------*/

/* See ultrie.h for details. */
ultrie_t ultrie_new( void )
{
    return (ultrie_t) __new( NULL, 0, false );
}

/* See ultrie.h for details. */
void ultrie_destroy( ultrie_t _u )
{
    struct ultrie *u = (struct ultrie*) _u;
    struct ultrie *last;

    last = u;
    while( NULL != last->next ) {
        last = last->next;
    }

    while( NULL != u ) {
        struct ultrie *p;

        if( NULL != u->child ) {
            last->next = u->child;
            while( NULL != last->next ) {
                last = last->next;
            }
        }
        p = u;
        u = u->next;

        if( p->string ) {
            free( p->string );
        }
        free( p );
    }
}

/* See ultrie.h for details. */
int ultrie_add( ultrie_t _u, const char *k, uint64_t v )
{
    struct ultrie *u = (struct ultrie*) _u;

    if( NULL == k || NULL == u ) {
        return -1;
    }

    if( NULL == u->string ) {
        /* Nothing is defined.  Easy. */
        u->string = strdup( k );
        if( NULL != u->string ) {
            u->value = v;
            u->token = 1;
        }

        return 0;
    }

    while( 1 ) {
        char *s = u->string;

        while( (*s) && (*k) && (*s == *k) ) {
            s++;
            k++;
        }

        if( '\0' == *s ) {
            if( '\0' == *k ) {
                /* Existing internal node matched, just make it have a value
                 * and be an endpoint. */
                if( 0 != u->token ) {
                    /* This is a duplicate.  Fail. */
                    return -2;
                }
                u->token = 1;
                u->value = v;
                return 0;
            } else {
                if( NULL == u->child ) {
                    /* Add a new child. */
                    u->child = __new( k, v, true );
                    return 0;
                } else {
                    /* Search children. */
                    u = u->child;
                }
            }
        } else {
            if( '\0' == *k ) {
                /* A partial string matched.  Split at this point. */
                struct ultrie *p = __new( s, u->value, u->token );
                p->next = u->next;
                p->child = u->child;
                *s = '\0';
                u->child = p;
                u->next = NULL;
                u->token = 1;
                u->value = v;
                return 0;
            } else {
                if( *k < *s ) {
                    /* Use the existing u node & add after it
                     * instead of re-allocating.  This is required
                     * in case the u node is the root node. */
                    struct ultrie *p = __new( s, u->value, u->token );
                    p->next = u->next;
                    p->child = u->child;

                    u->value = v;
                    u->next = p;
                    u->child = NULL;
                    free( u->string );
                    u->string = strdup( k );
                    return 0;
                } else {
                    if( NULL == u->next ) {
                        if( u->string == s ) {
                            /* Append a new node to the end of the list */
                            u->next = __new( k, v, true );
                            return 0;
                        } else {
                            /* Split a long string into 2 children. */
                            struct ultrie *p1 = __new( k, v, true );
                            struct ultrie *p2 = __new( s, u->value, true );

                            p2->child = u->child;
                            u->child = p2;
                            u->token = 0;
                            u->value = 0;
                            p2->next = p1;
                            *s = '\0';
                            return 0;
                        }
                    } else {
                        /* Move on to the next item for comparison. */
                        u = u->next;
                    }
                }
            }
        }
    }

    /* It is not possible to hit this, but some compilers may require it. */
    return -1;
}


/*----------------------------------------------------------------------------*/
/*                             Internal functions                             */
/*----------------------------------------------------------------------------*/
static struct ultrie* __new( const char *k, uint64_t v, bool token )
{
    struct ultrie *rv;

    rv = (struct ultrie*) malloc( sizeof(struct ultrie) );
    if( NULL != rv ) {
        memset( rv, 0, sizeof(struct ultrie) );
        if( NULL != k ) {
            rv->string = strdup( k );
            if( NULL != rv->string ) {
                rv->value = v;
                rv->token = token;
            } else {
                free( rv );
                rv = NULL;
            }
        }
    }

    return rv;
}
