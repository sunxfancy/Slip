/* 
* @Author: sxf
* @Date:   2015-11-30 17:51:42
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-03 18:12:16
*/

#ifndef STABLE_H
#define STABLE_H

#include "value.h"
#include "object.h"

typedef struct SString SString;

typedef struct STablePair {
	SString* key;
	slip_Value value;
} STablePair;


typedef struct STable {
	slip_Obj 	base;

	// 分成两部分, 一部分是用作数组的, 一部分则作为hash表
	slip_Value* array; // 默认情况是未分配
	int 		array_size;	
	int 		array_nuse;

	// 用作hash表的部分
	STablePair* hash_map;
	int 		map_size;
	int 		map_nuse;

} STable;


extern slip_Obj* 		slipT_createTable();

/**
 * @brief 初始化Table的hash表部分
 * @param t Table对象
 * @param size 初始化后的大小
 * 
 * @return 正确时返回0, 否则为异常码
 */
extern int 			slipT_initHash(slip_Obj* t, int size);
extern int 			slipT_initArray(slip_Obj* t, int size);

/**
 * @brief rehash过程 重新hash表内全部元素
 * 
 * @param t Table对象
 * @param size 重新分配的大小
 * 
 * @return 正确时为0, 其余情况为异常码
 */
extern int 			slipT_reHash(slip_Obj* t, int size);
extern int 			slipT_reArray(slip_Obj* t, int size);


/**
 * @brief 插入hash表
 * 
 * @param t Table
 * @param key 键
 * @param value 要插入的Value值
 * @return 成功返回0, 异常返回异常码
 */
extern int 			slipT_insertHash(slip_Obj* table, slip_Obj* skey, slip_Value value);
extern slip_Value 	slipT_getHash(slip_Obj* table, slip_Obj* skey);
extern slip_Value 	slipT_getHashRef(slip_Obj* table, slip_Obj* skey); // 这个一定返回引用类型

extern slip_Value 	slipT_getOrInsertHashTable(slip_Obj* table, slip_Obj* skey);

extern int 			slipT_insertArray(slip_Obj* table, int index, slip_Value value);
extern slip_Value 	slipT_getArray(slip_Obj* table, slip_Obj* key);




#endif // STABLE_H
