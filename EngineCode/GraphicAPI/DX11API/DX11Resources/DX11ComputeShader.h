#pragma once

#include "GraphicAPI/MeshResources.h"
#include "DX11Initializer/DX11APIObjects.h"


/**@brief Implementacja compute shadera w DirectX11.
@ingroup DX11API*/
class DX11ComputeShader :	 public ComputeShader, protected DX11APIObjects
{
	RTTR_ENABLE( ComputeShader );
private:
	ID3D11ComputeShader*			m_computeShader;
protected:
	~DX11ComputeShader();
public:
	explicit DX11ComputeShader		( ID3D11ComputeShader* shader );

	inline ID3D11ComputeShader*		Get() { return m_computeShader; }

	virtual bool					ReloadFromFile			() override;
	virtual bool					ReloadFromBinFile		() override;
	virtual void					SaveShaderBinFile		( const std::wstring& fileName ) override;

	static DX11ComputeShader*		CreateFromFile			( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel = "cs_4_0" );
	static DX11ComputeShader*		CreateFromBinFile		( const std::wstring& fileName );
};

