#include "audiosource.h"



void string_tchar(std::string& src, TCHAR* buf)
{
#ifdef UNICODE  
    _stprintf_s(buf, MAX_PATH, _T("%S"), src.c_str());//%S���ַ�  
#else  
    _stprintf_s(buf, MAX_PATH, _T("%s"), src.c_str());//%s���ַ�
#endif
}
