#pragma once
#include<iostream>
#include<windows.h>
#include <mmsystem.h>
#include<dsound.h>
#include<TCHAR.H>
#pragma comment(lib, "WINMM.LIB")
using namespace std;
class Audioplayer
{
public:
	Audioplayer();
	void AddAudioclip(string path ,string name);
	void Playaudiocliponce(string name);
	void Playaudiocliploop(string name);
};

