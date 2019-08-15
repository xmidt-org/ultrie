/*
 * Copyright 2019 Comcast Cable Communications Management, LLC
 * Copyright 2019 Weston Schmidt
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

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "../src/ultrie.h"

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
const char *tokens[] = {    "2.4GHz",
                            "5GHz",
                            "access-points",
                            "advertisement",
                            "auto-channel-enable",
                            "b",
                            "basic-rate",
                            "channel",
                            "dfs-enabled",
                            "extension-channel",
                            "g",
                            "method",
                            "n",
                            "name",
                            "operating-channel-bandwidth",
                            "operating-standards",
                            "password",
                            "security-mode",
                            "ssid",
                            "tx-power",
                            "wifi",
                            0 };

const char *search[] = {    "2.4GHz",
                            "5GHz",
                            "bob",
                            "kevin",
                            "access-points",
                            "advertisement",
                            "auto-channel-enable",
                            "b",
                            "basic-rate",
                            "channel",
                            "dfs-enabled",
                            "extension-channel",
                            "g",
                            "method",
                            "fred",
                            "n",
                            "name",
                            "operating-channel-bandwidth",
                            "operating-standards",
                            "operating-ignore-me-now",
                            "password",
                            "security-mode",
                            "ssid",
                            "tx-power",
                            "wifi",
                            0 };

/*----------------------------------------------------------------------------*/
/*                             Function Prototypes                            */
/*----------------------------------------------------------------------------*/
/* none */

/*----------------------------------------------------------------------------*/
/*                             External Functions                             */
/*----------------------------------------------------------------------------*/
/* none */

/*----------------------------------------------------------------------------*/
/*                             Internal functions                             */
/*----------------------------------------------------------------------------*/
void test_string_compare( int count )
{
    clock_t start, diff;
    int msec, i, j, k;

    start = clock();
    for( k = 0; k < count; k++ ) {
        for( i = 0; 0 != search[i]; i++ ) {
            for( j = 0; 0 != tokens[j]; j++ ) {
                if( 0 == strcmp( search[i], tokens[j] ) ) {
                    continue;
                }
            }
        }
    }
    diff = clock() - start;
    msec = diff * 1000 / CLOCKS_PER_SEC;
    printf( "strcmp() x%d Time taken %d seconds %d milliseconds\n", count, msec / 1000, msec % 1000 );
}

void test_in_memory_trie( int count )
{
    clock_t start, diff;
    int msec, i, k;
    ultrie_t t;

    t = ultrie_new();

    for( i = 0; 0 != tokens[i]; i++ ) {
        ultrie_add( t, tokens[i], i );
    }

    start = clock();
    for( k = 0; k < count; k++ ) {
        for( i = 0; 0 != search[i]; i++ ) {
            ultrie_find( t, search[i], NULL );
        }
    }
    diff = clock() - start;
    msec = diff * 1000 / CLOCKS_PER_SEC;
    printf( "in memory trie() x%d Time taken %d seconds %d milliseconds\n", count, msec / 1000, msec % 1000 );
}

int main( int argc, char *argv[] )
{
    (void) argc;
    (void) argv;

    test_string_compare( 100000 );
    test_in_memory_trie( 100000 );
}
