/* 
* @Author: sxf
* @Date:   2015-11-30 17:41:42
* @Last Modified by:   sxf
* @Last Modified time: 2015-11-30 21:43:23
*/

#include "sstring.h"
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int 
slipS_hash(SString* s) { // 这是一个针对32位整数的hash函数, 日后可以考虑变化hash的存储位数
	uint32_t hash = 0;  
    uint32_t x = 0;  
    const char* str = s->data;
    while (*str)  
    {  
        hash = (hash << 4) + (*str++);//hash左移4位，把当前字符ASCII存入hash低四位。   
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
slipS_equal(SString* s1, SString* s2) {
	if (s1->hash == s2->hash) {
		if (strcmp(s1->data, s2->data) == 0) return 1;
	}
	return 0;
}

SString*
slipS_copy(SString* s) {
	
}

SString*
slipS_create() {
	return (SString*) calloc(1, sizeof(SString));
}

SString*
slipS_createFromStr(const char* str) {
	SString* s = slipS_create();
	slipS_init(s, str);
}

SString* 
slipS_init(SString* s, const char* str) {
	int len = strlen(str);
	char* buf = (char*) malloc(len+1);
	assert(buf != NULL);
	if (s->data != NULL) free(s->data);
	s->data = strcpy(buf, str);
	s->len = len;
	s->hash = slipS_hash(s);
}