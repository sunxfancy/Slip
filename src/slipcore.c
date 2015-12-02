/* 
* @Author: sxf
* @Date:   2015-12-01 17:54:14
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-02 12:39:46
*/

#include <stdlib.h>
#include "slipcore.h"
#include "stable.h"
#include "vm.h"
#include "sliplist.h"


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
slipC_loadFile(slip_Core* vm, const char* path) {
	slip_Node* l = slipL_parseFile(path);
	slipV_pushListNode(vm, l);
	slipV_call(vm, 0);
}


int
slipC_loadStr(slip_Core* vm, const char* str) {
	slip_Node* l = slipL_parseString(str);
	slipV_pushListNode(vm, l);
	slipV_call(vm, 0);
}


slip_Value
slipC_findID(slip_Core* vm, const char* id) {
	int size = vm->env_stack.stack_nuse;
	STable* nowTable;
	slip_Value ans = {0};
	SString* key = slipS_createFromStr(id);
	for (int i = size; i > 0; --i) {
		slip_Value v = slipS_get(&(vm->env_stack), i);
		nowTable = (STable*)(v.v.o);
		ans = slipT_getHash(nowTable, key);
		if (ans.v.i != 0) return ans;
	}
	return ans;
}