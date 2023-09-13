#include "Messenger.h"

using namespace std;
using namespace Gdiplus;

Messenger::Messenger(shared_ptr<Crane> crane, shared_ptr<vector<string>> errorsMessages)
{
	textBrush = shared_ptr<SolidBrush>(new SolidBrush(Color(255, 0, 0, 0)));
	errorsBrush = shared_ptr<SolidBrush>(new SolidBrush(Color(255, 255, 0, 0)));
	fontFamily = shared_ptr<FontFamily>(new FontFamily(L"Times New Roman"));
	font = shared_ptr<Font>(new Font(fontFamily.get(), 18, FontStyleRegular, UnitPixel));
	this->crane = crane;
	this->errorsMessages = errorsMessages;
}

void Messenger::drawMessages(HDC& context)
{
	gfx = shared_ptr<Graphics>(new Graphics(context));
	drawWeightMessage();
	drawErrorsMessages();
	drawTypesMessage();
}

void Messenger::drawErrorsMessages()
{
	double messageY = errorY;
	for (auto errorMessage : *errorsMessages)
	{
		wstring message(errorMessage.begin(), errorMessage.end());
		PointF pointF(errorX, messageY);
		gfx->DrawString(message.c_str(), -1, font.get(), pointF, errorsBrush.get());
		messageY += errorHeight;
	}
	errorsMessages->clear();
}

void Messenger::drawWeightMessage()
{
	string weightMessageC = crane->getMessageAboutWeight();
	wstring weightMessage(weightMessageC.begin(), weightMessageC.end());
	PointF pointF(weightX + weightWidth, weightY);
	gfx->DrawString(weightMessage.c_str(), -1, font.get(), pointF, textBrush.get());
}

void Messenger::drawTypesMessage()
{
	string typeMessageC = crane->getMessageAboutAllowedTypes();
	wstring typeMessage(typeMessageC.begin(), typeMessageC.end());
	PointF pointF(restrictX, restrictY + 3 * restrictHeight);
	gfx->DrawString(typeMessage.c_str(), -1, font.get(), pointF, textBrush.get());
}
