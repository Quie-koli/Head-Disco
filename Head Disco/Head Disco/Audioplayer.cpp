#include "Audioplayer.h"
Audioplayer::Audioplayer() {
}
void string2tchar(std::string& src, TCHAR* buf)/*��stringתΪ���ַ�*/
{
#ifdef UNICODE  
    _stprintf_s(buf, MAX_PATH, _T("%S"), src.c_str());//%S���ַ�  
#else  
    _stprintf_s(buf, MAX_PATH, _T("%s"), src.c_str());//%s���ַ�
#endif
}
void Audioplayer::AddAudioclip(string path, string name) {/*������Ϸ��Ч*/
  
    path = "open " + path + " alias " + name;
    TCHAR* p = new TCHAR[999];
    string2tchar(path,p);
	mciSendString(p, NULL, 0, NULL);
}
void Audioplayer::Playaudiocliponce(string name)/*����һ����Ϸ��Ч,���ֲ�����һ�κ��޷��ٴβ��ţ�Ȼ����ֻҪ�������ؿ�ʼλ�þ��ܽ��*/
{
    string cmd = "seek "+name+" to start";
    TCHAR* p = new TCHAR[999];
    string2tchar(cmd, p);
    mciSendString(p, NULL, 0, NULL);
    name = "play " + name;
    string2tchar(name, p);
    mciSendString(p, NULL, 0, NULL);
}
void Audioplayer::Playaudiocliploop(string name)/*ѭ��������Ϸ��Ч*/
{
    name = "play " + name + " repeat";
    TCHAR* p = new TCHAR[999];
    string2tchar(name, p);
    mciSendString(p, NULL, 0, NULL);
}