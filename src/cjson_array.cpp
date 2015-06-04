#include <utility>
#include "cjson_array.h"
#include "cjson_utility.h"

namespace MyCJson{
	using std::get;
	using std::tuple;

	const char * CArrayItem::Parse(const char *value){

		//not an array
		if (!value || *value != '['){
			ep = value;
			return nullptr;
		}

		//Skip any spacing, get the value.
		value = Skip(value + 1);

		//empty array
		if (*value == ']'){
			return value + 1;
		}

		value = ParseItem(value);
		value = Skip(value);
		if (!value){
			ep = value;
			return nullptr;
		}

		while (*value == ','){
			//step over ',' then skip any blank after ','
			value = Skip(value + 1);
			value = ParseItem(value);

			//skip any blank before ','
			value = Skip(value);
			if (!value){
				ep = value;
				return nullptr;
			}
		}

		//end of array
		if (*value == ']'){
			return value + 1;
		}

		//malformed.
		ep = value;
		return nullptr;
	}

	const char* CArrayItem::ParseItem(const char *value){
		ParseRet ret;

		//repeat the parse process
		ret = PraseValue(value);
		if (get<0>(ret) == nullptr || get<1>(ret) == nullptr){
			ep = value;
			return nullptr;
		}
		value = get<1>(ret);
		child.push_back(get<0>(ret));
		return value;
	}

	void CArrayItem::AddItem(CBaseItem *item){
		if (item){
			child.push_back(item);
		}
	}

	CBaseItem* CArrayItem::DetachItem(int idx){
		if (idx >= (int)child.size() || idx < 0){
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
		if (idx >= (int)child.size() || idx < 0){
			return nullptr;
		}
		return child[idx];
	}

	void CArrayItem::ReplaceItem(int idx, CBaseItem *item){
		if (!item){
			return;
		}
		CBaseItem *p = GetItem(idx);
		if (!p){
			return;
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
			if (i != int(child.size() - 1)){
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

	int CArrayItem::GetSize(){
		return (int)child.size();
	}

}