#include <iostream>
#include <string>
#include <vector>
#include <regex>
using namespace std;

int main()
{

	R"(The String Data \ Stuff " )";

	const char *reg_esp = "[ ,.\\t\\n;:]";  // �ָ���Ԫ�б�

	std::regex rgx(reg_esp);  // regex����ģ����basic_regex���ͱ����Ϊchar�ľ��ֻ�
	std::cmatch match;        // cmatch��ģ����match_results���ͱ����Ϊconst char *�ľ��ֻ�
	const char *target = "Polytechnic University of Turin ";

	// ��e���б��ָ���Ԫ���ָ�����
	if (regex_search(target, match, rgx))
	{
		// ������
		const size_t n = match.size();
		for (size_t a = 0; a < n; a++)
		{
			string str(match[a].first, match[a].second);
			cout << str << "\n";
		}
	}

	getchar();
	return 0;
}