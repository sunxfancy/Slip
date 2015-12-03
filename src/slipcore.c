/* 
* @Author: sxf
* @Date:   2015-12-01 17:54:14
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-03 20:24:29
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
	slipC_pushEnvStack(vm, vm->context->env);
	return vm;
}


slip_Context* 
slipC_createContext() {
	slip_Context* ctx = (slip_Context*) calloc(1, sizeof(slip_Context));
	ctx->env = slipT_createTable(); // 创建并初始化全局hash表
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
	slip_Obj* nowTable;
	slip_Value ans = {0, 0};
	slip_Obj* key = slipS_createFromStr(id);
	for (int i = size; i > 0; --i) {
		slip_Value v = slipS_get(&(vm->env_stack), i);
		nowTable = v.v.o;
		ans = slipT_getHash(nowTable, key);
		if (ans.t != 0) return ans;
	}
	return ans;
}

slip_Value
slipC_findRef(slip_Core* vm, const char* id) {
	int size = vm->env_stack.stack_nuse;
	slip_Obj* nowTable;
	slip_Value ans = {0, 0};
	slip_Obj* key = slipS_createFromStr(id);
	for (int i = size; i > 0; --i) {
		slip_Value v = slipS_get(&(vm->env_stack), i);
		nowTable = v.v.o;
		ans = slipT_getHashRef(nowTable, key);
		if (ans.t != 0) return ans;
	}
	return ans;
}

int 				
slipC_setID(slip_Core* vm, const char* id, slip_Value value) {
	slip_Obj* key = slipS_createFromStr(id);
	int size = vm->env_stack.stack_nuse;
	slip_Value v = slipS_get(&(vm->env_stack), size);
	slip_Obj* nowTable = v.v.o;
	slipT_insertHash(nowTable, key, value);
	return 0;
}


int 			
slipC_pushEnvStack(slip_Core* vm, slip_Obj* env) {
	slip_Value etable;
	slipV_setValueTable(&etable, env);
	slipS_push(&(vm->env_stack), etable);
	return 0;
}


slip_Obj*  	
slipC_popEnvStack(slip_Core* vm) {
	slip_Value etable = slipS_pop(&(vm->env_stack));
	return etable.v.o;
}


int 				
slipC_printStack(slip_Core* vm) {
	slipS_printStack(&(vm->stack));
}