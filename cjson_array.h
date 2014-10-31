#ifndef CJSON_ARRAY_HEADER
#define CJSON_ARRAY_HEADER
#include "cjson.h"
namespace MyCJson{
	//CArray 为Array实现的类
	class CArrayItem : public CBaseItem
	{
	public:
		typedef std::vector<CBaseItem *> ObjArray;

	public:
		virtual ~CArrayItem();
		const char *Parse(const char *value);
		void Print(CHAR_VEC &container, int depth = 0);
		int GetSize(){
			return child.size();
		}
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