#ifndef MYCJSON_UTILITY_HEADER
#define MYCJSON_UTILITY_HEADER

#include <vector>
#include <tuple>

namespace MyCJson{
	class CBaseItem;

	typedef std::vector<char> CHAR_VEC;
	typedef std::tuple<CBaseItem*, const char* > ParseRet;
	typedef std::vector<CBaseItem* > ObjArray;
	typedef std::map<CHAR_VEC, CBaseItem *> ObjMap;

}
#endif