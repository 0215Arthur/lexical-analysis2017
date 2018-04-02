#include <iostream>
#include <string>

#include <fstream>



#pragma warning(disable:4996)

using namespace std;

char str[255];//�ַ�������
string keyword[26] = {
	"main","if","then","while","do","static",
	"defualt","do","int","double","struct","break","else",
	"long","swtich","case","typedf","char","return","const","float",
	"short","continue","for","void","sizeof" };

int keyword_num[26] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26 };

char separator[15] = { '{','}','[',']','(',')','~',',',';','.','#','?',':','"' };

int sep_num[15] = {28,29,30,31,32,33,34,35,36,37,38,39,40,41};

char Opeator_s[13] = { '+','-','=','/','*','%','<','>','!','^','&','|' };

int Ope_num_s[13] = { 42,43,44,45,46,47,48,49,50,51,52,53 };

char Operator[19][3] = {"++","--","+=","-=","*=","/=","%=",">=","<=","==","!=","|=","||","&&","&=","^=","->",">>","<<"};

int Ope_num[19] = {54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72};

void scanner(char * infile);
int  prePro(char * buffer);

int main()
{

	char  infile[30];
	cout << "�����ļ���Ϊ" << endl;
	cin >> infile;
	
	scanner(infile);
	cout << "�ʷ�������־�Ѿ�����... �뵽cpp�ļ���ǰĿ¼�鿴" << endl;
	cout << "�������������Ѿ�����... �뵽cpp�ļ���ǰĿ¼�鿴" << endl;
	return 0;


}
//�б��Ƿ�Ϊ��ĸ
bool isAlpha(char *a)
{
	if ((*a) >= 'a' && (*a) <= 'z' || (*a) >= 'A' && (*a) <= 'Z')
		return true;
	return false;
}
//�б��Ƿ�Ϊ����
bool isDigit(char *a)
{
	if ((*a) >= '0' && (*a) <= '9')
		return true;
	return false;
}

//�б���
int isSymbol(char *a)
{
	for (int i = 0; i < 15; i++)
	{

		if (*a == separator[i])
			return sep_num[i];
	}
	return 0;
}
//�б𵥷��������
int isOper(char *a)
{
	for (int i = 0; i < 12; i++)
	{
		if (*a == Opeator_s[i])
			return Ope_num_s[i];
	}
	return 0;
}

//�б�˫����
int isDOper(char *a)
{
	for (int i = 0; i <= 18; i++)
	{
		if (!strcmp(a, Operator[i]))
			return Ope_num[i];
	}
	return 0;

}

bool isINkey(string s)
{
	const char *show;
	int len = s.length();
	for (int i = 0; i < 25; i++)
	{
		int k = keyword[i].length();
		if (k <len)
		{
			show = strstr(s.c_str(), keyword[i].c_str());
			if (show!=NULL&&keyword[i][0]==s[0])
			    return true;
		}

	}
	return false;
}

//ʶ��ؼ���
int isKeyword(string s)
{
	int ID = 27;
	for (int i = 0; i < 25; i++)
	{
		if (s == keyword[i])
			return keyword_num[i];
	}
	return ID;

}

