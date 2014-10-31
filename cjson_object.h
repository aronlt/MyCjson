#ifndef CJSON_OBJECT_HEADER
#define CJSON_OBJECT_HEADER
#include "cjson.h"
namespace MyCJson{

	//CObject ΪObjectʵ�ֵ���
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
		//����Item
		const char* ParseItem(const char *value);
		//��char*ת��ΪCHARE_VEC
		CHAR_VEC StrToVec(const char* str);

	private:
		//���ӽڵ�
		ObjMap child;
	};
}
#endif // !MY_OBJECT_HEADER
