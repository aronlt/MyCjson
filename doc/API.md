#####MyCjson采用C++语言，使用C++11新特性，以及STL库等对CJson软件进行了重写，使得重写后的软件更具有OOP特性，而且也更方便使用和扩展。<br/>MyCjson采用google test单元测试框架进行了测试。

###如何使用？
**CObjectItem:**<br/>
`const char* Parse(const char *value):`<br/>
传入const char *字符串，将其解析为Object类型，返回解析后剩下的字符串,如果解析失败，返回nullptr。<br/>
<br/>
`void Print(CHAR_VEC &container, int depth = 0):`<br/>
以字符形式打印Object的内容，将结果放入container中，其中CHAR_VEC表示vector<char>容器。depth表示缩进层次<br/>
<br/>
`void AddItem(const char* name, CBaseItem *item);`<br/>
将对象添加到Object中，name表示对象的key，item表示对象的value<br/>
<br/>
`CBaseItem *GetItem(const char *str);`<br/>
根据key(可以是以字符串形式存储),获取对象的value<br/>
<br/>
`CBaseItem* DetachItem(const char *str);`<br/>
根据key解除对象，并返回对象的值<br/>
<br/>
`void DeleteItem(const char *str);`<br/>
根据key删除对象<br/>
<br/>
`void ReplaceItem(const char *str, CBaseItem *item);`<br/>
替换对象<br/>
<br/>
`static CHAR_VEC StrToVec(const char* str);`<br/>
将字符串转换为CHAR_VEC类型（类静态方法）<br/>

**CArrayItem:**<br/>
`const char *Parse(const char *value);`<br/>
传入const char *字符串，将其解析为Array类型，返回解析后剩下的字符串，如果解析失败，则返回nullptr<br/>
<br/>
`void Print(CHAR_VEC &container, int depth = 0);`<br/>
以字符形式打印Array，将结果放入container中，其中CHAR_VEC表示vector<char>容器。depth表示缩进层次<br/>
<br/>
`int GetSize();`<br/>
获取数组的大小<br/>
<br/>
`void AddItem(CBaseItem *item);`<br/>
添加数组元素 <br/>
<br/>
`CBaseItem* DetachItem(int idx);`<br/>
根据索引解除对象，返回对象的值<br/>
<br/>
`CBaseItem* GetItem(int idx);`<br/>
根据索引获取对象的值<br/>
<br/>
`void DeleteItem(int idx);`<br/>
根据索引删除对象<br/>
<br/>
`void ReplaceItem(int idx, CBaseItem *item);`<br/>
根据索引替换对象<br/>

**CStringItem:**<br/>
`CHAR_VEC* GetData();`<br/>
获取CStringItem的字符串内容,以CHAR_VEC形式返回<br/>
<br/>
`const char* Parse(const char *str);`<br/>
将const char* 类型字符串解析为CStringItem类型，返回解析后剩下的字符串，如果解析失败，则返回nullptr型<br/>
<br/>
`void Print(CHAR_VEC& container, int depth = 0);`<br/>
以字符形式打印CStringItem，将结果放入container中，其中CHAR_VEC表示vector<char>容器。depth表示缩进层次<br/>
<br/>
**CNumberItem:**<br/>
`const char* Parse(const char *num);`<br/>
将const char*类型字符串转为CNumberItem类型,返回解析后剩下的字符串，如果解析失败，则返回nullptr<br/>
<br/>
`void Print(CHAR_VEC &container, int depth = 0);`<br/>
以字符形式打印CNumberItem，将结果放入container中，其中CHAR_VEC表示vector<char>容器。depth表示缩进层次<br/>

`int GetInt();`<br/>
以int的形式获取CNumberItem类型的值。<br/>
<br/>
`double GetDouble();`<br/>
以double的形式获取CNumberItem类型的值<br/>
<br/>
**CBoolItem:**<br/>
`CBoolItem(bool val);`<br/>
构造CBoolItem类型，传入bool值<br/>
<br/>
`bool GetBool()`<br/>
获取CBoolItem的值	<br/>
<br/>
`void Print(CHAR_VEC& container, int depth = 0);`<br/>
以字符形式打印CBoolItem，将结果放入container中，其中CHAR_VEC表示vector<char>容器。depth表示缩进层次<br/>
<br/>
**CNullItem:**<br/>
`void Print(CHAR_VEC& container, int depth = 0)`<br/>
以字符形式打印CNullItem，将结果放入container中，其中CHAR_VEC表示vector<char>容器。depth表示缩进层次<br/>