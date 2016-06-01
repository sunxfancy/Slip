Slip
======

[![Build Status](https://travis-ci.org/sunxfancy/Slip.svg?branch=master)](https://travis-ci.org/sunxfancy/Slip)

[![Build status](https://ci.appveyor.com/api/projects/status/e72qy8m89e32187p?svg=true)](https://ci.appveyor.com/project/sunxfancy/slip)


Slip一门嵌入式lisp风格语言, lisp功能很强大, 但有时我们又不希望使用标准lisp库, 如果能和C方便的交互, 调用C函数, 而不是一般的lisp程序库, 那么也可定制性非常强, 我们可以自由的在上面创造各种语法和表达, 定义适合自身的宏, 而不再使用lisp本身定义的那些程序库.

Slip的设计思路和lua很接近, 将绝大部分功能实现放置到宿主语言中, 而语言本身非常小巧和简洁, 专为定制化DSL功能而设计。Slip使用纯C实现, 使用c99标准库, 不依赖其他任何组件.

本项目正在开发中, 将会陆续添加各种lisp语言特性.

### 项目构建

本项目使用CMake构建, 编译前请先安装CMake, 除标准库外不依赖其他任何C库

然后执行如下指令:
```
	mkdir build
	cd build
	cmake ..
	make
```

构建好的可执行文件会放置到bin目录下, 生成的链接库文件在build目录下
默认使用clang构建, 如果没有, 可以将CMakeLists下的编译器设置换成gcc或mingw-gcc:
```
SET (CMAKE_C_COMPILER_ENV_VAR "clang")
```

### 文档生成

本项目文档存放于doc目录下, 为md文本格式
同时使用doxygen生成文档, 需要先安装doxygen工具.
然后在build目录下执行:

```
	make doc
```
生成html和latex版的文档, 推荐使用html网页版, 较为方便

### 测试构建

本项目的测试框架使用gtest, 默认编译是不开启test编译的, 如需运行测试, 请打开CMakeLists下的编译开关
并且确保电脑上配置有gtest库
测试使用C++编译环境, 默认为clang++, 需要修改的请自行更改test下的CMakeLists配置文件


### 代码示例

C风格代码：

```
defun work(x) {
	print("work1:", x);
	print("work2:", x);
	print("work3:", x);
}

work(15);
```


Lisp风格代码

```
`(defun write (x y)   ; 这里是定义函数
	(print x y x)    ; 这是库里面的函数
)

`(let (x y)			; let宏负责开启一个局部环境, 并且你可以在let 后面声明一些局部变量
	(print x y)
	(hello) 		; 测试用C函数
)

`(write "ok" "test") ; 调用函数
```

两者是等价的，可以在同一文件中混用。

### 嵌入式用例

这款语言仿照lua的设计思路制成, 使用方法很接近, C接口通过从虚拟机的栈里获取参数, 返回时自行压栈

开启一个虚拟机非常方便, 可以用如下代码:
```
	slip_Core* vm = slipC_createCore(); // 启动一个虚拟机内核
	slipL_openStdLib(vm);				// 打开标准库
	slipC_loadFile(vm, file_in_name);   // 加载一个文件
```


栈的索引 1-栈顶 -1到栈底
栈上元素的可以用函数获取到:
```
	slipV_getValue (slip_Core* vm, int index);
```

定义C接口函数示例:
```
static int _print (slip_Core* vm, int num) {  // print函数原型
	for (int i = -num; i < 0; ++i)		// 从-num 到 -1, 是最后压栈的num个元素
	{
		slip_Value v = slipV_getValue(vm, i);
		slipV_printValue(&v); printf("\t");
	}
	slipV_popValueNum(vm, num); // 弹出元素
	printf("\n");
	return 0;  // 返回压栈元素个数
}

const slip_Reg stdlib[] = {  // 注册结构体
	{ "print", _print },
	{ NULL, NULL }
};
```

然后在创建虚拟机后, 执行注册函数:
```
	slipL_regGlobalCfuncs(vm, stdlib); // 注册C函数
	slipL_regGlobalCMacros(vm, stdmacro); // 注册C宏
```



MIT 协议
