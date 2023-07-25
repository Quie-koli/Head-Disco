#pragma once
class Gameobject
{
public:

	virtual int update() = 0;//将update设计为纯虚函数
	int px, py;
};

