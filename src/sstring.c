/* 
* @Author: sxf
* @Date:   2015-11-30 17:41:42
* @Last Modified by:   sxf
* @Last Modified time: 2015-12-02 14:08:14
*/

#include "sstring.h"
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define CHECK_STR(name, src) \
	SString* name; \
	if slipO_checkType(src, slipO_string_t) \
		name = slipO_castString(src); \
	else return -1


int 
slipS_hash(slip_Obj* str) { 
	CHECK_STR(s, str);
	s->hash = slipS_hashcstr(s->data);
	return s->hash;
}


int
slipS_hashcstr(const char* s) { // 这是一个针对32位整数的hash函数, 日后可以考虑变化hash的存储位数
	uint32_t hash = 0;  
    uint32_t x = 0;  
    while (*s)  
    {  
        hash = (hash << 4) + (*s++);//hash左移4位，把当前字符ASCII存入hash低四位。   
        if ((x = hash & 0xF0000000L) != 0)  
        {  
            //如果最高的四位不为0，则说明字符多余7个，现在正在存第7个字符，如果不处理，再加下一个字符时，第一个字符会被移出，因此要有如下处理。  
            //该处理，如果最高位为0，就会仅仅影响5-8位，否则会影响5-31位，因为C语言使用的算数移位  
            //因为1-4位刚刚存储了新加入到字符，所以不能>>28  
            hash ^= (x >> 24);  
            //上面这行代码并不会对X有影响，本身X和hash的高4位相同，下面这行代码&~即对28-31(高4位)位清零。  
            hash &= ~x;  
        }  
    }  
    //返回一个符号位为0的数，即丢弃最高位，以免函数外产生影响。(我们可以考虑，如果只有字符，符号位不可能为负)  
    return (hash & 0x7FFFFFFF);  
}


int 
slipS_equal(slip_Obj* str1, slip_Obj* str2) {
	CHECK_STR(s1, str1);
	CHECK_STR(s2, str2);
	if (s1->hash == s2->hash) {
		if (strcmp(s1->data, s2->data) == 0) return 1;
	}
	return 0;
}


int 
slipS_equalcstr(slip_Obj* str1, const char* str2) {
	CHECK_STR(s1, str1);
	if (strcmp(s1->data, str2) == 0) return 1;
	return 0;
}

slip_Obj*
slipS_copy(slip_Obj* str) {
	CHECK_STR(s, str);
	SString* ns = slipS_create();
	char* buf = (char*) malloc(s->len + 1);
	assert(buf != NULL);
	strcpy(buf, s->data);
	ns->data = buf;
	ns->len = s->len;
	ns->hash = s->hash;
	return (slip_Obj*)ns;
}

slip_Obj*
slipS_create() { 
	slip_Obj* obj = (slip_Obj*) calloc(1, sizeof(SString));
	obj->type = slipO_string_t;
	return obj;
}

slip_Obj*
slipS_createFromStr(const char* str) {
	slip_Obj* s = slipS_create();
	slipS_init(s, str);
	return s;
}

slip_Obj* 
slipS_init(slip_Obj* sobj, const char* str) {
	CHECK_STR(s, sobj);
	int len = strlen(str);
	char* buf = (char*) malloc(len+1);
	assert(buf != NULL);
	if (s->data != NULL) free(s->data);
	strcpy(buf, str);
	s->data = buf;
	s->len = len;
	s->hash = slipS_hash(s);
	return (slip_Obj*)s;
}