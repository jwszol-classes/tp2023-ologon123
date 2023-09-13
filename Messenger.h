#pragma once
#include <string>
#include <memory>
#include <windows.h>
#include <gdiplus.h>
#include "Crane.h"
class Messenger
{
public:
	Messenger(std::shared_ptr<Crane> crane, std::shared_ptr<std::vector<std::string>> errorsMessages);
	void drawMessages(HDC& context);
private:
	void drawErrorsMessages();
	void drawWeightMessage();
	void drawTypesMessage();

	std::shared_ptr<Gdiplus::SolidBrush> textBrush;
	std::shared_ptr<Gdiplus::SolidBrush> errorsBrush;
	std::shared_ptr<Gdiplus::FontFamily> fontFamily;
	std::shared_ptr<Gdiplus::Font> font;
	std::shared_ptr<Gdiplus::Graphics> gfx;
	std::shared_ptr<Crane> crane;
	std::shared_ptr<std::vector<std::string>> errorsMessages;

	const int errorX = 25;
	const int errorY = 700;
	const int errorHeight = 30;

	const int restrictX = 25;
	const int restrictY = 450;
	const int restrictWidth = 100;
	const int restrictHeight = 25;

	const int weightX = 25;
	const int weightY = 25;
	const int weightWidth = 100;
	const int weightHeight = 25;
};

