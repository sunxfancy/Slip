/* 
* @Author: sxf
* @Date:   2015-12-01 15:16:58
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-03 10:03:58
*/

#include "libapi.h"
#include "stable.h"
#include "sstring.h"
#include <stdio.h>
#include "slipcore.h"
#include "slip_stdlib.h"
#include "vm.h"

int 
slipL_regLib(slip_Core* vm, const char* lib_name, const slip_Reg* func_list) {
	// 检查全局环境中有无该库，有则继续向其中添加一个新的
	slip_Obj* libkey = slipS_createFromStr(lib_name);
	slip_Value libv = slipT_getOrInsertHashTable(vm->context->env, libkey);
	slip_Obj* lib_table = libv.v.o;
	int i = 0;
	const slip_Reg* list = func_list;
	while (list->name != NULL) {
		++list; ++i;
	}
	slipT_initHash(lib_table, i*2);

	while (func_list->name != NULL) {
		const char*    name = func_list->name;
		slip_CFunction func = func_list->func;
		slip_Value vfunc;
		slipV_setValueCFunc(&vfunc, func);
		slip_Obj* key = slipS_createFromStr(name);
		slipT_insertHash(lib_table, key, vfunc);
		++func_list;
	}
	return 0;
}


int 
slipL_regGlobalCfuncs(slip_Core* vm, const slip_Reg* func_list) {
	while (func_list->name != NULL) {
		const char*    name = func_list->name;
		slip_CFunction func = func_list->func;
		slip_Value vfunc;
		slipV_setValueCFunc(&vfunc, func);
		slip_Obj* key = slipS_createFromStr(name);
		slipT_insertHash(vm->context->env, key, vfunc);
		++func_list;
	}
}


int
slipL_regLibMacro(slip_Core* vm, const char* lib_name, const slip_RegM* func_list) {
	// 检查全局环境中有无该库，有则继续向其中添加一个新的
	slip_Obj* libkey = slipS_createFromStr(lib_name);
	slip_Value libv = slipT_getOrInsertHashTable(vm->context->env, libkey);
	slip_Obj* lib_table = libv.v.o;
	int i = 0;
	const slip_Reg* list = func_list;
	while (list->name != NULL) {
		++list; ++i;
	}
	slipT_initHash(lib_table, i*2);

	while (func_list->name != NULL) {
		const char* 	name = func_list->name;
		slip_CMacro 	func = func_list->macro;
		slip_Value vfunc;
		slipV_setValueCMacro(&vfunc, func);
		slip_Obj* key = slipS_createFromStr(name);
		slipT_insertHash(lib_table, key, vfunc);
		++func_list;
	}
	return 0;

}


int
slipL_regGlobalCMacros(slip_Core* vm, const slip_RegM* func_list) {
	while (func_list->name != NULL) {
		const char*    	name = func_list->name;
		slip_CMacro 	func = func_list->macro;
		slip_Value vfunc;
		slipV_setValueCMacro(&vfunc, func);
		slip_Obj* key = slipS_createFromStr(name);
		slipT_insertHash(vm->context->env, key, vfunc);
		++func_list;
	}
}







int
slipL_callCFunction(slip_Core* vm, slip_CFunction func, int num) {
	int ret_num = func(vm, num);
	int pop_num = slipV_popValueNum(vm, ret_num);
	if (pop_num != ret_num) return -1;
	return pop_num;
}


int
slipL_callCMacro(slip_Core* vm, slip_CMacro func, slip_Node* node, int num) {
	int ret_num = func(vm, node, num);
	int pop_num = slipV_popValueNum(vm, ret_num);
	if (pop_num != ret_num) return -1;
	return pop_num;
}



int 		
slipL_openStdLib(slip_Core* vm) {
	slipL_regGlobalCfuncs(vm, testlib);
	slipL_regGlobalCfuncs(vm, stdlib);
	slipL_regGlobalCMacros(vm, stdmacro);
}

