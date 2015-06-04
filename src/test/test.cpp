#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include "../cjson_object.h"
#include "../cjson_array.h"
#include "../cjson_number.h"
#include "../cjson_string.h"
#include "../cjson.h"

using namespace std;
using MyCJson::CNumberItem;
using MyCJson::CStringItem;
using MyCJson::CArrayItem;
using MyCJson::CBoolItem;
using MyCJson::CObjectItem;
using MyCJson::CNullItem;
using MyCJson::CHAR_VEC;
using MyCJson::CBaseItem;


static bool CheckValue(CObjectItem &obj, const char* key, const char *value){
	CStringItem* strItem = (CStringItem *)obj.GetItem(key);
	CHAR_VEC *charVec = strItem->GetData();
	CHAR_VEC vec = CObjectItem::StrToVec(value);
	return equal(charVec->begin(), charVec->end(), vec.begin());
}


static void PutToFile(const char* filename, CBaseItem* item){
	//Test Print
	ofstream out;
	out.open(filename);
	if (out.is_open() == false){
		return;
	}
	vector<char> container;
	item->Print(container);
	for (auto elem : container){
		out << elem;
	}
	out << endl;
	out.close();
}

void TestByFile(const string &ifile, const string &ofile){
	ifstream f;
	ofstream out;
	f.open(ifile.c_str());
	out.open(ofile.c_str());
	if (f.is_open() == false || out.is_open() == false){
		return;
	}
	string data;
	string line;
	while (getline(f, line)){
		data += line;
	}

	CObjectItem obj;
	obj.Parse(data.c_str());
	CHAR_VEC container;
	obj.Print(container);
	for (auto elem : container){
		out << elem;
	}
	f.close();
	out.close();
}

bool TestObject(){
	const char* p = "{ \n\"name\": \"Jack(\\\"Bee\\\") Nimble\", \n\"format\": {\"type\":       \"rect\", \n\"width\":      1920.001, \n\"height\":     1080, \n\"interlace\":  false,\"frame rate\": 24\n}\n}";
	const char *q = "{\n		\"Image\": {\n			\"Width\":  800,\n			\"Height\": 600,\n			\"Title\":  \"View from 15th Floor\",\n			\"Thumbnail\": {\n				\"Url\":    \"http:/*www.example.com/image/481989943\",\n				\"Height\": 125,\n				\"Width\":  \"100\"\n			},\n			\"IDs\": [116, 943, 234, 38793]\n		}\n	}";

	CObjectItem obj;
	CObjectItem obj2;

	//test parse(if parse false, it will return false)
	if (!obj.Parse(p) || !obj2.Parse(q)){
		return false;
	}

	PutToFile("tests\\test_object.txt", &obj);
	PutToFile("tests\\test_object.txt", &obj2);

	CStringItem *str = new CStringItem();
	const char* key = "\"lintong\"";
	const char* value = "\"nihao\"";
	if (!str->Parse(value)){
		return false;
	}

	//Test AddItem
	obj.AddItem(key, str);
	if (CheckValue(obj, key, value) == false){
		return false;
	}

	//Test Replace
	const char* value2 = "\"xiangwen\"";
	CStringItem *str2 = new CStringItem();
	str2->Parse(value2);
	obj.ReplaceItem(key, str2);
	if (CheckValue(obj, key, value2) == false){
		return false;
	}
	
	//Test DeleteItem
	obj.DeleteItem(key);
	if (obj.GetItem(key)){
		return false;
	}

	return true;
}



bool TestArray(){
	const char *p = "[\"Sunday\", \"Monday\", \"Tuesday\", \"Wednesday\", \"Thursday\", \"Friday\", \"Saturday\"]";
	const char *p2 = "[\n    [0, -1, 0],\n    [1, 0, 0],\n    [0, 0, 1]\n	]\n";
	const char *p3 = "[\n{ \n	 \"precision\": \"zip\",\n	 \"Latitude\":  37.7668,\n	 \"Longitude\": -122.3959,\n	 \"Address\":   \"\",\n	 \"City\":      \"SAN FRANCISCO\",\n	 \"State\":     \"CA\",\n	 \"Zip\":       \"94107\",\n	 \"Country\":   \"US\"\n	 },\n	 {\n	 \"precision\": \"zip\",\n	 \"Latitude\":  37.371991,\n	 \"Longitude\": -122.026020,\n	 \"Address\":   \"\",\n	 \"City\":      \"SUNNYVALE\",\n	 \"State\":     \"CA\",\n	 \"Zip\":       \"94085\",\n	 \"Country\":   \"US\"\n	 }\n	 ]";;

	CArrayItem array;
	CArrayItem array2;
	CArrayItem array3;
	if (!array.Parse(p) || !array2.Parse(p2) || !array3.Parse(p3)){
		return false;
	}

	PutToFile("tests\\test_array.txt", &array);
	PutToFile("tests\\test_array.txt", &array2);
	PutToFile("tests\\text_array.txt", &array3);

	//Test AddItem function
	CStringItem *strObj = new CStringItem();
	const char *item = "\"hello, my name is lintong\"";
	strObj->Parse(item);
	array.AddItem(strObj);
	CStringItem* elem = (CStringItem *)array.GetItem(7);
	CHAR_VEC *charVec = elem->GetData();
	CHAR_VEC vec = CObjectItem::StrToVec(item);
	if (equal(charVec->begin(), charVec->end(), vec.begin()) == false){
		return false;
	}

	//Test DeleteItem
	array.DeleteItem(0);


	//Test ReplaceItem
	CNumberItem *number = new MyCJson::CNumberItem();
	char *r = "123e12";
	number->Parse(r);
	array.ReplaceItem(0, number);

	//Test GetItem
	CNumberItem* numberElem = (CNumberItem*)array.GetItem(0);
	double a = numberElem->GetDouble();
	double b = 123e12;
	if (a != b){
		return false;
	}
	return true;

}
