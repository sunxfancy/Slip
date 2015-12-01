/* 
* @Author: sxf
* @Date:   2015-12-01 11:14:19
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-01 13:59:34
*/

#include "stable.h"
#include "sstring.h"
#include <stdlib.h>
#include <malloc.h>


STable* 		
slipT_create() {
	return (STable*) calloc (1, sizeof(STable));
}


int 			
slipT_initHash(STable* t, int size) {
	if (t->hash_map != NULL) free (t->hash_map);
	t->hash_map = (STablePair*) calloc (size, sizeof(STablePair));
	t->map_nuse = 0;
	t->map_size = size;
	return 0;
}


int 			
slipT_initArray(STable* t, int size) {
	if (t->array != NULL) free (t->array);
	t->array = (slip_Value*) calloc (size, sizeof(slip_Value));
	t->array_nuse = 0;
	t->array_size = size;
	return 0;
}


static inline int
getHashCode(int map_size, int num) {
	if (num < 0) return num % map_size + map_size;
	return num % map_size;
}


static inline int
getTCsequence(int i) {
	int c = i >> 1;
	if (i & 1) return - (c * c);
	return c * c;
}



int 			
slipT_reHash(STable* t, int size) {
	int old_size = t->map_size;
	STablePair* old_table = t->hash_map;
	t->hash_map = calloc (size, sizeof(STablePair));
	t->map_size = size;
	for (int i = 0; i < old_size; ++i) {	
		SString* key = old_table[i].key;
		if (key != 0) {
			slipT_insertHash(t, key, old_table[i].value);
		}
	}
	return 0;
}


int 			
slipT_reArray(STable* t, int size) {

}


int
slipT_insertHash(STable* t, SString* key, slip_Value value) {
	if (t->map_nuse > ((t->map_size * 3) / 4)) 
		slipT_reHash(t, t->map_size * 2);
	int hashcode = getHashCode(t->map_size, key->hash);
	int pos = hashcode;
	int i = 0;
	while (t->hash_map[pos].key != 0) {
		pos = getHashCode(t->map_size, hashcode + getTCsequence(++i));
		if (i > t->map_size / 2) { 
			slipT_reHash(t, t->map_size * 2);
			return slipT_insertHash(t, key, value);
		}
	}
	t->hash_map[pos].key = key;
	t->hash_map[pos].value = value;
	return 0;
}


slip_Value 
slipT_getHash(STable* t, SString* key) {
	int hashcode = getHashCode(t->map_size, key->hash);
	int pos = hashcode; int i = 0;
	while (t->hash_map[pos].key != 0) {
		if (slipS_equal(t->hash_map[pos].key, key)) {
			return t->hash_map[pos].value;			
		}
		pos = getHashCode(t->map_size, hashcode + getTCsequence(++i));
	}
	slip_Value ans = {0};
	return ans;
}


int 			
slipT_insertArray(STable* t, int index, slip_Value value) {

}


slip_Value 	
slipT_getArray(STable* t, SString* key) {

}



