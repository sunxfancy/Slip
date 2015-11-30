/* 
* @Author: sxf
* @Date:   2015-11-30 09:38:17
* @Last Modified by:   sxf
* @Last Modified time: 2015-11-30 18:15:34
*/



#ifndef LIBAPI_H
#define LIBAPI_H

typedef struct slip_Core slip_Core;

typedef int (*slip_CFunction)(slip_Core*);
typedef struct slip_Reg {
	const char* name;
	slip_CFunction func;
} slip_Reg;

extern int 		slipL_regLib(const char* lib_name, const slip_Reg* func_list);
extern int 		slipL_regGlobalCfuncs(const slip_Reg* func_list);




#endif // LIBAPI_H
