#include <utility>
#include <string.h>
#include <stdlib.h>
#include "cjson.h"
#include "cjson_string.h"
#include "cjson_object.h"
#include "cjson_utility.h"

namespace MyCJson{
	using std::tuple;
	using std::get;

	const char * CObjectItem::Parse(const char *value){
		//is object?
		if (!value || *value != '{'){
			ep = value;
			return nullptr;
		}

		//skip blank after '{'
		value = Skip(value + 1);

		//empty object
		if (*value == '}'){
			return value + 1;
		}
		value = ParseItem(value);
		value = Skip(value);
		if (!value){
			return 	nullptr;
		}

		//parse Items in the object
		while (*value == ','){
			//skip blank after ',' 
			value = Skip(value + 1);
			value = ParseItem(value);
			value = Skip(value);
			if (!value){
				return nullptr;
			}
		}

		//end of object
		if (*value == '}') {
			return value + 1;
		}
		//malformed.
		ep = value;
		return nullptr;
	}


	const char* CObjectItem::ParseItem(const char *value){
		//parse key
		CStringItem *pNameObj = new CStringItem();
		value = Skip(pNameObj->Parse(Skip(value)));
		if (!value || *value != ':'){
			ep = value;
			return nullptr;
		}

		//parse value
		ParseRet ret;
		value = Skip(value + 1);
		ret = PraseValue(value);
		if (get<0>(ret) == nullptr && get<1>(ret) == nullptr){
			ep = value;
			return nullptr;
		}

		//add into child map
		value = get<1>(ret);
		child[*(pNameObj->GetData())] = get<0>(ret);
		delete(pNameObj);
		return value;
	}

	void CObjectItem::AddItem(const char* name, CBaseItem *item){
		if (!name || !item){
			return;
		}
		CHAR_VEC p = StrToVec(name);
		child[p] = item;
	}

	CHAR_VEC CObjectItem::StrToVec(const char* str){
		if (!str){
			exit(EXIT_FAILURE);
		}

		size_t len = strlen(str) + 1;
		CHAR_VEC p;
		p.reserve(len);

		//delete '\"' in str
		for (int i = 0; i < (int)strlen(str); ++i){
			if (str[i] != '\"'){
				p.push_back(str[i]);
			}
		}
		p.push_back('\0');
		return p;
	}

	CBaseItem * CObjectItem::GetItem(const char *str){
		CHAR_VEC p = StrToVec(str);
		auto iter = child.find(p);
		if (iter != child.end()){
			return iter->second;
		}
		return nullptr;
	}

	CBaseItem* CObjectItem::DetachItem(const char *str){
		CBaseItem *ret = nullptr;
		CHAR_VEC p = StrToVec(str);
		auto iter = child.find(p);
		if (iter != child.end()){
			ret = iter->second;
			child.erase(iter);
		}
		return ret;
	}

	void CObjectItem::DeleteItem(const char *str){
		CBaseItem *p = DetachItem(str);
		delete(p);
	}

	void CObjectItem::ReplaceItem(const char *str, CBaseItem *item){
		if (!str || !item){
			return;
		}
		CBaseItem *p = GetItem(str);
		if (!p){
			return;
		}
		delete(p);

		CHAR_VEC name = StrToVec(str);
		child[name] = item;
	}

	void CObjectItem::Print(CHAR_VEC &container, int depth){
		//handle empty object
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