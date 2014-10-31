#ifndef MyCjson_header
#define MyCjson_header
#include <vector>
#include <map>
#include <utility>
namespace MyCJson{
	//�����ָ��
	extern const char *ep;

	//�����հ׷�
	const char *skip(const char *in);

	//����
	class CBaseItem{
	public:
		typedef std::vector<char> CHAR_VEC;
		typedef std::tuple<CBaseItem*, const char *> ParseRet;

		//�������ͣ���Ϊint �� double�����߼�һ�������Բ���������)
		struct Nunmber{
			int valInt;
			double valDouble;
		};


		//json��ֵ����
		union Value{
			bool valBool;
			Nunmber number;
			CHAR_VEC *pValString;
		};


	public:
		virtual ~CBaseItem(){}
		//�����ַ��������ݲ�ͬ���������ɲ�ͬ��Item
		ParseRet PraseValue(const char *value);
		//��ӡ�ַ���
		char * PrintValue(CBaseItem *item, int depth, int fmt);
		//��������Ľ�������
		virtual const char *Parse(const char *pStr);
		virtual void Print(CHAR_VEC &container, int depth = 0);

	protected:
		CHAR_VEC *pName;
		Value value;

	};

	//NULL��
	class CNullItem :public CBaseItem{
	public:
		void Print(CHAR_VEC &container){
			container.push_back('n');
			container.push_back('u');
			container.push_back('l');
			container.push_back('l');
		}

	};
	//BOOL��
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