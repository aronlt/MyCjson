#include <stdlib.h>
#include "cjson_number.h"

namespace MyCJson{
	const char* CNumberItem::Parse(const char *num){
		double n = 0, sign = 1, scale = 0;
		int subscale = 0, signsubscale = 1;

		//Has sign?
		if (*num == '-'){
			sign = -1;
			++num;
		}

		//is zero
		if (*num == '0'){
			++num;
		}
		//Number?
		if (*num >= '1' && *num <= '9'){
			do{
				n = (n*10.0) + (*num++ - '0');
			} while (*num >= '0' && *num <= '9');
		}

		//Fractional part?
		if (*num == '.' && num[1] >= '0' && num[1] <= '9') {
			++num;
			do{
				n = (n*10.0) + (*num++ - '0');
				--scale;
			} while (*num >= '0' && *num <= '9');
		}

		//Exponent?
		if (*num == 'e' || *num == 'E'){
			++num;
			//With sign?
			if (*num == '+'){
				++num;
			}
			else if (*num == '-'){
				signsubscale = -1;
				++num;
			}
			//Number?
			while (*num >= '0' && *num <= '9'){
				subscale = (subscale * 10) + (*num++ - '0');
			}
		}
		//number = +/- number.fraction * 10^+/- exponent
		n = sign*n*pow(10.0, (scale + subscale * signsubscale));

		value.number.valDouble = n;
		value.number.valInt = (int)n;
		return num;
	}

	void CNumberItem::Print(CHAR_VEC &container, int depth){
		char *str;
		double d = value.number.valDouble;

		if (fabs(((double)value.number.valInt) - d) <= DBL_EPSILON && d <= INT_MAX && d >= INT_MIN){
			//2^64+1 can be represented in 21 chars.
			str = (char*)malloc(21);	
			if (str){
				sprintf_s(str, 21, "%d", value.number.valInt);
			}
			else{
				exit(EXIT_FAILURE);
			}
		}
		else{
			//This is a nice tradeoff.
			str = (char*)malloc(64);	
			if (str){
				if (fabs(floor(d) - d) <= DBL_EPSILON && fabs(d) < 1.0e60){
					sprintf_s(str, 64, "%.0f", d);
				}
				else if (fabs(d) < 1.0e-6 || fabs(d) > 1.0e9){
					sprintf_s(str, 64, "%e", d);
				}
				else{
					sprintf_s(str, 64, "%f", d);
				}
			}
			else{
				exit(EXIT_FAILURE);
			}
		}

		for (int i = 0; i < (int)strlen(str); ++i){
			container.push_back(str[i]);
		}
		free(str);
	}

	int CNumberItem::GetInt(){
		return value.number.valInt;
	}

	double CNumberItem::GetDouble(){
		return value.number.valDouble;
	}

}