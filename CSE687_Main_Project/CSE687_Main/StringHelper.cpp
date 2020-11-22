#include "StringHelper.h"

vector<string> utility::StringHelper::split(const string& src, char splitter)
{
	vector<string> accum;
	string temp;
	size_t index = 0;

	do
	{
		while ((src[index] == splitter) && index < src.length())
		{
			++index;
			if (temp.size() > 0)
			{
				accum.push_back(temp);
				temp.clear();
			}
		}
		if (src[index] != '\0') {
			temp += src[index];
		}
	} while (index++ < src.size());

	if (temp.size() > 0) {
		accum.push_back(temp);
	}
	return accum;
}