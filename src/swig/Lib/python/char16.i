// Original Code
// https://code.google.com/p/jirrlicht/source/browse/trunk/jni/originalSwigProject/wchar_t.i

%{

int char16_len(const char16_t* s)
{
	int cnt = 0;
	while(*s++) cnt++;
	return cnt*2;
}
%}


%typemap(out) char16_t* { if($1) $result = PyUnicode_DecodeUTF16((const char *) $1, char16_len($1), "strict",0); }
