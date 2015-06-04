##MyCjson����C++���ԣ�ʹ��C++11�����ԣ��Լ�STL��ȶ�CJson�����������д��ʹ����д������������OOP���ԣ�����Ҳ������ʹ�ú���չ��
##MyCjson����google test��Ԫ���Կ�ܽ����˲��ԡ�

###���ʹ�ã�
CObjectItem:
		`const char* Parse(const char *value):`
		����const char *�ַ������������ΪObject���ͣ����ؽ�����ʣ�µ��ַ���,�������ʧ�ܣ�����nullptr��

		`void Print(CHAR_VEC &container, int depth = 0):`
		���ַ���ʽ��ӡObject�����ݣ����������container�У�����CHAR_VEC��ʾvector<char>������depth��ʾ�������

		`void AddItem(const char* name, CBaseItem *item);`
		��������ӵ�Object�У�name��ʾ�����key��item��ʾ�����value

		`CBaseItem *GetItem(const char *str);`
		����key(���������ַ�����ʽ�洢),��ȡ�����value

		`CBaseItem* DetachItem(const char *str);`
		����key������󣬲����ض����ֵ

		`void DeleteItem(const char *str);`
		����keyɾ������

		`void ReplaceItem(const char *str, CBaseItem *item);`
		�滻����

		static CHAR_VEC StrToVec(const char* str);
		���ַ���ת��ΪCHAR_VEC���ͣ��ྲ̬������

CArrayItem��
		const char *Parse(const char *value);
		����const char *�ַ������������ΪArray���ͣ����ؽ�����ʣ�µ��ַ������������ʧ�ܣ��򷵻�nullptr

		void Print(CHAR_VEC &container, int depth = 0);
		���ַ���ʽ��ӡArray�����������container�У�����CHAR_VEC��ʾvector<char>������depth��ʾ�������

		int GetSize();
		��ȡ����Ĵ�С

		void AddItem(CBaseItem *item);
		�������Ԫ�� 
		
		CBaseItem* DetachItem(int idx);
		��������������󣬷��ض����ֵ

		CBaseItem* GetItem(int idx);
		����������ȡ�����ֵ

		void DeleteItem(int idx);
		��������ɾ������

		void ReplaceItem(int idx, CBaseItem *item);
		���������滻����

CStringItem:
		CHAR_VEC* GetData();
		��ȡCStringItem���ַ�������,��CHAR_VEC��ʽ����

		const char* Parse(const char *str);
		��const char* �����ַ�������ΪCStringItem���ͣ����ؽ�����ʣ�µ��ַ������������ʧ�ܣ��򷵻�nullptr��

		void Print(CHAR_VEC& container, int depth = 0);
		���ַ���ʽ��ӡCStringItem�����������container�У�����CHAR_VEC��ʾvector<char>������depth��ʾ�������

CNumberItem:
		const char* Parse(const char *num);
		��const char*�����ַ���תΪCNumberItem����,���ؽ�����ʣ�µ��ַ������������ʧ�ܣ��򷵻�nullptr

		void Print(CHAR_VEC &container, int depth = 0);
		���ַ���ʽ��ӡCNumberItem�����������container�У�����CHAR_VEC��ʾvector<char>������depth��ʾ�������	

		int GetInt();
		��int����ʽ��ȡCNumberItem���͵�ֵ��

		double GetDouble();
		��double����ʽ��ȡCNumberItem���͵�ֵ

CBoolItem:
		CBoolItem(bool val);
		����CBoolItem���ͣ�����boolֵ

		bool GetBool()
		��ȡCBoolItem��ֵ

		void Print(CHAR_VEC& container, int depth = 0);
		���ַ���ʽ��ӡCBoolItem�����������container�У�����CHAR_VEC��ʾvector<char>������depth��ʾ�������	

CNullItem:
		void Print(CHAR_VEC& container, int depth = 0)
		���ַ���ʽ��ӡCNullItem�����������container�У�����CHAR_VEC��ʾvector<char>������depth��ʾ�������	
