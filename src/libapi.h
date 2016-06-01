/*
* @Author: sxf
* @Date:   2015-11-30 09:38:17
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-02 22:19:02
*
* 库API，主要负责定义系统库和用户库的接口，是和C函数关联的关键模块
*/



#ifndef LIBAPI_H
#define LIBAPI_H

#include "sliplist.h"

typedef struct slip_Core slip_Core;

typedef int (*slip_CFunction)(slip_Core*, int);
typedef int (*slip_CMacro)(slip_Core*, slip_Node*, int num);

typedef struct slip_Reg {
	const char* 	name;
	slip_CFunction  func;
} slip_Reg;

typedef struct slip_RegM {
	const char* 	name;
	slip_CMacro 	macro;
} slip_RegM;


/**
 * 注册一个库
 * @method slipL_regLib
 * @param  vm           虚拟机
 * @param  lib_name     库名字，会被导入符号表
 * @param  func_list    函数名字，指针列表
 * @return              成功返回0
 */
extern int 		slipL_regLib(slip_Core* vm, const char* lib_name, const slip_Reg* func_list);

/**
 * 注册一个全局库，所有函数会被放入到全局符号表中
 * @method slipL_regGlobalCfuncs
 * @param  vm           虚拟机
 * @param  func_list    函数名字，指针列表
 * @return              成功返回0
 */
extern int 		slipL_regGlobalCfuncs(slip_Core* vm, const slip_Reg* func_list);

/**
 * 注册用户宏库
 * @method slipL_regLibMacro
 * @param  vm                虚拟机
 * @param  lib_name          库名字，会被导入符号表
 * @param  func_list         宏名字，指针列表
 * @return                   成功返回0
 */
extern int 		slipL_regLibMacro(slip_Core* vm, const char* lib_name, const slip_RegM* func_list);

/**
 * 注册一个全局宏库，所有宏会被放入到全局符号表中
 * @method slipL_regGlobalCMacros
 * @param  vm           虚拟机
 * @param  func_list    宏名字，指针列表
 * @return              成功返回0
 */
extern int 		slipL_regGlobalCMacros(slip_Core* vm, const slip_RegM* func_list);

/**
 * 引入标准库
 * @method slipL_openStdLib
 * @param  vm               虚拟机
 * @return                  成功返回0
 */
extern int 		slipL_openStdLib(slip_Core* vm);

/**
 * 调用一个C函数
 * @method slipL_callCFunction
 * @param  vm                  虚拟机
 * @param  func                函数指针
 * @param  num                 参数个数
 * @return                     返回的元素个数，负数为异常
 */
extern int 		slipL_callCFunction(slip_Core* vm, slip_CFunction func, int num);

/**
 * 调用一个C宏
 * @method slipL_callCMacro
 * @param  vm               虚拟机
 * @param  func             宏指针
 * @param  node             要操作的代码节点
 * @param  num              参数个数
 * @return                  返回的元素个数，负数为异常
 */
extern int 		slipL_callCMacro(slip_Core* vm, slip_CMacro func, slip_Node* node, int num);


#endif // LIBAPI_H
