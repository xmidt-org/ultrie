/**
 *  Copyright 2019 Comcast Cable Communications Management, LLC
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <CUnit/Basic.h>

#include <unistd.h>

#include "../src/ultrie.h"

void test_add( void )
{
    ultrie_t t;
    int i;
    uint64_t val;

    struct tests {
        const char *k;
        uint64_t v;
    } test_vector[] = {
        { .k = "cab",      .v = 1  },
        { .k = "cad",      .v = 2  },
        { .k = "cart",     .v = 3  },
        { .k = "car",      .v = 4  },
        { .k = "cap",      .v = 5  },
        { .k = "cabernet", .v = 6  },
        { .k = "ca",       .v = 7  },
        { .k = "cabaret",  .v = 8  },
        { .k = "carrot",   .v = 9  },
        { .k = "doc",      .v = 10 },
        { .k = "apple",    .v = 11 },
        { .k = "dom",      .v = 12 },
        { .k = NULL,       .v = 0  }
    };

    const char *invalid[] = {
        "9",
        "a",
        "c",
        "carrots",
        "zod",
        "do",
        NULL,
    };

    t = ultrie_new();
    CU_ASSERT( NULL != t );

    for( i = 0; NULL != test_vector[i].k; i++ ) {
        ultrie_add( t, test_vector[i].k, test_vector[i].v );
        CU_ASSERT( 0 == ultrie_find(t, test_vector[i].k, &val) );
        CU_ASSERT( test_vector[i].v == val );
    }
    ultrie_print( t );

    CU_ASSERT( -1 == ultrie_add(NULL, "apple", 99) );
    CU_ASSERT( -1 == ultrie_add(t, NULL, 99) );
    CU_ASSERT( -2 == ultrie_add(t, "apple", 99) );

    for( i = 0; NULL != test_vector[i].k; i++ ) {
        CU_ASSERT( 0 == ultrie_find(t, test_vector[i].k, &val) );
        CU_ASSERT( test_vector[i].v == val );
    }

    val = 88;
    CU_ASSERT( 0 != ultrie_find(t, NULL, &val) );
    CU_ASSERT( 88 == val );
    CU_ASSERT( 0 == ultrie_find(t, "apple", NULL) );
    CU_ASSERT( 0 != ultrie_find(t, "invalid", NULL) );
    CU_ASSERT( 0 != ultrie_find(t, NULL, NULL) );

    for( i = 0; NULL != invalid[i]; i++ ) {
        CU_ASSERT( 0 != ultrie_find(t, invalid[i], NULL) );
    }

    ultrie_destroy( t );
}

void add_suites( CU_pSuite *suite )
{
    *suite = CU_add_suite( "metrics tests", NULL, NULL );
    CU_add_test( *suite, "Test Adding", test_add );
}

/*----------------------------------------------------------------------------*/
/*                             External Functions                             */
/*----------------------------------------------------------------------------*/
int main( void )
{
    unsigned rv = 1;
    CU_pSuite suite = NULL;

    if( CUE_SUCCESS == CU_initialize_registry() ) {
        add_suites( &suite );

        if( NULL != suite ) {
            CU_basic_set_mode( CU_BRM_VERBOSE );
            CU_basic_run_tests();
            printf( "\n" );
            CU_basic_show_failures( CU_get_failure_list() );
            printf( "\n\n" );
            rv = CU_get_number_of_tests_failed();
        }

        CU_cleanup_registry();
    }

    if( 0 != rv ) {
        return 1;
    }

    return 0;
}
