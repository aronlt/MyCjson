#ifndef CJSON_STRING_HEADER
#define CJSON_STRING_HEADER
#include "cjson.h"

namespace MyCJson{
	class CStringItem :public CBaseItem{
	public:
		CStringItem();
		~CStringItem();
		CHAR_VEC* GetData(){
			return value.pValString;
		}
		const char* Parse(const char *str);
		void Print(CHAR_VEC &container, int depth = 0);
	private:
		static const unsigned char firstByteMark[7];
		unsigned Hex4(const char *str);
		unsigned ParseHex4(const char *str);
	};
}
#endif