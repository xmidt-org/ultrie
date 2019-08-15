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

#include <stdint.h>

typedef void* ultrie_t;

/**
 *  Creates a new ultrie object.
 *
 *  @note: The object must be destroyed with ultrie_destroy()
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
 *  @param value the value
 *
 *  @return -1 if there was an error adding to the list, -2 if this key
 *          is already present or 0 if successful 
 */
int ultrie_add( ultrie_t u, const char *key, uint64_t value );

/**
 *  Finds the token for the key.
 *
 *  @param u     the trie to evaluate against
 *  @param key   the key to search for
 *  @param value the resulting value to return (only set if found)
 *
 *  @return 0 if the key is found, error otherwise.
 */
int ultrie_find( ultrie_t u, const char *key, uint64_t *value );

/**
 *  This function provides an array of bytes that represents the present
 *  ultrie_t trie that can be used in that state.
 *
 *  @note: A dehydrated trie is represented as an array of bytes that can be
 *         used in place.  This does not require the time or resources needed
 *         to build the entire trie, but isn't quite as fast.
 *
 *  @note: The actual ultrie_t passed in is untouched during the dehydration
 *         process.
 *
 *  @note: The returned pointer (if non-NULL) will need to be freed via free()
 *         when the caller is done with it.
 *
 *  @param u   the trie to dehydrate
 *  @param len the size of the returned array of bytes
 *  
 *  @return Non-NULL if successful or NULL on error
 */
uint8_t* ultrie_dehydrate( ultrie_t u, size_t *len );

/**
 *  This function takes a dehydrated trie in the buffer and builds a ultrie_t
 *  object.
 *
 *  @param buf  the dehydrated buffer to rehydrate
 *  @param len  the size of the buffer
 *
 *  @return the object or NULL on error
 */
ultrie_t ultrie_rehydrate( const uint8_t *buf, size_t len );

/**
 *  Finds the token for the key.
 *
 *  @param buf   the dehydrated buffer to use
 *  @param len   the size of the buffer
 *  @param key   the key to search for
 *  @param value the resulting value to return (only set if found)
 *
 *  @return 0 if the key is found, error otherwise.
 */
int ultrie_dehydrated_find( const uint8_t *buf, const char *key, uint64_t *value );

/**
 *  Prints out the trie in graphviz DOT notation so you can debug it.
 *
 *  @param u the trie to print out
 */
void ultrie_print( ultrie_t u );

#endif
