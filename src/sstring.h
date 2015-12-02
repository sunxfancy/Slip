/* 
* @Author: sxf
* @Date:   2015-11-30 17:27:49
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-02 14:04:56
*/


#ifndef SSTRING_H
#define SSTRING_H

#include "object.h"

typedef struct SString {
	slip_Obj 	base;
	char* 		data;
	int 		len;
	int 		hash;
} SString;

/**
 * @brief ELFhash算法, 结果会缓存到SString对象中
 * @return hash值
 */
extern int 		slipS_hash(slip_Obj* str);


/**
 * @brief 计算一个char指针的hash值
 * 
 * @param s 要计算的字符串
 * @return hash值
 */
extern int 		slipS_hashcstr(const char* s);

/**
 * @brief 测试两字符串是否相当
 * @return 若参数s1 和s2 字符串相同则返回1。否则返回0。
 */
extern int 		slipS_equal(slip_Obj* str1, slip_Obj* str2);


/**
 * @brief 测试两字符串是否相当
 * @return 若参数s1 和s2 字符串相同则返回1。否则返回0。
 */
extern int 		slipS_equalcstr(slip_Obj* str1, const char* str2);

/**
 * @brief 字符串比较函数, 仅仅是简单调用了strcmp
 * @return 若参数s1 和s2 字符串相同则返回0。s1 若大于s2 则返回大于0 的值。s1 若小于s2 则返回小于0 的值。
 */
extern int 		slipS_cmp(slip_Obj* str1, slip_Obj* str2);

/**
 * @brief 拷贝字符串
 */
extern slip_Obj* slipS_copy(slip_Obj* str);

/**
 * @brief 初始化整个字符串, 如果原先有存储字符串, 则先释放该资源
 * 
 * @param s 目标字符串
 * @param str C字符串
 * 
 * @return 目标字符串
 */
extern slip_Obj* slipS_init(slip_Obj* sobj, const char* str);

/**
 * @brief 创建一个空的字符串
 */
extern slip_Obj* slipS_create();

/**
 * @brief 创建并初始化一个字符串
 */
extern slip_Obj* slipS_createFromStr(const char* str);




#endif // SSTRING_H
