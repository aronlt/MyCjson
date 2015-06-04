MyCjson
=======
采用C++语言重写了[CJson](http://sourceforge.net/projects/cjson/).
-------
重写内容：<br/>
1:Object类型采用Map存储子元素，可以方便查找对象<br/>
2:Array类型采用Vector存储子元素<br/>
3：采用vector<char>替代char*，从而避免了繁琐的内存管理<br/>
使用方式：
```c++
#include <vector>
#include <iostream>
#include "cjson.h"
using namespace MyCJson
int main(){
	
	CBaseItem item;
	char *pTest = "{\n\"name\": \"Jack(\\\"Bee\\\") Nimble\", \n\"format\": {\"type\":       \"rect\", \n\"width\":      1920, \n\"height\":     1080, \n\"interlace\":  false,\"frame rate\": 24\n}\n}";
	item.PraseValue(pTest);
	CBaseItem::CHAR_VEC container;
	item.Print(container);
	for(auto elem: container){
	  std::cout << elem;
	}
	return 0;
}
```
测试结果如下:<br/>
![结果](/doc/result.png)

具体的使用方式见[doc/API.md](/doc/API.md)文件
--------
