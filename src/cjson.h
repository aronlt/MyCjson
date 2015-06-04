#ifndef MYCJSON_JSON_HEADER
#define MYCJSON_JSON_HEADER
#include <vector>
#include <map>
#include <utility>
#include "cjson_utility.h"

namespace MyCJson{

	//error point
	extern const char *ep;

	//Skip blank
	const char *Skip(const char *in);

	//base class
	class CBaseItem{
	public:


		//digital type
		struct Nunmber{
			int valInt;
			double valDouble;
		};

		//type of value
		union Value{
			bool valBool;
			Nunmber number;
			CHAR_VEC *pValString;
		};

	public:
		virtual ~CBaseItem(){}

		//parse input string, then generate different Item
		ParseRet PraseValue(const char *value);

		//print string
		char * PrintValue(CBaseItem *item, int depth, int fmt);

		//derived class implement Parse function
		virtual const char *Parse(const char *pStr);

		//convert Item into string
		virtual void Print(CHAR_VEC &container, int depth = 0) = 0;

	protected:
		CHAR_VEC *pName;
		Value value;

	};

	//NULL
	class CNullItem :public CBaseItem{
	public:
		void Print(CHAR_VEC& container, int depth = 0){
			container.push_back('n');
			container.push_back('u');
			container.push_back('l');
			container.push_back('l');
		}
	};

	//BOOL
	class CBoolItem :public CBaseItem{
	public:
		CBoolItem(bool val){
			value.valBool = val;
		}
		bool GetBool(){
			return value.valBool;
		}
		void Print(CHAR_VEC& container, int depth = 0){
			if (value.valBool == true){
				container.push_back('t');
				container.push_back('r');
				container.push_back('u');
				container.push_back('e');
			}
			else{
				container.push_back('f');
				container.push_back('a');
				container.push_back('l');
				container.push_back('s');
				container.push_back('e');
			}
		}
	};
};

#endif