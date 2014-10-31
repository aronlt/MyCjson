#include <utility>
#include "cjson_array.h"

namespace MyCJson{
	using std::get;
	using std::tuple;

	const char * CArrayItem::Parse(const char *value){
		/* not an array! */
		if (*value != '['){
			ep = value;
			return 0;
		}
		value = skip(value + 1);
		/* empty array. */
		if (*value == ']'){
			return value + 1;
		}

		/* skip any spacing, get the value. */
		value = ParseItem(value);
		if (!value) return 0;

		while (*value == ',')
		{
			//Ìø¹ý','
			value = skip(value + 1);
			value = ParseItem(value);
			value = skip(value);
			/* memory fail */
			if (!value){
				ep = value;
				return nullptr;
			}
		}

		/* end of array */
		if (*value == ']'){
			return value + 1;
		}
		/* malformed. */
		ep = value;
		return nullptr;
	}

	const char* CArrayItem::ParseItem(const char *value){
		CBaseItem::ParseRet ret;
		ret = PraseValue(value);
		if (get<0>(ret) == nullptr && get<1>(ret) == nullptr){
			ep = value;
			return nullptr;
		}
		value = get<1>(ret);
		child.push_back(get<0>(ret));
		return value;
	}

	void CArrayItem::AddItem(CBaseItem *item){
		child.push_back(item);
	}

	CBaseItem* CArrayItem::DetachItem(int idx){
		if (idx >= (int)child.size()){
			return nullptr;
		}
		CBaseItem *p = child[idx];
		child.erase(child.begin() + idx);
		return p;
	}

	void CArrayItem::DeleteItem(int idx){
		delete(DetachItem(idx));
	}

	CBaseItem* CArrayItem::GetItem(int idx){
		if (idx >= (int)child.size()){
			return nullptr;
		}
		return child[idx];
	}

	void CArrayItem::ReplaceItem(int idx, CBaseItem *item){
		CBaseItem *p = GetItem(idx);
		if (!p){
			exit(EXIT_FAILURE);
		}
		delete(p);
		child[idx] = item;
	}

	void CArrayItem::Print(CHAR_VEC &container, int depth){
		if (child.empty()){
			container.push_back('[');
			container.push_back('\t');
			container.push_back(']');
			return;
		}
		container.push_back('[');

		for (int i = 0; i < (int)child.size(); ++i){
			child[i]->Print(container, depth);
			if (i != child.size() - 1){
				container.push_back(',');
				container.push_back(' ');
			}
		}
		container.push_back(']');
		container.push_back('\0');
	}

	CArrayItem::~CArrayItem(){
		for (auto iter : child){
			delete(iter);
		}
	}
}


/******************************²âÊÔº¯Êý*******************************/
//#include <vector>
//#include <iostream>
//#include "cjson_string.h"
//#include "cjson_number.h"
//using namespace std;
//
//void test1(){
//	char *p = "[\"Sunday\", \"Monday\", \"Tuesday\", \"Wednesday\", \"Thursday\", \"Friday\", \"Saturday\"]";
//	MyCJson::CArrayItem array;
//	array.Parse(p);
//	//²âÊÔAddItemº¯Êý
//	MyCJson::CStringItem *strObj = new MyCJson::CStringItem();
//	char *q = "\"hello, my name is lintong\"";
//	strObj->Parse(q);
//	array.AddItem(strObj);
//
//	//²âÊÔGetItemº¯Êý
//	//MyCJson::CBaseItem *item = nullptr;
//	//item = array.GetItem(0);
//	//MyCJson::CBaseItem::CHAR_VEC container;
//	//item->Print(container);
//	//for (auto iter : container){
//	//	cout << iter;
//	//}
//
//	//²âÊÔDeleteItemº¯Êý
//	array.DeleteItem(0);
//
//	//²âÊÔReplaceItemº¯Êý
//	MyCJson::CNumberItem *number = new MyCJson::CNumberItem();
//	char *r = "123e12";
//	number->Parse(r);
//	array.ReplaceItem(0, number);
//
//	MyCJson::CBaseItem::CHAR_VEC container;
//	array.Print(container);
//	for (auto iter : container){
//		cout << iter;
//	}
//}
//
//void test2(){
//	char *p = "[\n    [0, -1, 0],\n    [1, 0, 0],\n    [0, 0, 1]\n	]\n";
//	MyCJson::CArrayItem array;
//	array.Parse(p);
//	MyCJson::CBaseItem::CHAR_VEC container;
//	array.Print(container);
//	for (auto iter : container){
//		cout << iter;
//	}
//}
//
//void test3(){
//	char *p = "[\n{ \n	 \"precision\": \"zip\",\n	 \"Latitude\":  37.7668,\n	 \"Longitude\": -122.3959,\n	 \"Address\":   \"\",\n	 \"City\":      \"SAN FRANCISCO\",\n	 \"State\":     \"CA\",\n	 \"Zip\":       \"94107\",\n	 \"Country\":   \"US\"\n	 },\n	 {\n	 \"precision\": \"zip\",\n	 \"Latitude\":  37.371991,\n	 \"Longitude\": -122.026020,\n	 \"Address\":   \"\",\n	 \"City\":      \"SUNNYVALE\",\n	 \"State\":     \"CA\",\n	 \"Zip\":       \"94085\",\n	 \"Country\":   \"US\"\n	 }\n	 ]";
//	MyCJson::CArrayItem array;
//	array.Parse(p);
//	MyCJson::CBaseItem::CHAR_VEC container;
//	array.Print(container);
//	for (auto iter : container){
//		cout << iter;
//	}
//
//}
//int main(){
//	test1();
//	//test2();
//	//test3();
//	return 0;
//}