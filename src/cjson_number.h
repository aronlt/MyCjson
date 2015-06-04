#ifndef MYCJSON_NUMBER_HEADER
#define MYCJSON_NUMBER_HEADER
#include "cjson.h"
namespace MyCJson{
	//number class
	class CNumberItem :public CBaseItem{
	public:
		const char* Parse(const char *num);
		void Print(CHAR_VEC &container, int depth = 0);
		int GetInt();
		double GetDouble();
	};
}

#endif