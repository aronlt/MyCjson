#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "cjson_object.h"

using namespace MyCJson;
using namespace std;

void test(const string &ifile, const string &ofile){
	ifstream f;
	ofstream out;
	f.open(ifile.c_str());
	out.open(ofile.c_str());
	string data;
	string line;
	while (getline(f, line)){
		data += line;
	}

	CObjectItem obj;
	obj.Parse(data.c_str());
	CBaseItem::CHAR_VEC container;
	obj.Print(container);

	for (auto elem : container){
		out << elem;
	}
	f.close();
	out.close();
}


int main(){

	vector<pair<string, string>> files;
	files.push_back(make_pair("C:\\Users\\lintong\\Desktop\\tests\\test1.txt", "C:\\Users\\lintong\\Desktop\\tests\\test1_result.txt"));
	files.push_back(make_pair("C:\\Users\\lintong\\Desktop\\tests\\test2.txt", "C:\\Users\\lintong\\Desktop\\tests\\test2_result.txt"));
	files.push_back(make_pair("C:\\Users\\lintong\\Desktop\\tests\\test3.txt", "C:\\Users\\lintong\\Desktop\\tests\\test3_result.txt"));
	files.push_back(make_pair("C:\\Users\\lintong\\Desktop\\tests\\test4.txt", "C:\\Users\\lintong\\Desktop\\tests\\test4_result.txt"));
	files.push_back(make_pair("C:\\Users\\lintong\\Desktop\\tests\\test5.txt", "C:\\Users\\lintong\\Desktop\\tests\\test5_result.txt"));

	for (auto elem : files){
		test(elem.first, elem.second);
	}

	return 0;
}