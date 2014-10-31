#ifndef CJSON_NUMBER_HEADER
#define CJSON_NUMBER_HEADER
#include "cjson.h"
namespace MyCJson{
	class CNumberItem :public CBaseItem{
	public:
		const char* Parse(const char *num);
		void Print(CHAR_VEC &container, int depth = 0);
	};
}

#endif