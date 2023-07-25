#include "Audioplayer.h"
Audioplayer::Audioplayer() {
}
void string2tchar(std::string& src, TCHAR* buf)/*将string转为宽字符*/
{
#ifdef UNICODE  
    _stprintf_s(buf, MAX_PATH, _T("%S"), src.c_str());//%S宽字符  
#else  
    _stprintf_s(buf, MAX_PATH, _T("%s"), src.c_str());//%s单字符
#endif
}
void Audioplayer::AddAudioclip(string path, string name) {/*加载游戏音效*/
  
    path = "open " + path + " alias " + name;
    TCHAR* p = new TCHAR[999];
    string2tchar(path,p);
	mciSendString(p, NULL, 0, NULL);
}
void Audioplayer::Playaudiocliponce(string name)/*播放一次游戏音效,发现播放了一次后无法再次播放，然后发现只要把它跳回开始位置就能解决*/
{
    string cmd = "seek "+name+" to start";
    TCHAR* p = new TCHAR[999];
    string2tchar(cmd, p);
    mciSendString(p, NULL, 0, NULL);
    name = "play " + name;
    string2tchar(name, p);
    mciSendString(p, NULL, 0, NULL);
}
void Audioplayer::Playaudiocliploop(string name)/*循环播放游戏音效*/
{
    name = "play " + name + " repeat";
    TCHAR* p = new TCHAR[999];
    string2tchar(name, p);
    mciSendString(p, NULL, 0, NULL);
}