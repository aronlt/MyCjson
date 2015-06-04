#include <utility>
#include <stdlib.h>
#include "cjson.h"
#include "cjson_number.h"
#include "cjson_string.h"
#include "cjson_array.h"
#include "cjson_object.h"
#include "cjson_utility.h"

namespace MyCJson{
	using std::tuple;
	using std::get;
	const char *ep;

	const char * Skip(const char *in){
		while (in && *in && (unsigned char)*in <= 32) {
			++in;
		}
		return in;
	}

	ParseRet CBaseItem::PraseValue(const char *value){
		ParseRet ret;
		get<0>(ret) = nullptr;
		get<1>(ret) = nullptr;

		//fail on null
		if (!value){
			return ret;
		}

		//Skip blank, tab
		value = Skip(value);

		//deal with different Item
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

		// failure
		ep = value;
		return ret;
	}

	char* CBaseItem::PrintValue(CBaseItem* item, int depth, int fmt){
		if (!item) {
			return nullptr;
		}
		CHAR_VEC container;
		item->Print(container);
		char* out = (char *)malloc(sizeof(char) * container.size());
		if (!out){
			return nullptr;
		}
		for (size_t i = 0; i < container.size(); ++i){
			out[i] = container[i];
		}
		return out;
	}

	const char * CBaseItem::Parse(const char *pStr){
		return nullptr;
	}

	void CBaseItem::Print(CHAR_VEC &container, int depth /*= 0*/){
	}

}