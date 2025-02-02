#pragma once

#include "GraphicAPI/MeshResources.h"
#include "GraphicAPI/SwapChain.h"

#include <string>

namespace GUI
{



struct NativeWindowDescriptor
{
	WindowHandler			ParentHandle;
	unsigned short			Width;
	unsigned short			Height;
	unsigned short			PositionX;
	unsigned short			PositionY;
	bool					Fullscreen			: 1;
	bool					ShowWindow			: 1;	///< Show window immediately after creation.
	bool					AddExitButton		: 1;
	bool					AddMinimizeButton	: 1;
	bool					AddMaximizeButton	: 1;
	bool					AddFrame			: 1;
	bool					AddTitleBar			: 1;
	bool					AdjustSize			: 1;	///< Adjust window size to client area.
	std::string				WindowTitle;


// ================================ //
//
	NativeWindowDescriptor()
	{
		InitDefaults();
	}

	NativeWindowDescriptor( const std::string& windowTitle )
		:	WindowTitle( windowTitle )
	{
		InitDefaults();
	}

	void InitDefaults()
	{
		ParentHandle = nullptr;
		Width = 1024;
		Height = 768;
		PositionX = 0;
		PositionY = 0;
		Fullscreen = false;
		ShowWindow = true;
		AddExitButton = true;
		AddMinimizeButton = true;
		AddMaximizeButton = true;
		AddFrame = true;
		AddTitleBar = true;
		AdjustSize = true;
	}
};


/**@brief Klasa bazowa kontenera dla natywnego okna danego systemu.

Natywne okno powinno udost�pnia� przynajmniej sw�j render target i swapchain.
Ponadto mo�e zawiera� funkcje do obs�ugi prawdziwego okna, ale nie jest to konieczne.
GUI nie musi samo obs�ugiwa� prawdziwych okien, mo�e mie� je dostarczone przez aplikacj�.*/
class INativeWindow
{
private:
protected:
public:
	INativeWindow() = default;
	~INativeWindow() = default;

	virtual uint16				GetWidth	() = 0;
	virtual uint16				GetHeght	() = 0;

	virtual uint16				GetClientWidth	() = 0;
	virtual uint16				GetClientHeight	() = 0;

	virtual WindowHandler		GetHandle	() = 0;
	virtual std::string			GetTitle	() = 0;

	virtual void				Show		() = 0;
	virtual void				Hide		() = 0;
	
	virtual void				SetTitle	( const std::string& newTitle ) = 0;
};



}	// GUI
