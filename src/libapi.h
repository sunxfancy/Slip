/* 
* @Author: sxf
* @Date:   2015-11-30 09:38:17
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-02 22:19:02
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

extern int 		slipL_regLib(slip_Core* vm, const char* lib_name, const slip_Reg* func_list);
extern int 		slipL_regGlobalCfuncs(slip_Core* vm, const slip_Reg* func_list);

extern int 		slipL_regLibMacro(slip_Core* vm, const char* lib_name, const slip_RegM* func_list);
extern int 		slipL_regGlobalCMacros(slip_Core* vm, const slip_RegM* func_list);


extern int 		slipL_openStdLib(slip_Core* vm);
extern int 		slipL_callCFunction(slip_Core* vm, slip_CFunction func, int num);
extern int 		slipL_callCMacro(slip_Core* vm, slip_CMacro func, slip_Node* node, int num);


#endif // LIBAPI_H
