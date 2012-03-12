/*
 * TextueelScherm.cpp
 *
 *  Created on: 11 mrt. 2012
 *      Author: acer
 */

#include "TextueelScherm.hpp"

TextueelScherm::TextueelScherm( WeerData* weerData )
{
	//sla de weerdata op in het attribuut
	this->weerData = weerData;

	//ken font en skin toe
	this->font = ...
	this->skin = ...

	//maak een achtergrond label om alle andere widgets in op te slaan, en te tonen
	Label* achtergrond = ...

	//maak een listbox waar update en visueelknop aan toegevoegd worden
	this->listBox = ...

	//knop om data te updaten
	this->updateKnop = ...
	this->updateKnop->setSkin( this->skin );

	//knop om naar visueel scherm te schakelen
	this->visueelKnop = ...
	this->visueelKnop->setSkin( this->skin );



	//label veld voor weer data, beslaat de rest van het scherm (zie onder)
	this->weerDataLabel = ...
	weerDataLabel->setSkin( this->skin );


	//info label
	this->weerInfo = ...

	//zonneschijn label
	this->weerInfoZon = ...

	//neerslag label
	this->weerInfoNeerslag = ...

	//minimum temperatuur label
	this->weerInfoMintemp = ...

	//update labels met text, etc.

	//stel achtergrond label in als main widget, en maakt alles zichtbaar
}

TextueelScherm::~TextueelScherm()
{
}



void TextueelScherm::toonWeerData()
{
	//tijdelijke data buffer voor sprintf operaties
	char data[500];

	//stel tekst in voor info label
	sprintf( data, "Data: Nu / Morgen / Overmorgen" );
	this->weerInfo->???

	//stel tekst in voor zonneschijn label
	sprintf( data, "Zonneschijn: %i%%	/ %i%% / %i%%", ???, ???, ??? );
	this->weerInfoZon->setCaption( data );

	//stel tekst in voor neerslag label
	sprintf( data, ??? );
	...

	//stel tekst in voor minimum temperatuur label
	sprintf( data, ??? );
	...
}


void TextueelScherm::setToggleScherm( Screen* toggleScherm )
{
	//switch naar andere scherm (visueel scherm)
	this->toggleScherm = toggleScherm;
}



void TextueelScherm::update()
{
	//update weerdata en geef alles weer (update labels met nieuwe data)
	this->weerData->update();
	this->toonWeerData();
}



void TextueelScherm::pointerPressEvent( MAPoint2d maPoint )
{
	Point point;
	point.x = maPoint.x;
	point.y = maPoint.y;

	//update knop is ingedrukt
	if( this->updateKnop->contains( point ) )
	{
		this->updateKnop->setSelected( true );
		...
	}
	else
	{
		this->updateKnop->setSelected( false );
	}


	//visueel knop is ingedrukt
	if( this->visueelKnop->contains( point ) )
	{
		this->visueelKnop->setSelected( true );
		this->hide();
		this->toggleScherm->show();
	}
	else
	{
		this->visueelKnop->setSelected( false );
	}
}


