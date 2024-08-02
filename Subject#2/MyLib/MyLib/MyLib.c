#include "MyLib.h"

DLLEXPORT wchar_t* Trim(wchar_t* str) {
	if (str == NULL)
		return NULL;

	if (str[0] == 0)
		return _wcsdup(L"");

	size_t start = 0;
	size_t end = wcslen(str) - 1;
	while (str[start] && isspace(str[start]))
		start++;
	while (end > start && isspace(str[end]))
		end--;
	return Substr(str, start, end - start + 1);
}

DLLEXPORT wchar_t* _Substr(wchar_t* str, size_t start) {
	if (str == NULL)
		return NULL;

	size_t len = wcslen(str);
	if (len < start)
		return NULL;
	size_t size = len - start;
	wchar_t* ret = (wchar_t*)malloc(sizeof(wchar_t) * (size + 1));
	for (size_t i = start; str[i]; i++)
		ret[i - start] = str[i];
	ret[len] = 0;
	return ret;
}

DLLEXPORT wchar_t* Substr(wchar_t* str, size_t start, size_t count) {
	if (str == NULL)
		return NULL;
	size_t len = wcslen(str);

	if (len < start || len - start < count)
		return NULL;
	wchar_t* ret = (wchar_t*)malloc(sizeof(wchar_t) * (count + 1));
	for (size_t i = 0; i < count; i++) {
		ret[i] = str[i + start];
	}
	ret[count] = 0;
	return ret;
}

DLLEXPORT wchar_t* Getline(FILE* fp) {
	if (fp == NULL)
		return NULL;

	static wchar_t** remainWords = NULL;
	wchar_t buf[BUFFER_SIZE + 1] = { 0 };
	int fd = _fileno(fp);

	if (remainWords == NULL) {
		setlocale(LC_ALL, "");
		int maxFds = _getmaxstdio();
		remainWords = (wchar_t**)calloc(maxFds + 1, sizeof(wchar_t*));
	}

	while (true) {
		if (feof(fp))
			break;

		fgetws(buf, sizeof(buf) / sizeof(wchar_t), fp);
		size_t size = 0;
		size_t n = wcslen(buf);
		
		if (remainWords[fd] == NULL) {
			remainWords[fd] = _wcsdup(buf);
		}
		else {
			size = wcslen(remainWords[fd]);
			remainWords[fd] = (wchar_t*)realloc(remainWords[fd], sizeof(wchar_t) * (size + n));
			ReplaceString(&remainWords[fd], StrJoin(remainWords[fd], buf));
			size--;
		}

		for (size_t i = 0; remainWords[fd][i]; i++) {
			if (remainWords[fd][i] == '\n')
			{
				remainWords[fd][i] = 0;
				wchar_t* ret = _wcsdup(remainWords[fd]);
				ReplaceString(&remainWords[fd], _Substr(remainWords[fd], i + 1));
				return ret;
			}
		}
	}
	if (remainWords[fd] != NULL)
	{
		wchar_t* ret = _wcsdup(remainWords[fd]);
		free(remainWords[fd]);
		remainWords[fd] = NULL;
		return ret;
	}
	return NULL;
}

DLLEXPORT wchar_t* _Getline(int fd) {
	if (fd >= 3)
	{
		FILE* fp = fdopen(fd, "r+, ccs=UTF-8");

		wchar_t* ret = Getline(fp);
		fclose(fp);
		return ret;
	}
	return Getline(stdin);
}

DLLEXPORT wchar_t** Split(wchar_t* str, int delim, bool trim) {
	if (str == NULL || delim == 0)
		return NULL;

	int cnt = 0;
	int i = 0;
	while (str[i]) {
		while (str[i] && str[i] == delim)
			i++;
		if (str[i] && str[i] != delim) {
			cnt++;
			while (str[i] && str[i] != delim)
				i++;
		}
	}

	wchar_t** ret = (wchar_t**)malloc(sizeof(wchar_t*) * (cnt + 1));
	i = 0;
	int j = 0;
	while (str[j]) {
		while (str[j] && str[j] == delim)
			j++;
		int start = j;
		while (str[j] && str[j] != delim)
			j++;
		wchar_t* tmp = Substr(str, start, j - start);
		if (trim) {
			ret[i] = Trim(tmp);
			free(tmp);
		}
		else {
			ret[i] = tmp;
		}
		i++;
	}
	ret[cnt] = NULL;
	return ret;
}

