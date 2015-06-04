#####MyCjson����C++���ԣ�ʹ��C++11�����ԣ��Լ�STL��ȶ�CJson�����������д��ʹ����д������������OOP���ԣ�����Ҳ������ʹ�ú���չ��<br/>MyCjson����google test��Ԫ���Կ�ܽ����˲��ԡ�

###���ʹ�ã�
**CObjectItem:**<br/>
`const char* Parse(const char *value):`<br/>
����const char *�ַ������������ΪObject���ͣ����ؽ�����ʣ�µ��ַ���,�������ʧ�ܣ�����nullptr��<br/>
<br/>
`void Print(CHAR_VEC &container, int depth = 0):`<br/>
���ַ���ʽ��ӡObject�����ݣ����������container�У�����CHAR_VEC��ʾvector<char>������depth��ʾ�������<br/>
<br/>
`void AddItem(const char* name, CBaseItem *item);`<br/>
��������ӵ�Object�У�name��ʾ�����key��item��ʾ�����value<br/>
<br/>
`CBaseItem *GetItem(const char *str);`<br/>
����key(���������ַ�����ʽ�洢),��ȡ�����value<br/>
<br/>
`CBaseItem* DetachItem(const char *str);`<br/>
����key������󣬲����ض����ֵ<br/>
<br/>
`void DeleteItem(const char *str);`<br/>
����keyɾ������<br/>
<br/>
`void ReplaceItem(const char *str, CBaseItem *item);`<br/>
�滻����<br/>
<br/>
`static CHAR_VEC StrToVec(const char* str);`<br/>
���ַ���ת��ΪCHAR_VEC���ͣ��ྲ̬������<br/>

**CArrayItem:**<br/>
`const char *Parse(const char *value);`<br/>
����const char *�ַ������������ΪArray���ͣ����ؽ�����ʣ�µ��ַ������������ʧ�ܣ��򷵻�nullptr<br/>
<br/>
`void Print(CHAR_VEC &container, int depth = 0);`<br/>
���ַ���ʽ��ӡArray�����������container�У�����CHAR_VEC��ʾvector<char>������depth��ʾ�������<br/>
<br/>
`int GetSize();`<br/>
��ȡ����Ĵ�С<br/>
<br/>
`void AddItem(CBaseItem *item);`<br/>
�������Ԫ�� <br/>
<br/>
`CBaseItem* DetachItem(int idx);`<br/>
��������������󣬷��ض����ֵ<br/>
<br/>
`CBaseItem* GetItem(int idx);`<br/>
����������ȡ�����ֵ<br/>
<br/>
`void DeleteItem(int idx);`<br/>
��������ɾ������<br/>
<br/>
`void ReplaceItem(int idx, CBaseItem *item);`<br/>
���������滻����<br/>

**CStringItem:**<br/>
`CHAR_VEC* GetData();`<br/>
��ȡCStringItem���ַ�������,��CHAR_VEC��ʽ����<br/>
<br/>
`const char* Parse(const char *str);`<br/>
��const char* �����ַ�������ΪCStringItem���ͣ����ؽ�����ʣ�µ��ַ������������ʧ�ܣ��򷵻�nullptr��<br/>
<br/>
`void Print(CHAR_VEC& container, int depth = 0);`<br/>
���ַ���ʽ��ӡCStringItem�����������container�У�����CHAR_VEC��ʾvector<char>������depth��ʾ�������<br/>
<br/>
**CNumberItem:**<br/>
`const char* Parse(const char *num);`<br/>
��const char*�����ַ���תΪCNumberItem����,���ؽ�����ʣ�µ��ַ������������ʧ�ܣ��򷵻�nullptr<br/>
<br/>
`void Print(CHAR_VEC &container, int depth = 0);`<br/>
���ַ���ʽ��ӡCNumberItem�����������container�У�����CHAR_VEC��ʾvector<char>������depth��ʾ�������<br/>

`int GetInt();`<br/>
��int����ʽ��ȡCNumberItem���͵�ֵ��<br/>
<br/>
`double GetDouble();`<br/>
��double����ʽ��ȡCNumberItem���͵�ֵ<br/>
<br/>
**CBoolItem:**<br/>
`CBoolItem(bool val);`<br/>
����CBoolItem���ͣ�����boolֵ<br/>
<br/>
`bool GetBool()`<br/>
��ȡCBoolItem��ֵ	<br/>
<br/>
`void Print(CHAR_VEC& container, int depth = 0);`<br/>
���ַ���ʽ��ӡCBoolItem�����������container�У�����CHAR_VEC��ʾvector<char>������depth��ʾ�������<br/>
<br/>
**CNullItem:**<br/>
`void Print(CHAR_VEC& container, int depth = 0)`<br/>
���ַ���ʽ��ӡCNullItem�����������container�У�����CHAR_VEC��ʾvector<char>������depth��ʾ�������<br/>