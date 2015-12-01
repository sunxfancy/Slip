/* 
* @Author: sxf
* @Date:   2015-12-01 17:54:14
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-01 18:57:37
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
	slip_Value etable;
	etable.t = slipV_table_t;
	etable.v.o = (slip_Obj*) (vm->context->env);
	slipS_push(&(vm->env_stack), etable);
	return vm;
}


slip_Context* 
slipC_createContext() {
	slip_Context* ctx = (slip_Context*) calloc(1, sizeof(slip_Context));
	ctx->env = slipT_createTable();
	return ctx;
}



int
slipC_close(slip_Core* vm) {

}

