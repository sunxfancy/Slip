/* 
* @Author: sxf
* @Date:   2015-12-01 16:13:25
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-01 18:19:09
*/

#ifndef CHUNK_H
#define CHUNK_H

#include "object.h"
#include "sliplist.h"

typedef struct slip_Core slip_Core;

typedef struct SChunk {
	slip_Obj 	base;
	slip_Node*  head;
} SChunk;


extern SChunk*  	slipC_createChunk(slip_Node* node);
extern int 			slipC_callNode(slip_Core* vm, slip_Node* node);
extern int 			slipC_callChunk(slip_Core* vm, SChunk* c);


#endif // CHUNK_H
