#pragma once
#include "basesetting.h"
class backStage : public ZemaxProject
{
public:
	ZemaxProject Projectback;

	void backgroundProcessing(int argc, char* argv[]);
	void pathConvert_Single2Double(string& s);


private:



};