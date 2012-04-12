/*
 * TextueelScherm.cpp
 *
 *  Created on: 11 mrt. 2012
 *      Author: Niek Zuure
 */

#include "TextueelScherm.hpp"

TextueelScherm::TextueelScherm( WeerData* weerData )
{
	//ophalen van de schermgrootte
	MAExtent screenSize = maGetScrSize();

	//bepaal grootte van het scherm
	screenWidth = EXTENT_X( screenSize );
	screenHeight = EXTENT_Y( screenSize );

	//sla de weerdata op in het attribuut
	this->weerData = weerData;

	//ken font en skin toe
	this->font = new Font(RES_FONT);
	this->skin = new WidgetSkin( RES_SELECTED, RES_UNSELECTED, 16, 32, 16, 32, false, false );

	//maak een achtergrond label om alle andere widgets in op te slaan, en te tonen
	Label* achtergrond = new Label(0, 0, 50, 50, NULL);

	//maak een listbox waar update en visueelknop aan toegevoegd worden
	this->listBox = new ListBox(0, 0, screenWidth, 30, achtergrond, ListBox::LBO_HORIZONTAL, ListBox::LBA_LINEAR, true);
	int listHeight = listBox->getHeight();
	int listWidth = listBox->getWidth();

	//knop om data te updaten
	this->updateKnop = new Label( 0, 0, listWidth/2, listHeight, NULL," Updaten ", 0, font);
	this->updateKnop->setSkin( this->skin );
	listBox->add(updateKnop);

	//knop om naar visueel scherm te schakelen
	this->visueelKnop = new Label( 0, 0, listWidth/2, listHeight, NULL," Visueel ", 0, font);
	this->visueelKnop->setSkin( this->skin );
	listBox->add(visueelKniop);

	//label veld voor weer data, beslaat de rest van het scherm (zie onder)
	this->weerDataLabel = new Label(0, listHeight, screenWidth, screenHeight-listHeight, achtergrond, "", 0, font);
	weerDataLabel->setSkin( this->skin );


	//info label
	this->weerInfo = new Label(0,0,weerDataLabel->getWidth(),30,weerDataLabel,"Data: ../../..", 0, font);

	//zonneschijn label
	this->weerInfoZon = new Label(0,40,weerDataLabel->getWidth(),30,weerDataLabel,"Zonneschijn: ../../..", 0, font);

	//neerslag label
	this->weerInfoNeerslag = new Label(0,80,weerDataLabel->getWidth(),30,weerDataLabel,"Neerslag: ../../..", 0, font);

	//minimum temperatuur label
	this->weerInfoMintemp = new Label(0,120,weerDataLabel->getWidth(),30,weerDataLabel,"Min. temperatuur: ../../..", 0, font);

	//stel achtergrond label in als main widget, en maakt alles zichtbaar
	this->setMain(achtergrond);
}

void TextueelScherm::toonWeerData()
{
	//tijdelijke data buffer voor sprintf operaties
	char data[500];

	//stel tekst in voor info label
	sprintf( data, "Data: Nu / Morgen / Overmorgen" );
	this->weerInfo->setCaption( data );

	//stel tekst in voor zonneschijn label
	sprintf( data, "Zonneschijn: %i%%	/ %i%% / %i%%", weerData->zonneschijn[0], weerData->zonneschijn[1], weerData->zonneschijn[2] );
	this->weerInfoZon->setCaption( data );

	//stel tekst in voor neerslag label
	sprintf( data, "Neerslag: %i%%   / %i%% / %i%%", weerData->neerslag[0], weerData->neerslag[1], weerData->neerslag[2] );
	this->weerInfoNeerslag->setCaption(data);

	//stel tekst in voor minimum temperatuur label
	sprintf( data, "Neerslag: %i%%   / %i%% / %i%%", weerData->minimumtemperatuur[0], weerData->minimumtemperatuur[1], weerData->minimumtemperatuur[2] );
	this->weerInfoNeerslag->setCaption(data);
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
		this->updateKnop->setSelected( true );
	else
		this->updateKnop->setSelected( false );


	//visueel knop is ingedrukt
	if( this->visueelKnop->contains( point ) )
	{
		this->visueelKnop->setSelected( true );
		this->hide();
		this->toggleScherm->show();
	}
	else
		this->visueelKnop->setSelected( false );

}

TextueelScherm::~TextueelScherm() {}


