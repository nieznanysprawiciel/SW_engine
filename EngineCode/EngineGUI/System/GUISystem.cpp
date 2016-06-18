#include "GUISystem.h"

namespace GUI
{



/**@brief G��wna p�tla aplikacji.

@see Application
*/
int					GUISystem::MainLoop()
{
	return 0;
}

/**@brief Pozwala ustawi� i pobra� DataContext.

DataContext zostanie przepropagowany do wszystkich kontrolek w hierarchii.*/
EngineObject*&		GUISystem::DataContext()
{
	return m_dataContext;
}

/**@copydoc EngineObject::MemorySize*/
Size				GUISystem::GetMemorySize()
{
	Size size = sizeof( HostWindow );
	size += m_windows.capacity() * sizeof( HostWindow* );

	for( auto window : m_windows )
		size += window->GetMemorySize();

	return size;
}

}	// GUI

