#include<iostream>
#include<string>
#include<map>
#include<iomanip>
using namespace std;
#define max 50
map<string, int> codelist;//符号表
string wordlist[max] = { "void","main","return","if","else","do","while","for","int","char","float",
						 "double","bool","=","+","-","*","/", "(" ,")","[",
						 "]", "{" , "}" , "," , ":", ";" , ">" ,"<" ,">=" ,"<=" ,"<<",">>"
						 "==" , "!=", "INT","STRING","ID","++","--","+=","-=","&&","||","#"};
int wordid = 1;//接受单词种别码
string temp="";//临时字符串，接受识别结果
int i = 0;//定位
int shuang = 0;//标志是否找到双引号，字符串
//其他函数
void printlist(map<string, int> codelist)//打印符号表
{
	cout << "<<==========符号表==========>>" << endl;
	cout << "   符号" << right << setw(8) << "|" << right << setw(8) << "种别码" << endl;
	for (auto i= codelist.begin() ; i != codelist.end(); i++)
	{
		cout << "<" << left << setw(8) <<i->first << right << setw(8) << "|\t\t" << i->second << ">" << endl;
	}
	cout << "<<==========================>>" << endl;
}
void set_codelist(string *wordlist)//设置符号表
{
	for (int i = 0; i < max ; i++)
	{
		codelist.insert(pair<string, int>(wordlist[i], i));
	}
}

//判断函数
bool IsLetter(char ch)//判断是否为字母
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return true;
	else
		return false;
}
bool IsDigit(char ch)//判断是否为数字
{
	if (ch >= '0' && ch <= '9')
		return true;
	else
		return false;
}
bool IsKey(string str)//判断是否为关键字
{
	if (str == "void" || str == "main" || str == "return" || str == "if" || str == "else" 
		|| str == "while" || str == "do" || str == "for"
		|| str == "int" || str == "char" || str == "double" || str == "float" || str == "bool")
	{
		return true;
	}
	return false;
}

//核心函数
void deal(string line)//处理
{
	int shuang = 0;//标志是否找到双引号，字符串
	if (line[i] == ' ')//如果识别到空格
	{
		wordid = -1;
		i++;//继续走
	}
	else//不是空格
	{
		temp = "";//清空
		if (IsDigit(line[i]))//如果现在的字符是数字
		{
			temp = "";//清空
			int sum = 0;
			while (IsDigit(line[i]))
			{
				sum = sum * 10 + (line[i] - '0');
				i++;
			}
			wordid = codelist.find("INT")->second;//找INT所对应的种别码
			temp += to_string(sum);//数字变为字符串，方便比较
		}
		else if (IsLetter(line[i]))//如果现在的字符是字母
		{
			temp = "";//清空
			while (IsDigit(line[i]) || IsLetter(line[i])) {//获取当前整个单词，一定是以字母开头
				temp+= line[i];   //加入temp字符串
				i++;
			}
			if (IsKey(temp))//如果字符串是关键字
			{
				wordid = codelist.find(temp)->second;//找temp所对应的种别码
			}
			else//如果字符串不是关键字，是自己命名的变量之类的
			{
				wordid = codelist.find("ID")->second;//找ID所对应的种别码
			}
		}
		else if (line[i] == '#')//结束
		{
			cout << "结束！" << endl;
			exit(0);
		}
		else //如果现在的字符是其他符号
		{
			temp = "";//清空
			temp += line[i];//加进temp字符串
			if (codelist.count(temp))//如果当前字符可以找到
			{
				temp += line[i+1];
				if (codelist.count(temp))//如果可以找到当前字符和下一个字符组合的情况例如=+等
				{
					wordid = codelist.find(temp)->second;//找temp所对应的种别码
					i += 2;
				}
				else
				{
					temp = "";//清空
					temp += line[i];
					wordid = codelist.find(temp)->second;//找temp所对应的种别码
					i++;
				}
			}
			else if (line[i]=='"' && shuang==0)//如果当前是左双引号
			{
				shuang = 1;//找到一个左双引号
				i++;
				while (line[i]!='#')//若字符存在且不是结束符
				{
					temp += line[i];//加进temp字符串
					i++;
					if (line[i] == '"' && shuang != 0)//如果当前是右双引号
					{
						temp += line[i];//加进temp字符串
						shuang = 0;//清零
						wordid = codelist.find("STRING")->second;//找STRING所对应的种别码
						i++;
						break;
					}
				}
			}
			else//当前字符找不到且不是双引号
			{
				wordid = -2;
				cout << "出错！" << endl;
				exit(0);
			}
		}
	}
}

void main()
{
	//前期准备
	set_codelist(wordlist);
	printlist(codelist);
	string line = "";//要输入的字符串

	//开始
	cout << "请输入句子，以#结束：" << endl;
	getline(cin, line);//输入
	//开始输出
	cout << "   符号" << right << setw(8) << "|" << right << setw(8) << "种别码" << endl;
	do
	{
		deal(line);
		if (wordid != -1)//不是空格的话
		{
			cout << "<" << left << setw(8) << temp << right << setw(8) << "|\t\t" << wordid << ">" << endl;
		}
	} while (wordid != -2);//当前字符找不到
	cout << "结束！" << endl;
}