DLLEXPORT wchar_t* StrJoin(wchar_t* s1, wchar_t* s2) {
	if (s1 == NULL || s2 == NULL)
		return NULL;

	size_t len1 = wcslen(s1);
	size_t len2 = wcslen(s2);
	wchar_t* ret = (wchar_t*)malloc(sizeof(wchar_t) * (len1 + len2 + 1));
	for (int i = 0; s1[i]; i++) { ret[i] = s1[i]; }
	for (int i = 0; s2[i]; i++) { ret[i + len1] = s2[i]; }
	ret[len1 + len2] = 0;
	return ret;
}

DLLEXPORT int StrFindByChar(wchar_t* str, wchar_t target, size_t pos) {
	if (str == NULL)
		return -1;
	size_t len = wcslen(str);
	if (pos >= len)
		return -1;

	for (size_t i = pos; str[i]; i++)
	{
		if (str[i] == target)
			return i;
	}
	return -1;
}

DLLEXPORT int StrFindByString(wchar_t* str, wchar_t* target, size_t pos) {
	if (str == NULL)
		return -1;
	size_t len = wcslen(str);
	if (pos >= len)
		return -1;

	for (int i = pos; str[i]; i++)
	{
		for (int j = 0;; j++) {
			if (str[j] == 0 || str[i + j] != target[j])
				break;
			if (target[j] == 0)
				return i;
		}
	}
	return -1;
}

DLLEXPORT int StrRFindByChar(wchar_t* str, wchar_t target, size_t pos) {
	if (str == NULL)
		return -1;
	size_t len = wcslen(str);
	if (pos >= len)
		return -1;

	for (int i = pos; i >= 0; i--)
		if (str[i] == target)
			return i;
	return -1;
}

DLLEXPORT int StrRFindByString(wchar_t* str, wchar_t* target, size_t pos) {
	if (str == NULL)
		return -1;
	size_t len = wcslen(str);
	if (pos >= len)
		return -1;

	for (int i = pos; i >= 0; i--)
	{
		for (int j = i;; j++) {
			if (str[j] == 0 || str[i + j] != target[j])
				break;
			if (target[j] == 0)
				return i;
		}
	}
	return -1;
}

DLLEXPORT void ReplaceString(wchar_t** oldString, wchar_t* newString) {
	if (*oldString == NULL)
		return;
	if (newString == NULL)
	{
		if (_msize(*oldString) > 0)
			free(*oldString);
		*oldString = NULL;
		return;
	}
	wchar_t* tmp = _wcsdup(newString);
	if (_msize(*oldString) > 0)
		free(*oldString);
	if (_msize(newString) > 0)
		free(newString);
	*oldString = tmp;
}

DLLEXPORT wchar_t* IntToAscii(int n) {
	if (n == INT_MIN)
		return _wcsdup(L"-2147483648");

	int len = 1;
	int tmp = n;
	bool negative = (n < 0);
	n = abs(n);

	len += negative;
	while ((tmp /= 10)) len++;
	wchar_t* ret = (wchar_t*)malloc(sizeof(wchar_t) * (len + 1));
	for (int i = len - 1; i >= 0 + negative; i--) {
		ret[i] = n % 10 + '0';
		n /= 10;
	}
	ret[len] = 0;
	if (negative)
		ret[0] = '-';
	return ret;
}

DLLEXPORT wchar_t* CharToString(wchar_t c) {
	wchar_t* ret = (wchar_t*)calloc(2, sizeof(wchar_t));
	ret[0] = c;
	return ret;
}

