#include<iostream>
#include<string>
#include<map>
#include<iomanip>
using namespace std;
#define max 50
map<string, int> codelist;//���ű�
string wordlist[max] = { "void","main","return","if","else","do","while","for","int","char","float",
						 "double","bool","=","+","-","*","/", "(" ,")","[",
						 "]", "{" , "}" , "," , ":", ";" , ">" ,"<" ,">=" ,"<=" ,"<<",">>"
						 "==" , "!=", "INT","STRING","ID","++","--","+=","-=","&&","||","#"};
int wordid = 1;//���ܵ����ֱ���
string temp="";//��ʱ�ַ���������ʶ����
int i = 0;//��λ
int shuang = 0;//��־�Ƿ��ҵ�˫���ţ��ַ���
//��������
void printlist(map<string, int> codelist)//��ӡ���ű�
{
	cout << "<<==========���ű�==========>>" << endl;
	cout << "   ����" << right << setw(8) << "|" << right << setw(8) << "�ֱ���" << endl;
	for (auto i= codelist.begin() ; i != codelist.end(); i++)
	{
		cout << "<" << left << setw(8) <<i->first << right << setw(8) << "|\t\t" << i->second << ">" << endl;
	}
	cout << "<<==========================>>" << endl;
}
void set_codelist(string *wordlist)//���÷��ű�
{
	for (int i = 0; i < max ; i++)
	{
		codelist.insert(pair<string, int>(wordlist[i], i));
	}
}

//�жϺ���
bool IsLetter(char ch)//�ж��Ƿ�Ϊ��ĸ
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return true;
	else
		return false;
}
bool IsDigit(char ch)//�ж��Ƿ�Ϊ����
{
	if (ch >= '0' && ch <= '9')
		return true;
	else
		return false;
}
bool IsKey(string str)//�ж��Ƿ�Ϊ�ؼ���
{
	if (str == "void" || str == "main" || str == "return" || str == "if" || str == "else" 
		|| str == "while" || str == "do" || str == "for"
		|| str == "int" || str == "char" || str == "double" || str == "float" || str == "bool")
	{
		return true;
	}
	return false;
}

//���ĺ���
void deal(string line)//����
{
	int shuang = 0;//��־�Ƿ��ҵ�˫���ţ��ַ���
	if (line[i] == ' ')//���ʶ�𵽿ո�
	{
		wordid = -1;
		i++;//������
	}
	else//���ǿո�
	{
		temp = "";//���
		if (IsDigit(line[i]))//������ڵ��ַ�������
		{
			temp = "";//���
			int sum = 0;
			while (IsDigit(line[i]))
			{
				sum = sum * 10 + (line[i] - '0');
				i++;
			}
			wordid = codelist.find("INT")->second;//��INT����Ӧ���ֱ���
			temp += to_string(sum);//���ֱ�Ϊ�ַ���������Ƚ�
		}
		else if (IsLetter(line[i]))//������ڵ��ַ�����ĸ
		{
			temp = "";//���
			while (IsDigit(line[i]) || IsLetter(line[i])) {//��ȡ��ǰ�������ʣ�һ��������ĸ��ͷ
				temp+= line[i];   //����temp�ַ���
				i++;
			}
			if (IsKey(temp))//����ַ����ǹؼ���
			{
				wordid = codelist.find(temp)->second;//��temp����Ӧ���ֱ���
			}
			else//����ַ������ǹؼ��֣����Լ������ı���֮���
			{
				wordid = codelist.find("ID")->second;//��ID����Ӧ���ֱ���
			}
		}
		else if (line[i] == '#')//����
		{
			cout << "������" << endl;
			exit(0);
		}
		else //������ڵ��ַ�����������
		{
			temp = "";//���
			temp += line[i];//�ӽ�temp�ַ���
			if (codelist.count(temp))//�����ǰ�ַ������ҵ�
			{
				temp += line[i+1];
				if (codelist.count(temp))//��������ҵ���ǰ�ַ�����һ���ַ���ϵ��������=+��
				{
					wordid = codelist.find(temp)->second;//��temp����Ӧ���ֱ���
					i += 2;
				}
				else
				{
					temp = "";//���
					temp += line[i];
					wordid = codelist.find(temp)->second;//��temp����Ӧ���ֱ���
					i++;
				}
			}
			else if (line[i]=='"' && shuang==0)//�����ǰ����˫����
			{
				shuang = 1;//�ҵ�һ����˫����
				i++;
				while (line[i]!='#')//���ַ������Ҳ��ǽ�����
				{
					temp += line[i];//�ӽ�temp�ַ���
					i++;
					if (line[i] == '"' && shuang != 0)//�����ǰ����˫����
					{
						temp += line[i];//�ӽ�temp�ַ���
						shuang = 0;//����
						wordid = codelist.find("STRING")->second;//��STRING����Ӧ���ֱ���
						i++;
						break;
					}
				}
			}
			else//��ǰ�ַ��Ҳ����Ҳ���˫����
			{
				wordid = -2;
				cout << "����" << endl;
				exit(0);
			}
		}
	}
}

void main()
{
	//ǰ��׼��
	set_codelist(wordlist);
	printlist(codelist);
	string line = "";//Ҫ������ַ���

	//��ʼ
	cout << "��������ӣ���#������" << endl;
	getline(cin, line);//����
	//��ʼ���
	cout << "   ����" << right << setw(8) << "|" << right << setw(8) << "�ֱ���" << endl;
	do
	{
		deal(line);
		if (wordid != -1)//���ǿո�Ļ�
		{
			cout << "<" << left << setw(8) << temp << right << setw(8) << "|\t\t" << wordid << ">" << endl;
		}
	} while (wordid != -2);//��ǰ�ַ��Ҳ���
	cout << "������" << endl;
}