/* 
* @Author: sxf
* @Date:   2015-12-01 16:42:01
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-01 18:27:58
*/

#include "schunk.h"
#include "vm.h"
#include "slipcore.h"
#include <malloc.h>


SChunk*  
slipC_createChunk(slip_Node* node) {
	SChunk* s = (SChunk*) calloc(1, sizeof(SChunk));
	s->head = node;
	return s;
}


int
slipC_callNode(slip_Core* vm, slip_Node* node) {
	
}


int
slipC_callChunk(slip_Core* vm, SChunk* c) {
	return slipC_callNode(vm, c->head);
}


