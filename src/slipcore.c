/* 
* @Author: sxf
* @Date:   2015-12-01 17:54:14
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-01 20:14:57
*/

#include <stdlib.h>
#include "slipcore.h"
#include "stable.h"


slip_Core* 	
slipC_createCore() {
	slip_Core* vm = (slip_Core*) calloc(1, sizeof(slip_Core));
	slipS_extend(&(vm->env_stack));
	slipS_extend(&(vm->stack));
	vm->context = slipC_createContext();

	// 将全局符号表压栈
	slip_Value etable;
	slipV_setValueTable(&etable, vm->context->env);
	slipS_push(&(vm->env_stack), etable);
	return vm;
}


slip_Context* 
slipC_createContext() {
	slip_Context* ctx = (slip_Context*) calloc(1, sizeof(slip_Context));
	ctx->env = slipT_createTable();
	slipT_initHash(ctx->env, 128);
	return ctx;
}



int
slipC_close(slip_Core* vm) {

}



int
slipC_loadFile(const char* path) {

}


int
slipC_loadStr(const char* str) {

}

