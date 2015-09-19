#pragma once

#include "../DX11Initializer/DX11APIObjects.h"
#include "GraphicAPI\MeshResources.h"


/**@brief Implementacja tekstury w DirectX 11.
@ingroup DX11API*/
class DX11Texture	:	public TextureObject, public DX11APIObjects
{
private:
	ID3D11ShaderResourceView*				m_texture;
protected:
	~DX11Texture();
public:
	DX11Texture( const std::wstring& path, ID3D11ShaderResourceView* tex );


	inline ID3D11ShaderResourceView*		Get() { return m_texture; }

	static DX11Texture*						CreateFromFile			( const std::wstring& fileName );
	static DX11Texture*						CreateFromMemory		();
};