//ɨ��������
void scanner(char * infile)
{
	char buffer[255];//�ַ�������

	ifstream in;
	ofstream out,var,con;
	in.open(infile, ios::in);
	out.open("outfile.log", ios::out);
	var.open("������.txt", ios::out);
	con.open("������.txt",ios::out);
	
	if (!in.is_open())
	{
		cout << "can't open the file" << endl;
		in.close();
		exit(-1);

	}
	
	char demin[] = " ";//�ָ��ַ�����
	char *pch;//��ŷָ��ַ���
	bool flag=false;//ע�Ͷα�־
	int state = 0;
	string token="";//��ʱ�ַ���
    //����ɨ�����
	int line = 0;
	while (in.getline(buffer, 200))
	{
		line++;
		int S_flag = prePro(buffer);
		if (S_flag)
		{
			pch = str;
		}
		else
      		pch = strtok(str,demin);//�Կո�ָ��ַ���

		while (pch != NULL)
		{
			//ͷ�ļ� 
			
			
			//ɨ���ַ���
			for (int i = 0; i < strlen(pch); i++)
			{
				state = 0;
				//�������ע������
				if (*(pch + i) == '/')
				{
					if (*(pch + i + 1) == '*'&&((i+1)<strlen(pch)))
					{
						flag = true;
						break;
					}
				}
				//ע���������
				if (*(pch + i) == '*'&&flag)
				{

					if (*(pch + i + 1) == '/' && ((i + 1)<strlen(pch)))
					{
						flag = false;
						i++;
						continue;
					}
				}
				
				
			  

				//������ ��ʶ��
				if ((isAlpha(pch + i)|| *(pch + i) == '_') && !flag)
				{
					state = 1;
					while (isAlpha(pch + i) || isDigit(pch + i) || *(pch + i) == '_')
					{
						
						token += *(pch + i);
						i++;
					}
					//��ʶ��
					
					if (!isOper(pch + i) && !isSymbol(pch + i)&&*(pch+i)!='\0'&&*(pch + i) != ' ')
					{
						token += *(pch + i);
						cout << "ERROR    "<<"Line  "<<line<<"  "<<token << "------------------>" << "illegal ID" << endl;
						out <<"ERROR     " << "Line  " << line << "  " <<token << "------------------>" << "illegal ID"  << endl;
						token = "";
						break;
					}
					
					if (isKeyword(token) == 27)
					{
					
						
							cout << "Line  " << line << "  " << token  << "------------------>" << "(27," << "-)" << endl;
							out << "Line  " << line << "  " << token  << "------------------>" << "(27," << "-)" << endl;
							var << "Line  " << line << "  " << token << "------------------>" << "(27," << "-)" << endl;
				
					}
					//������
					else
					{
						int t = isKeyword(token);

						cout << "Line  " << line << "  " << token  << "------------------>" <<"("<<t  << ",-)" << endl;
						out << "Line  " << line << "  " << token << "------------------>" << "("<< t << ",-)" << endl;
					}
					token = "";
				}

				
				//����
				if (isDigit(pch + i) && !flag)
				{
					state = 2;
				CASE01:

					int k = strlen(pch);
					while (isDigit(pch + i))
					{
						token += *(pch + i);
						i++;
						if (i >= k)
							break;
						//ʵ������
						if (*(pch + i) == '.')
						{
							token += *(pch + i);
							i++;
							if (i >= k)
								break;
							while (isDigit(pch + i))
							{
								token += *(pch + i);
								i++;
							}
							//x.xxxxxxxxx
							if (i >= k)
								break;
							if (*(pch + i) == 'e' || *(pch + i) == 'E')
							{
								token += *(pch + i);
								i++;
								if (i >= k)
									break;
								//x.exxx
								while (isDigit(pch + i))
								{
									token += *(pch + i);
									i++;
									if (i >= k)
										break;
								}
								if (i + 1 >= k)
									break;
								//x.e+-xxxxxx
								if ((*(pch + i) == '+' || *(pch + i) == '-')&&isDigit(pch+i+1))
								{
									token += *(pch + i);
									i++;
								
									while (isDigit(pch + i))
									{
										token += *(pch + i);
										i++;
										if (i >= k)
											break;
									}
									break;
								}
							}

							break;
						}
						//xe
						if ((*(pch + i) == 'e' || *(pch + i) == 'E'))
						{
							token += *(pch + i);
							i++;
							if (i >= k)
								break;
							//xexxx
							while (isDigit(pch + i))
							{
								token += *(pch + i);
								i++;
								if (i >= k)
									break;
							}
							if (i + 1 >= k)
								break;
							//xe+-xxxxxx
							if ((*(pch + i) == '+' || *(pch + i) == '-') && isDigit(pch + i + 1))
							{
								token += *(pch + i);
								i++;

								while (isDigit(pch + i))
								{
									token += *(pch + i);
									i++;
									if (i >= k)
										break;
								}
								break;
							}


							break;
						}
					}
					cout << "Line  " << line << "  " << token  << "------------------>" << "(74," << "-)" << endl;
					out << "Line  " << line << "  " << token  << "------------------>" << "(74," << "-)" << endl;
					con << "Line  " << line << "  " << token << "------------------>" << "(74," << "-)" << endl;
					token = "";

				}
			
				//�����
				if (isOper(pch + i) && !flag)
				{
					state = 3;
					//�������
					int k = strlen(pch);
					if (i + 1 >= k)
					{
						int k = isOper(pch + i);
						cout << "Line  " << line << "  " << *(pch + i)  << "------------------>" << "(" << k << ",-)" << endl;
						out << "Line  " << line << "  " << *(pch + i)  << "------------------>" << "(" << k << ",-)" << endl;
						break;
					}
						
				     
					else if (!isOper(pch + i + 1))
					{
						//+-x.xxxxxxx     +-.xxxxxxxxxx
						
						if ( (*(pch+i)=='+'||*(pch+i)=='-')&&(isDigit(pch + i + 1) || *(pch+i+1)=='.'))
						{
							int _t_flag = 0;
							if (i != 0)
								if (*(pch + i - 1) == '='|| *(pch + i - 1) == '\10')
									_t_flag = 1;
								else
									_t_flag = 0;
							else
								_t_flag = 1;
							if (_t_flag)
							{
								if (isDigit(pch + i + 1) )
								{
									token += *(pch + i);
									i++;
									goto CASE01;
								}
								else if (*(pch + i + 1) == '.')
								{

									token += *(pch + i);
									i++;
									goto CASE02;
								}
							}
							else
							{
								int k = isOper(pch + i);
								cout << "Line  " << line << "  " << *(pch + i) << "------------------>" << "(" << k << ",-)" << endl;
								out << "Line  " << line << "  " << *(pch + i) << "------------------>" << "(" << k << ",-)" << endl;
							}
							
						}
						//�������
						else
						{
							int k = isOper(pch + i);
							cout << "Line  " << line << "  " << *(pch + i)  << "------------------>" << "(" << k << ",-)" << endl;
							out << "Line  " << line << "  " << *(pch + i) << "------------------>" << "(" << k << ",-)" << endl;

						}
					}
					//˫�����
					else
					{
						char temp[3] = {'\0'};
					    temp[0] = *(pch + i);
						temp[1] = *(pch + i + 1);
						if (isDOper(temp))
						{
							int k = isDOper(temp);
							cout << "Line  " << line << "  " << temp << "------------------>" << "(" << k << ",-)" << endl;
							out << "Line  " << line << "  " << temp  << "------------------>" << "(" << k << ",-)" << endl;
							i++;
						}
						else
						{
							int k = isOper(pch + i);
							cout << "Line  " << line << "  " << *(pch + i)  << "------------------>" << "(" << k << ",-)" << endl;
							out << "Line  " << line << "  " << *(pch + i)  << "------------------>" << "(" << k << ",-)" << endl;
						}

					}
				}
				


				//���
				if (isSymbol(pch + i) && !flag)
				{
					state = 4;
					int _k = isSymbol(pch + i);
					int k = strlen(pch);
					if (*(pch + i) != '.')
					{

						cout << "Line  " << line << "  " << *(pch + i) << "------------------>" << "(" << _k << ",-)" << endl;
						out << "Line  " << line << "  " << *(pch + i) << "------------------>" << "(" << _k << ",-)" << endl;
						int len = strlen(pch);
						string s="";
						bool n_flag = false;
						if (*(pch + i) == '"')
						{
							
							i++;
							while (i < len)
							{
								
								if (*(pch + i) == '"')
								{
									
										if (*(pch + i - 1) == '\\')
											s += *(pch + i);
										else
										{
											n_flag = true;
											break;

										}
													
								}
								else
								{
									s += *(pch + i);
								}
								i++;
							}
							if (!n_flag)
							{
								cout << "Line  " << line << "  "<<s << "------------->" << "ȱ������" << endl;
								out << "Line  " << line << "  "<<s << "------------->" << "ȱ������" << endl;
							}
							else
							{
								cout <<"Line  " << line << "  "<<s << "-------------------->" << "�ַ�������" << endl;
								out <<  "Line  " << line << "  "<<s << "-------------------->" << "�ַ�������" << endl;
								con << "Line  " << line << "  " << s << "-------------------->" << "�ַ�������" << endl;
							}

						}
						else if (*(pch + i) == '\'')
						{
							n_flag = false;
							s = "";
							i++;
							while (i < len)
							{

								if (*(pch + i) == '\'')
								{

									if (*(pch + i - 1) == '\\')
										s += *(pch + i);
									else
									{
										n_flag = true;
										break;

									}

								}
								else
								{
									s += *(pch + i);
								}
								i++;
							}
							if (!n_flag)
							{
								cout << "Line  " << line << "  " << s << "------------->" << "ȱ������" << endl;
								out << "Line  " << line << "  " << s << "------------->" << "ȱ������" << endl;
							}
							else
							{
								cout << "Line  " << line << "  " << s << "-------------------->" << "�ַ�����" << endl;
								out << "Line  " << line << "  " << s << "-------------------->" << "�ַ�����" << endl;
								con << "Line  " << line << "  " << s << "-------------------->" << "�ַ�����" << endl;
							}
						}
					}
					else
					{
					CASE02:

						if (i + 1 >= k)
						{
							cout << "Line  " << line << "  " << *(pch + i) << "------------------>" << "(" << _k << ",-)" << endl;
							out << "Line  " << line << "  " << *(pch + i) << "------------------>" << "(" << _k << ",-)" << endl;
							break;
						}
							
						//.xxxxʵ�����
						if (isDigit(pch + i + 1))
						{
							token += *(pch + i);
							i++;
							if (i >= k)
								break;
							while (isDigit(pch + i))
							{
								token += *(pch + i);
								i++;
							}
							//.xxxxxxxxx
							if (i >= k)
								break;
							if (*(pch + i) == 'e' || *(pch + i) == 'E')
							{
								token += *(pch + i);
								i++;
								if (i >= k)
									break;
								//x.exxx
								while (isDigit(pch + i))
								{
									token += *(pch + i);
									i++;
									if (i >= k)
										break;
								}
								if (i + 1 >= k)
									break;
								//x.e+-xxxxxx
								if ((*(pch + i) == '+' || *(pch + i) == '-') && isDigit(pch + i + 1))
								{
									token += *(pch + i);
									i++;

									while (isDigit(pch + i))
									{
										token += *(pch + i);
										i++;
										if (i >= k)
											break;
									}
									
								}
							}

							cout << "Line  " << line << "  " << token << "------------------>" << "(74," << "-)" << endl;
							out << "Line  " << line << "  " << token << "------------------>" << "(74," << "-)" << endl;
							con << "Line  " << line << "  " << token << "------------------>" << "(74," << "-)" << endl;

							token = "";

						}
						else
						{
							cout << "Line  " << line << "  " << *(pch + i) << "------------------>" << "(" << _k << ",-)" << endl;
							out << "Line  " << line << "  " << *(pch + i) << "------------------>" << "(" << _k << ",-)" << endl;

						}

					}			
				}
			    
				if (state==0&&*(pch+i)!=' ')
				{
					cout <<  "Line  " << line << "  "<< *(pch + i) << "------------->can't identify the word"<<endl;
					break;
				}
				
				
			}
		

//cout << pch << "-------" << strlen(pch) << endl;
			if (!S_flag)
				pch = strtok(NULL, " ");
			else
				break;
		}



	}
	in.close();
	out.close();
	var.close();
	con.close();
}


//Ԥ����
int prePro(char * buffer)
{
	memset(str, 0, 255);
	int j = 0;
	int k = 0;
	for (int i = 0; i < strlen(buffer); i++)
	{
	    //��ȥע����
		if (buffer[i]== '/'&&buffer[i + 1] == '/')
		{
			break;
		}
		else
		{
			//����Ʊ��
			if (buffer[i] == '\t')
				buffer[i] = ' ';
			if (buffer[i] == '"' || buffer[i] == '\'')
				k = 1;
			str[j++] = buffer[i];
		}
	}
	return k;
}