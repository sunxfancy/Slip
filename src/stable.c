/*
* @Author: sxf
* @Date:   2015-12-01 11:14:19
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-03 18:19:01
*/

#include "stable.h"
#include "sstring.h"
#include <stdlib.h>
#include <stdlib.h>


static slip_Obj* meta = NULL;

slip_Obj*
slipT_createTable() {
	if (meta == NULL) meta = slipS_createFromStr("meta");
	slip_Obj* obj = (slip_Obj*) calloc (1, sizeof(STable));
	obj->type = slipO_table_t; // 创建元素并设定类型
	return obj;
}


int
slipT_initHash(slip_Obj* t, int size) {
	STable* table;
	if slipO_checkType(t, slipO_table_t)
		table = slipO_castTable(t);
	else return -1;
	if (table->hash_map != NULL) free (table->hash_map);
	table->hash_map = (STablePair*) calloc (size, sizeof(STablePair));
	table->map_nuse = 0;
	table->map_size = size;
	return 0;
}


int
slipT_initArray(slip_Obj* t, int size) {
	STable* table;
	if slipO_checkType(t, slipO_table_t)
		table = slipO_castTable(t);
	else return -1;
	if (table->array != NULL) free (table->array);
	table->array = (slip_Value*) calloc (size, sizeof(slip_Value));
	table->array_nuse = 0;
	table->array_size = size;
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
slipT_reHash(slip_Obj* t, int size) {
	STable* table;
	if slipO_checkType(t, slipO_table_t)
		table = slipO_castTable(t);
	else return -1;
	int old_size = table->map_size;
	STablePair* old_table = table->hash_map;
	table->hash_map = calloc (size, sizeof(STablePair));
	table->map_size = size;
	for (int i = 0; i < old_size; ++i) {
		SString* key = old_table[i].key;
		if (key != 0) {
			slipT_insertHash(slipO_castObj(table), slipO_castObj(key), old_table[i].value);
		}
	}
	return 0;
}


int
slipT_reArray(slip_Obj* t, int size) {

	return 0;
}


int
slipT_insertHash(slip_Obj* table, slip_Obj* skey, slip_Value value) {
	STable* t;
	if slipO_checkType(table, slipO_table_t)
		t = slipO_castTable(table);
	else return -1;
	SString* key;
	if slipO_checkType(skey, slipO_string_t)
		key = slipO_castString(skey);
	else return -1;

	slip_Obj* to = slipO_castObj(t);
	if (t->map_size == 0) slipT_initHash(to, 8);
	if (t->map_nuse > ((t->map_size * 3) / 4))
		slipT_reHash(to, t->map_size * 2);
	int hashcode = getHashCode(t->map_size, key->hash);
	int pos = hashcode;
	int i = 0;
	while (t->hash_map[pos].key != 0) {
		pos = getHashCode(t->map_size, hashcode + getTCsequence(++i));
		if (i > t->map_size / 2) {
			slipT_reHash((slip_Obj*)t, t->map_size * 2);
			return slipT_insertHash((slip_Obj*)t, (slip_Obj*)key, value);
		}
	}
	t->hash_map[pos].key = key;
	t->hash_map[pos].value = value;
	return 0;
}

static slip_Value
slip_gethash(STable* t, SString* key, int is_ref) {
	slip_Value ans = {{0}, 0};
	if (t->map_size == 0) return ans;
	int hashcode = getHashCode(t->map_size, key->hash);
	int pos = hashcode; int i = 0;
	while (t->hash_map[pos].key != 0) {
		if (slipS_equal(slipO_castObj(t->hash_map[pos].key), slipO_castObj(key))) {
			if (!is_ref) return t->hash_map[pos].value;
			else {
				slipV_setValueRef(&ans, &(t->hash_map[pos].value));
				return ans;
			}
		}
		pos = getHashCode(t->map_size, hashcode + getTCsequence(++i));
	}
	return ans;
}

static slip_Value
slipT_getHashImpl(slip_Obj* table, slip_Obj* skey, int is_ref) {
	slip_Value ans = {{0}, 0};
	STable* t;
	if slipO_checkType(table, slipO_table_t)
		t = slipO_castTable(table);
	else return ans;
	SString* key;
	if slipO_checkType(skey, slipO_string_t)
		key = slipO_castString(skey);
	else return ans;

	slip_Value ret = slip_gethash(t, key, is_ref);
	if (ret.t != 0) return ret;

	// 处理元表，递归进行查找
	slip_Value meta_table = slip_gethash(t, (SString*)meta, is_ref);
	if (meta_table.v.i != 0 && meta_table.t == slipV_table_t)
		return slipT_getHash(meta_table.v.o, (slip_Obj*)key);
	return ans;
}

slip_Value
slipT_getHash(slip_Obj* table, slip_Obj* skey) {
	return slipT_getHashImpl(table, skey, 0);
}

slip_Value
slipT_getHashRef(slip_Obj* table, slip_Obj* skey) {
	return slipT_getHashImpl(table, skey, 1);
}


slip_Value
slipT_getOrInsertHashTable(slip_Obj* table, slip_Obj* skey) {
	slip_Value ans = {{0}};
	ans = slipT_getHash(table, skey);
	if (ans.t == 0 || ans.t != slipV_table_t) {
		slip_Obj* newTable = slipT_createTable();
		slipV_setValueTable(&ans, newTable);
		slipT_insertHash(table, skey, ans);
	}
	return ans;
}



int
slipT_insertArray(slip_Obj* t, int index, slip_Value value) {
	// TODO: finish it!
	return 0;
}


slip_Value
slipT_getArray(slip_Obj* t, slip_Obj* key) {
	slip_Value ans = {{0}, 0};
	// TODO: finish it!
	return ans;
}
