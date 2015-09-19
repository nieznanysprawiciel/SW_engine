#pragma once

#include "GraphicAPI\MeshResources.h"
#include "../DX11Initializer/DX11APIObjects.h"


/**@brief Implementacja pixel shadera w DirectX 11.
@ingroup DX11API*/
class DX11PixelShader :		public PixelShaderObject, public DX11APIObjects
{
private:
	ID3D11PixelShader*			m_pixelShader;
protected:
	~DX11PixelShader();
public:
	DX11PixelShader( ID3D11PixelShader* shader );

	inline ID3D11PixelShader*			Get() { return m_pixelShader; }

	virtual bool						ReloadFromFile			() override;
	virtual bool						ReloadFromBinFile		() override;
	virtual void						SaveShaderBinFile		( const std::wstring& fileName ) override;

	static DX11PixelShader*				CreateFromFile			( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel = "vs_4_0" );
	static DX11PixelShader*				CreateFromBinFile		( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel = "vs_4_0" );
};

