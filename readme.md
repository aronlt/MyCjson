MyCjson
=======
����C++������д��CJson��http://sourceforge.net/projects/cjson/��
-------
��д���ݣ�<br/>
1:Object���Ͳ���Map�洢��Ԫ�أ����Է�����Ҷ���<br/>
2:Array���Ͳ���Vector�洢��Ԫ��<br/>
3������vector<char>���char*���Ӷ������˷������ڴ����<br/>
ʹ�÷�ʽ��
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
�����ʹ�÷�ʽ�������ļ�
--------
