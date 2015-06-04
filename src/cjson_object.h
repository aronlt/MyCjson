#ifndef MYCJSON_OBJECT_HEADER
#define MYCJSON_OBJECT_HEADER
#include "cjson.h"
#include "cjson_object.h"

namespace MyCJson{

	//Object class
	class CObjectItem :public CBaseItem{
	public:
		CObjectItem(){
		}
		virtual ~CObjectItem();
		const char* Parse(const char *value);
		void Print(CHAR_VEC &container, int depth = 0);
		void AddItem(const char* name, CBaseItem *item);
		CBaseItem *GetItem(const char *str);
		CBaseItem* DetachItem(const char *str);
		void DeleteItem(const char *str);
		void ReplaceItem(const char *str, CBaseItem *item);
		static CHAR_VEC StrToVec(const char* str);

	protected:
		//Parse Item
		const char* ParseItem(const char *value);
		//convert char* to CHAR_VEC

	private:
		//Child nodes
		ObjMap child;
	};
}
#endif
