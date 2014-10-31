#ifndef CJSON_OBJECT_HEADER
#define CJSON_OBJECT_HEADER
#include "cjson.h"
namespace MyCJson{

	//CObject 为Object实现的类
	class CObjectItem :public CBaseItem{
	public:
		typedef std::map<CHAR_VEC, CBaseItem *> ObjMap;

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

	protected:
		//解析Item
		const char* ParseItem(const char *value);
		//将char*转换为CHARE_VEC
		CHAR_VEC StrToVec(const char* str);

	private:
		//孩子节点
		ObjMap child;
	};
}
#endif // !MY_OBJECT_HEADER
