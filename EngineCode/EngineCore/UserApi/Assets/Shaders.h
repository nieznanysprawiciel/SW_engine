#pragma once
/**@file Shaders.h
@author nieznanysprawiciel
@copyright Plik jest cz�ci� silnika graficznego SWEngine.

@brief Deklaracja klasy Shaders.*/

class VertexShader;
class PixelShader;
class ShaderInputLayout;
class InputLayoutDescriptor;


#include "EngineCore/UserApi/ApiGroup.h"
#include "GraphicAPI/ResourcePtr.h"

#include <string>


namespace Api { namespace Assets {

	/**@brief Zapewnia dost�p do modeli w klasie AssetsManager.
	@ingroup UserAPI
	@ingroup AssetsAPI*/
	class Shaders : public ApiGroup
	{
	private:
	protected:
	public:
		Shaders() = default;
		~Shaders() = default;

		VertexShader*		GetVertexShaderSync		( const std::wstring& name );
		VertexShader*		LoadVertexShaderSync	( const std::wstring& name );
		VertexShader*		LoadVertexShaderSync	( const std::wstring& name, ShaderInputLayout** layout, InputLayoutDescriptor* layoutDesc );
		PixelShader*		GetPixelShaderSync		( const std::wstring& name );
		PixelShader*		LoadPixelShaderSync		( const std::wstring& name );

		std::vector< ResourcePtr< VertexShader > >			ListVertexShaders	();
		std::vector< ResourcePtr< PixelShader > >			ListPixelShaders	();
		std::vector< ResourcePtr< ShaderInputLayout > >		ListShaderLayouts	();
	};


}	// Assets
}	// Api
