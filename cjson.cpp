#include <utility>
#include <stdlib.h>
#include "cjson.h"
#include "cjson_number.h"
#include "cjson_string.h"
#include "cjson_array.h"
#include "cjson_object.h"

namespace MyCJson{
	using std::tuple;
	using std::get;

	CBaseItem::ParseRet CBaseItem::PraseValue(const char *value)
	{
		/* Fail on null. */
		ParseRet ret;
		get<0>(ret) = nullptr;
		get<1>(ret) = nullptr;


		if (!value){
			get<1>(ret) = nullptr;
			return ret;
		}
		value = skip(value);
		if (!strncmp(value, "null", 4)){
			get<0>(ret) = new CNullItem();
			get<1>(ret) = value + 4;
			return ret;
		}
		if (!strncmp(value, "false", 5)){
			get<0>(ret) = new CBoolItem(false);;
			get<1>(ret) = value + 5;
			return ret;
		}
		if (!strncmp(value, "true", 4))	{
			get<0>(ret) = new CBoolItem(true);
			get<1>(ret) = value + 4;
			return ret;
		}
		if (*value == '\"'){
			CStringItem *pItem = new CStringItem();
			value = pItem->Parse(value);
			get<0>(ret) = pItem;
			get<1>(ret) = value;
			return ret;
		}
		if (*value == '-' || (*value >= '0' && *value <= '9')){
			CNumberItem *pItem = new CNumberItem();
			value = pItem->Parse(value);
			get<0>(ret) = pItem;
			get<1>(ret) = value;
			return ret;
		}
		if (*value == '['){
			CArrayItem *pItem = new CArrayItem();
			value = pItem->Parse(value);
			get<0>(ret) = pItem;
			get<1>(ret) = value;
			return ret;
		}
		if (*value == '{'){
			CObjectItem *pItem = new CObjectItem();
			value = pItem->Parse(value);
			get<0>(ret) = pItem;
			get<1>(ret) = value;
			return ret;
		}
		/* failure. */
		ep = value;
		return ret;
	}

	char * CBaseItem::PrintValue(CBaseItem *item, int depth, int fmt){
		if (!item) {
			return nullptr;
		}
		char *out = 0;
		CHAR_VEC container;
		item->Print(container);
		out = (char *)malloc(sizeof(char) * container.size());
		if (!out){
			return nullptr;
		}
		for (int i = 0; i < container.size(); ++i){
			out[i] = container[i];
		}
		return out;
	}

	const char * CBaseItem::Parse(const char *pStr)
	{
		return nullptr;
	}

	void CBaseItem::Print(CHAR_VEC &container, int depth){
	}

	const char * skip(const char *in){
		while (in && *in && (unsigned char)*in <= 32) {
			in++;
		}
		return in;
	}
	const char *ep;
}

///*
//²âÊÔº¯Êý
//*/
//using namespace MyCJson;
//int main(){
//	CBaseItem item;
//	char *pTest = "{\n\"name\": \"Jack(\\\"Bee\\\") Nimble\", \n\"format\": {\"type\":       \"rect\", \n\"width\":      1920, \n\"height\":     1080, \n\"interlace\":  false,\"frame rate\": 24\n}\n}";
//	item.PraseValue(pTest);
//
//	return 0;
//}