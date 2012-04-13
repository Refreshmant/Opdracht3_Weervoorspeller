/*
 * VisueelScherm.cpp
 *
 *  Created on: 11 mrt. 2012
 *      Author: Niek Zuure
 */

#include "VisueelScherm.hpp"

VisueelScherm::VisueelScherm( WeerData* weerData )
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
	Label* achtergrond = new Label(0, 0, screenWidth, screenHeight, NULL);

	//maak een listbox met update en textueelknop
	this->listBox = new ListBox(0, 0, screenWidth, 30, achtergrond, ListBox::LBO_HORIZONTAL, ListBox::LBA_LINEAR, true);
	int listHeight = listBox->getHeight();
	int listWidth = listBox->getWidth();

	//knop om data te updaten
	this->updateKnop = new Label(0, 0, listWidth/2, listHeight, NULL, " Updaten", 0, font);
	this->updateKnop->setSkin( this->skin );
	listBox->add(updateKnop);

	//knop om naar textueel te schakelen
	this->textueelKnop = new Label(0, 0, listWidth/2, listHeight, NULL, " Textueel", 0, font);
	this->textueelKnop->setSkin( this->skin );
	listBox->add(textueelKnop);

	//staafdiagram

	//maak eerst een placeholder
	this->diagramTekening = maCreatePlaceholder();

	//laat de placeholder tekenbaar zijn
	maCreateDrawableImage( this->diagramTekening, EXTENT_X( maGetScrSize() ), EXTENT_Y( maGetScrSize() ) - 30 );

	//mak een nieuwe image met de placeholder
	this->diagramImage = new Image( 0, 30, EXTENT_X( maGetScrSize() ), EXTENT_Y( maGetScrSize() ) - 30, achtergrond, true, true, this->diagramTekening );

	this->setMain( achtergrond );
}

/**
 * met dan aan iwan, en tevens met zijn toestemming
 */
void VisueelScherm::update()
{
	//Offsets
	int offy = 5;
	int offx = 5;

	//Zet buffer voor tekst
	char data[500];

	//update waarden vam weerdata
	this->weerData->update();

	//stel draw target in op onze tekening
	maSetDrawTarget( this->diagramTekening );

	//Defineer de kleur
	maSetColor(0xffffff);

	/**
	 * zon
	 */
	//Tekent tekst van zonneschijn
	maDrawText(offx, offy, "Zonneschijn (max 100%)");
	offy+=20;

	//Vult extra informatie naast de grafiek
	sprintf( data, "%i%% / %i%% / %i%%", weerData->zonneschijn[0], weerData->zonneschijn[1], weerData->zonneschijn[2]);

	//Tekent extra informatie
	maDrawText(offx+105, offy+5, data);

	//Teken de grafiek
	maLine(offx,offy,offx+100,offy);
	maLine(offx,offy,offx,offy+25);
	offy+=3;

	//Tekenen de balken van de zonnenschijn
	maFillRect(offx, offy, weerData->zonneschijn[0], 5);
	offy+=7;
	maFillRect(offx, offy, weerData->zonneschijn[1], 5);
	offy+=7;
	maFillRect(offx, offy, weerData->zonneschijn[2], 5);
	offy+=20;

	/**
	 * neerslag
	 */
	//Tekent tekst van neerslag
	maDrawText(offx, offy, "Neerslag (max 100%)");
	offy+=20;

	//Vult extra informatie naast de grafiek
	sprintf( data, "%i%% / %i%% / %i%%", weerData->neerslag[0], weerData->neerslag[1], weerData->neerslag[2]);

	//Tekent extra informatie
	maDrawText(offx+105, offy+5, data);

	//Teken de grafiek
	maLine(offx, offy, offx+100, offy);
	maLine(offx, offy, offx, offy+25);
	offy+=3;

	//Tekent de balken
	maFillRect(offx, offy, weerData->neerslag[0], 5);
	offy+=7;

	maFillRect(offx, offy, weerData->neerslag[1], 5);
	offy+=7;

	maFillRect(offx, offy, weerData->neerslag[2], 5);
	offy+=20;

	/**
	 * temperatuur
	 */
	//Tekent tekst van minimale temperatuur
	maDrawText(offx, offy, "Min. temperatuur (min/max 25c)");
	offy+=20;

	//Vult extra informatie naast de grafiek
	sprintf( data, "%i%s/%i%s/%i%s", weerData->minimumtemperatuur[0],"C", weerData->minimumtemperatuur[1],"C", weerData->minimumtemperatuur[2],"C");

	//Tekent extra informatie
	maDrawText(offx+105, offy+5, data);

	//Teken de grafiek
	maLine(offx, offy, offx+100, offy);
	maLine(offx+50, offy, offx+50, offy+25);

	//Tekenen van de de balken van temperatuur
	offy+=3;

	//Als de temperatuur negatief is, balken aan de negatieve zijde tekenen
	if(weerData->minimumtemperatuur[0]>0)
		maFillRect(offx+50, offy, weerData->minimumtemperatuur[0]*2, 5);
	else
		maFillRect(offx+50+weerData->minimumtemperatuur[0]*2, offy, weerData->minimumtemperatuur[0]*2, 5);

	offy+=7;
	//Als de temperatuur negatief is, balken aan de negatieve zijde tekenen
	if(weerData->minimumtemperatuur[1]>0)
		maFillRect(offx+50, offy, weerData->minimumtemperatuur[1]*2, 5);
	else
		maFillRect(offx+50+weerData->minimumtemperatuur[1]*2, offy, weerData->minimumtemperatuur[1]*2, 5);

	offy+=7;
	//Als de temperatuur negatief is, balken aan de negatieve zijde tekenen
	if(weerData->minimumtemperatuur[2]>0)
		maFillRect(offx+50, offy, weerData->minimumtemperatuur[2]*2, 5);
	else
		maFillRect(offx+50+weerData->minimumtemperatuur[2]*2, offy, weerData->minimumtemperatuur[2]*2, 5);

	// Draw target na tekenen teruggeven naar scherm!
	maSetDrawTarget( HANDLE_SCREEN );

	//update de image met de nieuwe tekening
	this->diagramImage->setResource( this->diagramTekening );

}

void VisueelScherm::setToggleScherm( Screen* toggleScherm )
{
	//switch naar andere scherm (textueel scherm)
	this->toggleScherm = toggleScherm;
}

void VisueelScherm::pointerPressEvent( MAPoint2d maPoint )
{
	Point point;
	point.x = maPoint.x;
	point.y = maPoint.y;

	//update knop is ingedrukt
	if( this->updateKnop->contains( point ) )
	{
		this->updateKnop->setSelected( true );
		this->update();
	}
	else
	{
		this->updateKnop->setSelected( false );
	}

	//textueel knop is ingedrukt
	if( this->textueelKnop->contains( point ) )
	{
		this->textueelKnop->setSelected( true );
		this->hide();
		this->toggleScherm->show();
	}
	else
	{
		this->textueelKnop->setSelected( false );
	}
}

VisueelScherm::~VisueelScherm(){}
