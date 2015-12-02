/* 
* @Author: sxf
* @Date:   2015-11-30 09:38:17
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-02 10:13:08
*/



#ifndef LIBAPI_H
#define LIBAPI_H

typedef struct slip_Core slip_Core;

typedef int (*slip_CFunction)(slip_Core*, int);
typedef struct slip_Reg {
	const char* name;
	slip_CFunction func;
} slip_Reg;

extern int 		slipL_regLib(slip_Core* vm, const char* lib_name, const slip_Reg* func_list);
extern int 		slipL_regGlobalCfuncs(slip_Core* vm, const slip_Reg* func_list);

extern int 		slipL_openStdLib(slip_Core* vm);
extern int 		slipL_callCFunction(slip_Core* vm, slip_CFunction func, int num);

#endif // LIBAPI_H
