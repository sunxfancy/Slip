/* 
* @Author: sxf
* @Date:   2015-11-29 10:14:26
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-01 08:59:15
* 
* 基本的垃圾回收器
*/


#ifndef GC_H
#define GC_H


#include "object.h"

// GC Mark
#define GC_WHITE 		0
#define GC_OLD_WHITE 	1
#define GC_GRAY  		2
#define GC_BLACK 		3

/**
 * GC过程是一个分代增量的过程
 * 首先分为新生代GC_WHITE 和 老年代GC_OLD_WHTE
 * 一般会仅对GC_WHITE进行垃圾回收, 对全部WHITE回收的称为full-gc
 * 增量GC是利用GRAY标识, 每次选取一部分GRAY进行遍历, 找出其中的WHITE, 将其设置为GRAY, 而自身设置为BLACK
 * BLACK是明确的被引用的,并且下面没有WHITE节点的对象, 扫描时跳过即可
 */


extern void  	slipG_fullGC(slip_Obj* obj);
extern void 	slipG_gc(slip_Obj* obj);


extern int 		slipG_countMem(slip_Obj* obj);
extern int 		slipG_countObj(slip_Obj* obj);


extern void 	slipG_markObj(slip_Obj* obj);



#endif // GC_H
