#pragma once

#define _CRT_SECURE_NO_DEPRECATE  //vs2012以后的版本要加这两行
#define _CRT_NONSTDC_NO_DEPRECATE
//通过预编译方式去掉unicode字符集
#ifdef UNICODE
#undef UNICODE
#endif

#include<easyx.h>
#include<string>
#include<iostream>
#include<vector>
#include<conio.h>
#include<cstdlib>
#include<ctime>
#include<iostream>