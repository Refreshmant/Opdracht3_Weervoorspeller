/*
 * TextueelScherm.h
 *
 *  Created on: 11 mrt. 2012
 *      Author: Niek Zuure
 */

#ifndef TEXTUEELSCHERM_HPP_
#define TEXTUEELSCHERM_HPP_


#include <MAUI/Screen.h>
#include <MAUI/Font.h>
#include <MAUI/WidgetSkin.h>

#include <conprint.h>

#include "WeerData.hpp"


using namespace MAUI;


class TextueelScherm : public Screen
{
private:
//	scherm info
	int screenWidth, screenHeight;

	//skin, font
	WidgetSkin* skin;
	Font* font;

	//scherm waar we naartoe toggelen bij indrukken visueelknop
	Screen* toggleScherm;

	//standaard knoppenset bovenaan
	ListBox* listBox;
	Label* updateKnop, visueelKnop;

	//data van weer
	WeerData* weerData;

	//textuele weergave van weerdata
	Label* weerDataLabel;
	Label* weerInfo;
	Label* weerInfoZon;
	Label* weerInfoNeerslag;
	Label* weerInfoMintemp;

public:
	TextueelScherm( WeerData* weerData );
	virtual ~TextueelScherm();

	void setToggleScherm( Screen* toggleScherm );
	void update();
	void toonWeerData();

	void pointerPressEvent( MAPoint2d point );
};

#endif /* TEXTUEELSCHERM_H_ */
