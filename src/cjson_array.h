#ifndef MYCJSON_ARRAY_HEADER
#define MYCJSON_ARRAY_HEADER
#include "cjson.h"
#include "cjson_utility.h"

namespace MyCJson{

	//Array class
	class CArrayItem : public CBaseItem
	{
	public:
		virtual ~CArrayItem();
		const char *Parse(const char *value);
		void Print(CHAR_VEC &container, int depth = 0);
		int GetSize();
		void AddItem(CBaseItem *item);
		CBaseItem* DetachItem(int idx);
		CBaseItem* GetItem(int idx);
		void DeleteItem(int idx);
		void ReplaceItem(int idx, CBaseItem *item);

	private:
		ObjArray child;

	protected:
		const char* ParseItem(const char *value);
	};
}

#endif