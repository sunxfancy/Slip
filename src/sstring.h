/* 
* @Author: sxf
* @Date:   2015-11-30 17:27:49
* @Last Modified by:   sxf
* @Last Modified time: 2015-11-30 21:40:20
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
extern int 		slipS_hash(SString* s);

/**
 * @brief 测试两字符串是否相当
 * @return 若参数s1 和s2 字符串相同则返回1。否则返回0。
 */
extern int 		slipS_equal(SString* s1, SString* s2);

/**
 * @brief 字符串比较函数, 仅仅是简单调用了strcmp
 * @return 若参数s1 和s2 字符串相同则返回0。s1 若大于s2 则返回大于0 的值。s1 若小于s2 则返回小于0 的值。
 */
extern int 		slipS_cmp(SString* s1, SString* s2);

/**
 * @brief 拷贝字符串
 */
extern SString* slipS_copy(SString* s);

/**
 * @brief 初始化整个字符串, 如果原先有存储字符串, 则先释放该资源
 * 
 * @param s 目标字符串
 * @param str C字符串
 * 
 * @return 目标字符串
 */
extern SString* slipS_init(SString* s, const char* str);

/**
 * @brief 创建一个空的字符串
 */
extern SString* slipS_create();

/**
 * @brief 创建并初始化一个字符串
 */
extern SString* slipS_createFromStr(const char* str);




#endif // SSTRING_H
