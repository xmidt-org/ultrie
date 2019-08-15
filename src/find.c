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
/* none */

/*----------------------------------------------------------------------------*/
/*                             External Functions                             */
/*----------------------------------------------------------------------------*/

/* See ultrie.h for details. */
int ultrie_find( ultrie_t _u, const char *k, uint64_t *v )
{
    struct ultrie *u = (struct ultrie*) _u;

    if( NULL == k ) {
        return -1;
    }

    while( NULL != u ) {
        char *s = u->string;

        if( *k < *s ) {
            /* Not found since the trie is sorted. */
            return -1;
        } else if( *s < *k ){
            /* Look next until we have a character that matches. */
            u = u->next;
        } else {
            /* Found 1 character that matched, now power through them all. */
            while( (*s) && (*k) && (*s == *k) ) {
                s++;
                k++;
            }

            if( '\0' == *s && '\0' == *k ) {
                /* Exact match.  We're done. */
                if( u->token ) {
                    if( NULL != v ) {
                        *v = u->value;
                    }
                    return 0;
                }
                return -1;
            } else if( '\0' == *s && *k ) {
                /* We must continue down a child node. */
                u = u->child;
            } else {
                /* We did not match. */
                return -1;
            }
        }
    }
    return -1;
}

/*----------------------------------------------------------------------------*/
/*                             Internal functions                             */
/*----------------------------------------------------------------------------*/
/* none */
