#pragma once
/**@file BaseInputController.h
@author nieznanysprawiciel
@copyright Plik jest częścią silnika graficznego SWEngine.

@brief Klasa bazowa dla kontrollerów obsługujących wejście od użytkownika.*/


#include "EngineCore/ControllersEngine/BaseClasses/IController.h"


class InputAbstractionLayerBase;


/**@brief Klasa bazowa dla wszystkich kontrolerów do sterowania przez użytkownika.*/
class BaseInputController : public IController
{
	RTTR_ENABLE( IController )
protected:
	InputAbstractionLayerBase*		m_abstractionLayer;

public:
	explicit BaseInputController		( InputAbstractionLayerBase* layer );
	virtual ~BaseInputController		();

	void				SetAbstractionLayer	( InputAbstractionLayerBase* layer ) { m_abstractionLayer = layer; };
};
