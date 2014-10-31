#include <utility>
#include <string.h>
#include <stdlib.h>
#include "cjson.h"
#include "cjson_string.h"
#include "cjson_object.h"


namespace MyCJson{
	using std::tuple;
	using std::get;

	const char * CObjectItem::Parse(const char *value){
		//判断是否出错
		if (*value != '{'){
			ep = value;
			return nullptr;
		}
		//跳过空白
		value = skip(value + 1);
		//空的object
		if (*value == '}'){
			return value + 1;
		}
		value = skip(ParseItem(value));
		if (!value){
			return 	nullptr;
		}
		//解析多个元素
		while (*value == ','){
			//跳过','
			value = skip(value + 1);
			value = skip(ParseItem(value));
			if (!value){
				return nullptr;
			}
		}
		/* end of object */
		if (*value == '}') {
			return value + 1;
		}
		/* malformed. */
		ep = value;
		return nullptr;
	}


	const char* CObjectItem::ParseItem(const char *value){
		//解析 Name：
		CStringItem *pNameObj = new CStringItem();
		value = skip(pNameObj->Parse(skip(value)));
		if (!value || *value != ':'){
			ep = value;
			return nullptr;
		}

		//解析该name对应的值
		CBaseItem::ParseRet ret;
		value = skip(value + 1);
		ret = PraseValue(value);
		if (get<0>(ret) == nullptr && get<1>(ret) == nullptr){
			ep = value;
			return nullptr;
		}
		//将元素放入child容器中
		value = get<1>(ret);
		child[*(pNameObj->GetData())] = get<0>(ret);
		delete(pNameObj);
		return value;
	}

	void CObjectItem::AddItem(const char* name, CBaseItem *item){
		CHAR_VEC p = StrToVec(name);
		child[p] = item;
	}

	CBaseItem::CHAR_VEC CObjectItem::StrToVec(const char* str){
		if (!str){
			exit(EXIT_FAILURE);
		}

		size_t len;
		len = strlen(str) + 1;
		CHAR_VEC p;
		p.reserve(len);
		//将str中的\"去掉
		for (int i = 0; i < strlen(str); ++i){
			if (str[i] != '\"'){
				p.push_back(str[i]);
			}
		}
		p.push_back('\0');
		return p;
	}

	CBaseItem * CObjectItem::GetItem(const char *str){
		CHAR_VEC p = StrToVec(str);
		ObjMap::iterator iter = child.find(p);
		if (iter != child.end()){
			return iter->second;
		}
		return nullptr;
	}

	CBaseItem* CObjectItem::DetachItem(const char *str){
		CHAR_VEC p = StrToVec(str);
		auto iter = child.find(p);
		CBaseItem *ret = nullptr;
		if (iter != child.end()){
			ret = iter->second;
		}
		child.erase(iter);
		return ret;
	}

	void CObjectItem::DeleteItem(const char *str){
		CBaseItem *p = DetachItem(str);
		delete(p);
	}

	void CObjectItem::ReplaceItem(const char *str, CBaseItem *item){
		CBaseItem *p = GetItem(str);
		if (!p){
			return;
		}
		delete(p);

		CHAR_VEC name = StrToVec(str);
		child[name] = item;
	}

	void CObjectItem::Print(CHAR_VEC &container, int depth){
		/*handle empty object*/
		if (child.empty()){
			container.push_back('{');
			container.push_back('\n');
			container.push_back('\t');
			container.push_back('}');
			return;
		}

		int k = depth;
		container.push_back('\n');
		for (int i = 0; i < k; ++i){
			container.push_back('\t');
		}
		container.push_back('{');
		container.push_back('\n');

		++depth;
		for (auto elem : child){
			for (int j = 0; j < depth; ++j){
				container.push_back('\t');
			}
			container.insert(container.end(), '\"');
			container.insert(container.end(), elem.first.begin(), elem.first.end());
			container.insert(container.end() - 1, '\"');
			
			container.push_back(':');
			container.push_back('\t');
			elem.second->Print(container, depth);
			auto iter = child.end();
			--iter;
			if (elem != *iter){
				container.push_back(',');
			}
			container.push_back('\n');
		}
		container.push_back('\n');
		for (int i = 0; i < k; ++i){
			container.push_back('\t');
		}
		container.push_back('}');
		container.push_back('\0');
	}

	CObjectItem::~CObjectItem(){
		for (auto iter : child){
			delete(iter.second);
		}
	}

}


///***************测试函数*********************************/
//
//#include <vector>
//#include <iostream>
//using namespace std;
//void test1(){
//	char *p = "{ \n\"name\": \"Jack(\\\"Bee\\\") Nimble\", \n\"format\": {\"type\":       \"rect\", \n\"width\":      1920.001, \n\"height\":     1080, \n\"interlace\":  false,\"frame rate\": 24\n}\n}";
//
//	MyCJson::CObjectItem obj;
//	//测试Parse函数
//	obj.Parse(p);
//
//	MyCJson::CStringItem *str = new MyCJson::CStringItem();
//
//	str->Parse("\"lintong\"");
//	//测试AddItem函数
//	obj.AddItem("\"nihao\"", str);
//
//	//测试DeleteItem函数
//	obj.DeleteItem("\"nihao\"");
//
//	//测试Replace函数
//	MyCJson::CStringItem *str2 = new MyCJson::CStringItem();
//	str2->Parse("\"林通\"");
//	obj.ReplaceItem("\"name\"", str2);
//	std::vector<char> container;
//
//	//测试Print函数
//	obj.Print(container);
//	for (auto elem : container){
//		cout << elem;
//	}
//}
//void test2(){
//	char *p = "{\n		\"Image\": {\n			\"Width\":  800,\n			\"Height\": 600,\n			\"Title\":  \"View from 15th Floor\",\n			\"Thumbnail\": {\n				\"Url\":    \"http:/*www.example.com/image/481989943\",\n				\"Height\": 125,\n				\"Width\":  \"100\"\n			},\n			\"IDs\": [116, 943, 234, 38793]\n		}\n	}";
//	MyCJson::CObjectItem obj;
//	obj.Parse(p);
//	std::vector<char> container;
//	obj.Print(container);
//	for (auto elem : container){
//		cout << elem;
//	}
//}
//int main(){
//	test1();
//	test2();
//	return 0;
//}