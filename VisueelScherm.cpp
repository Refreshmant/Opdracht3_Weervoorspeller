/*
 * VisueelScherm.cpp
 *
 *  Created on: 11 mrt. 2012
 *      Author: acer
 */

#include "VisueelScherm.hpp"

VisueelScherm::VisueelScherm( WeerData* weerData )
{
	//sla de weerdata op in het attribuut
	this->weerData = weerData;

	//ken font en skin toe
	...

	//maak een achtergrond label om alle andere widgets in op te slaan, en te tonen
	Label* achtergrond = ...

	//maak een listbox met update en textueelknop
	this->listBox = new ...

	//knop om data te updaten
	this->updateKnop = new ...

	//knop om naar visueel te schakelen
	this->textueelKnop = new ...



	//staafdiagram

	//maak eerst een placeholder
	this->diagramTekening = maCreatePlaceholder();

	//laat de placeholder tekenbaar zijn
	maCreateDrawableImage( this->diagramTekening, EXTENT_X( maGetScrSize() ), EXTENT_Y( maGetScrSize() ) - 30 );

	//mak een nieuwe image met de placeholder
	this->diagramImage = new Image( 0, 30, EXTENT_X( maGetScrSize() ), EXTENT_Y( maGetScrSize() ) - 30, achtergrond, true, true, this->diagramTekening );


	this->setMain( achtergrond );
}


VisueelScherm::~VisueelScherm()
{
}


void VisueelScherm::update()
{
	//update waarden vam weerdata
	...

	//stel draw target in op onze tekening
	maSetDrawTarget( this->diagramTekening );

	//teken een staaf diagram

	//legenda
	//teken blokje en text met zonneschijn, neerslag en temperatuur

	//teken 10-stap lijnen

	//teken de staven van zonneschijn, neerslag en minimum temperatuur


	//altijd draw target na tekenen teruggeven naar scherm!
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