DLLEXPORT void _InsertString(wchar_t** original, size_t pos, wchar_t c) {
	if (original == NULL || *original == NULL)
		return NULL;
	wchar_t* oldString = *original;
	size_t len = wcslen(oldString);
	if (pos > len)
		return NULL;

	wchar_t* ret = (wchar_t*)calloc(len + 2, sizeof(wchar_t));
	ret = MyStrncpy(ret, oldString, 0, pos);
	ret[pos] = c;
	size_t i = pos + 1;
	for (; oldString[i - 1]; i++)
		ret[i] = oldString[i - 1];
	if (_msize(oldString) > 0)
		free(oldString);
	*original = ret;
}

DLLEXPORT void InsertString(wchar_t** original, size_t pos, wchar_t* str) {
	if (original == NULL || *original == NULL || str == NULL)
		return NULL;
	wchar_t* oldString = *original;
	size_t len1 = wcslen(oldString);
	size_t len2 = wcslen(str);

	wchar_t* ret = (wchar_t*)calloc(len1 + len2 + 1, sizeof(wchar_t));
	ret = MyStrncpy(ret, oldString, 0, pos);
	ret = MyStrcpy(ret, str, pos);
	size_t i = pos + 1;
	for (; oldString[i - 1]; i++)
		ret[i] = oldString[i - 1];
	if (_msize(oldString) > 0)
		free(oldString);
	*original = ret;
}

DLLEXPORT wchar_t* MyStrcpy(wchar_t* dest, wchar_t* src, size_t pos) {
	if (src == NULL)
		return dest;
	return MyStrncpy(dest, src, pos, wcslen(src));
}

DLLEXPORT wchar_t* MyStrncpy(wchar_t* dest, wchar_t* src, size_t pos, size_t n) {
	if (dest == NULL)
		return NULL;
	if (src == NULL || n == 0)
		return dest;
	size_t len = wcslen(dest);
	if (wcslen(src) < n)
		return dest;
	size_t i = 0;
	for (; i < n; i++)
		dest[i + pos] = src[i];
	dest[i + pos] = 0;
	return dest;
}

DLLEXPORT void String_ToUpper(wchar_t* str) {
	if (str == NULL)
		return;
	for (size_t i = 0; str[i]; i++)
		str[i] = toupper(str[i]);
}

DLLEXPORT void String_ToLower(wchar_t* str) {
	if (str == NULL)
		return;
	for (size_t i = 0; str[i]; i++)
		str[i] = tolower(str[i]);
}

DLLEXPORT wchar_t* Readline(wchar_t* msg) {
	setlocale(LC_ALL, "");

	wchar_t* ret = NULL;
	while (true)
	{
		wprintf(L"%ls", msg);
		ret = _Getline(0);
		if (wcslen(ret) != 0)
			break;
		free(ret);
	}
	ReplaceString(&ret, Trim(ret));
	return ret;
}

DLLEXPORT int MyStrcmp(wchar_t* s1, wchar_t* s2) {
	if (s1 == NULL && s2 == NULL)
		return 0;
	else if (s1 == NULL)
		return -1;
	else if (s2 == NULL)
		return 1;


	size_t i = 0;
	for (; s1[i]; i++) {
		if (s2[i] != s1[i])
			break;
	}
	return s1[i] - s2[i];
}

DLLEXPORT int Get2PCharSize(wchar_t** strs) {
	if (strs == NULL)
		return 0;
	size_t i = 0;
	for (; strs[i]; i++);
	return i;
}

DLLEXPORT int StringToInt(wchar_t* str) {
	size_t i = 0;
	int n = 0;
	bool negative = (str[i] == '-');

	if (str[i] == '-' || str[i] == '+')
		i++;
	for (; str[i]; i++) {
		wchar_t c = str[i];
		if (c < '0' || '9' < c)
			break;
		n *= 10;
		n += c - '0';
	}
	if (negative)
		return -n;
	return n;
}

DLLEXPORT void Free2P(void** v, int size) {
	if (v == NULL || size < 0)
		return;
	for (size_t i = 0; i < size; i++)
		free(v[i]);
	free(v);
}