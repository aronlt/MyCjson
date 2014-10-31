#ifndef MyCjson_header
#define MyCjson_header
#include <vector>
#include <map>
#include <utility>
namespace MyCJson{
	//出错的指针
	extern const char *ep;

	//跳过空白符
	const char *skip(const char *in);

	//基类
	class CBaseItem{
	public:
		typedef std::vector<char> CHAR_VEC;
		typedef std::tuple<CBaseItem*, const char *> ParseRet;

		//数字类型（因为int 与 double处理逻辑一样，所以不加以区分)
		struct Nunmber{
			int valInt;
			double valDouble;
		};


		//json的值类型
		union Value{
			bool valBool;
			Nunmber number;
			CHAR_VEC *pValString;
		};


	public:
		virtual ~CBaseItem(){}
		//解析字符串，根据不同的特征生成不同的Item
		ParseRet PraseValue(const char *value);
		//打印字符串
		char * PrintValue(CBaseItem *item, int depth, int fmt);
		//子类自身的解析函数
		virtual const char *Parse(const char *pStr);
		virtual void Print(CHAR_VEC &container, int depth = 0);

	protected:
		CHAR_VEC *pName;
		Value value;

	};

	//NULL类
	class CNullItem :public CBaseItem{
	public:
		void Print(CHAR_VEC &container){
			container.push_back('n');
			container.push_back('u');
			container.push_back('l');
			container.push_back('l');
		}

	};
	//BOOL类
	class CBoolItem :public CBaseItem{
	public:
		CBoolItem(bool val){
			value.valBool = val;
		}
		void Print(CHAR_VEC &container){
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