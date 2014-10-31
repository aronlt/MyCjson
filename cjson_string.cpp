#include "cjson_string.h"

namespace MyCJson{
	const unsigned char CStringItem::firstByteMark[7] = { 0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };

	const char* CStringItem::Parse(const char *str){
		const char *ptr = str + 1;
		CHAR_VEC *ptr2 = nullptr;
		CHAR_VEC *out = value.pValString;
		int len = 0;
		unsigned uc, uc2;

		/* not a string! */
		if (*str != '\"'){
			ep = str;
			return nullptr;
		}
		/*calculate how much memory*/
		while (*ptr != '\"' && *ptr && ++len){
			if (*ptr++ == '\\'){
				ptr++;	/* Skip escaped quotes. */
			}
		}
		out->reserve(len + 1);	/* This is how long we need for the string, roughly. */

		ptr = str + 1;
		ptr2 = out;

		while (*ptr != '\"' && *ptr){
			if (*ptr != '\\'){
				ptr2->push_back(*ptr);
				++ptr;
			}
			else
			{
				ptr++;
				switch (*ptr)
				{
				case 'b':
					ptr2->push_back('\b');
					++ptr2;
					break;
				case 'f':
					ptr2->push_back('\f');
					++ptr2;
					break;
				case 'n':
					ptr2->push_back('\n');
					++ptr2;
					break;
				case 'r':
					ptr2->push_back('\r');
					++ptr2;
					break;

				case 't':
					ptr2->push_back('\t');
					++ptr2;
					break;
				case 'u':
					/* transcode utf16 to utf8. */
					uc = ParseHex4(ptr + 1);
					/* get the unicode char. */
					ptr += 4;
					/* check for invalid.*/
					if ((uc >= 0xDC00 && uc <= 0xDFFF) || uc == 0){
						break;
					}
					/* UTF16 surrogate pairs.*/
					if (uc >= 0xD800 && uc <= 0xDBFF){
						/* missing second-half of surrogate.*/
						if (ptr[1] != '\\' || ptr[2] != 'u'){
							break;
						}
						uc2 = ParseHex4(ptr + 3);
						ptr += 6;
						/* invalid second-half of surrogate.*/
						if (uc2 < 0xDC00 || uc2>0xDFFF){
							break;
						}
						uc = 0x10000 + (((uc & 0x3FF) << 10) | (uc2 & 0x3FF));
					}

					len = 4;
					if (uc < 0x80){
						len = 1;
					}
					else if (uc < 0x800){
						len = 2;
					}
					else if (uc < 0x10000){
						len = 3;
					}
					ptr2 += len;

					switch (len) {
					case 4:
						--ptr2;
						ptr2->push_back(((uc | 0x80) & 0xBF));
						uc >>= 6;
					case 3:
						--ptr2;
						ptr2->push_back(((uc | 0x80) & 0xBF));
						uc >>= 6;
					case 2:
						--ptr2;
						ptr2->push_back(((uc | 0x80) & 0xBF));
						uc >>= 6;
					case 1:
						--ptr2;
						ptr2->push_back(uc | firstByteMark[len]);
					}
					ptr2 += len;
					break;
				default:
					ptr2->push_back(*ptr);
					break;
				}
				ptr++;
			}
		}
		
		if (*ptr == '\"') {
			ptr++;
		}
		else{
			ep = ptr;
			return nullptr;
		}
		ptr2->push_back('\0');
		return ptr;
	}
	unsigned CStringItem::Hex4(const char *str){
		unsigned h = 0;
		if (*str >= '0' && *str <= '9'){
			h += (*str) - '0';
		}
		else if (*str >= 'A' && *str <= 'F') {
			h += 10 + (*str) - 'A';
		}
		else if (*str >= 'a' && *str <= 'f'){
			h += 10 + (*str) - 'a';
		}
		else return 0;
	}
	unsigned CStringItem::ParseHex4(const char *str)
	{
		unsigned h = 0;
		for (int i = 0; i < 4; ++i){
			h += Hex4(str);
			h = h << 4;
			++str;
		}
		return h;
	}

	void CStringItem::Print(CHAR_VEC &container, int depth){
		if (value.pValString->empty()){
			container.push_back('\"');
			container.push_back('\n');
			container.push_back('\"');
			return;
		}

		container.push_back('\"');
		for (int i = 0; i < value.pValString->size(); ++i){
			char ch = value.pValString->at(i);
			if ((unsigned char)ch > 31 && ch != '\"' && ch != '\\'){
				container.push_back(ch);
			}
			else{
				if (ch == '\0'){
					break;
				}
				container.push_back('\\');
				switch (ch)
				{
				case '\\':
					container.push_back('\\');
					break;
				case '\"':
					container.push_back('\"');
					break;
				case '\b':
					container.push_back('b');
					break;
				case '\f':
					container.push_back('f');
					break;
				case '\n':
					container.push_back('n');
					break;
				case '\r':
					container.push_back('r');
					break;
				case '\t':
					container.push_back('t');
					break;
				default: 
					/* escape and print */
					char p[10];
					sprintf_s(p, 10, "u%04x", ch); 
					for (int j = 0; j < strlen(p); ++j){
						container.push_back(p[j]);
					}
					break;	
				}
			}
		}
		container.push_back('\"');
		container.push_back('\0');
	}

	CStringItem::~CStringItem(){
		delete(value.pValString);
	}

	CStringItem::CStringItem(){
		value.pValString = new CHAR_VEC();
	}

}


