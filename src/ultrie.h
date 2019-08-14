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
#ifndef __ULTRIE_H__
#define __ULTRIE_H__

typedef void* ultrie_t;

/**
 *  Creates a new ultrie object.
 *
 *  The object must be destroyed with ultrie_destroy()
 *
 *  @return the object or NULL on error
 */
ultrie_t ultrie_new( void );

/**
 *  Destroys the specified ultrie object.
 *
 *  @param u the trie to destroy
 */
void ultrie_destroy( ultrie_t u );

/**
 *  Adds to the trie the key and value pair.
 *
 *  @param u     the trie to add to
 *  @param key   the key string
 *  @param value the value void *
 *
 *  @return -1 if there was an error adding to the list, -2 if this key
 *          is already present or 0 if successful 
 */
int ultrie_add( ultrie_t u, const char *key, void *value );

/**
 *  Finds the token for the key.
 *
 *  @param u   the trie to evaluate against
 *  @param key the key to search for
 *
 *  @return NULL on error or if the value for the token was NULL.  Non-NULL
 *          otherwise.
 */
void* ultrie_find( ultrie_t u, const char *key );

/**
 *  Prints out the trie in graphviz DOT notation so you can debug it.
 *
 *  @param u the trie to print out
 */
void ultrie_print( ultrie_t u );

#endif
