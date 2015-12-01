/* 
* @Author: sxf
* @Date:   2015-12-01 15:16:58
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-01 20:31:44
*/

#include "libapi.h"
#include "stable.h"
#include "sstring.h"
#include <stdio.h>
#include "slipcore.h"
#include "slip_stdlib.h"

int 
slipL_regLib(slip_Core* vm, const char* lib_name, const slip_Reg* func_list) {
	STable* lib_table = slipT_createTable();

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
		SString* key = slipS_createFromStr(name);
		slipT_insertHash(lib_table, key, vfunc);
		++func_list;
	}

	slip_Value vlib;
	slipV_setValueTable(&vlib, lib_table);
	SString* libkey = slipS_createFromStr(lib_name);
	slipT_insertHash(vm->context->env, libkey, vlib);

	return 0;
}


int 
slipL_regGlobalCfuncs(slip_Core* vm, const slip_Reg* func_list) {
	while (func_list->name != NULL) {
		const char*    name = func_list->name;
		slip_CFunction func = func_list->func;
		slip_Value vfunc;
		slipV_setValueCFunc(&vfunc, func);
		SString* key = slipS_createFromStr(name);
		slipT_insertHash(vm->context->env, key, vfunc);
		++func_list;
	}
}


int 		
slipL_openStdLib(slip_Core* vm) {
	slipL_regGlobalCfuncs(vm, testlib);
}