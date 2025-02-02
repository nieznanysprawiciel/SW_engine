#pragma once
/**
@file IRenderPass.h
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/

#include "Common/EngineObject.h"


#include "GraphicAPI/MeshResources.h"
#include "GraphicAPI/RasterizerState.h"
#include "GraphicAPI/BlendingState.h"
#include "GraphicAPI/DepthStencilState.h"
#include "GraphicAPI/IRenderer.h"

#include "EngineCore/DisplayEngine/RenderContext.h"

#include <DirectXMath.h>
#include <vector>

class RenderTargetObject;
class CameraActor;
class StaticActor;
class ShaderInputLayout;
class AssetsManager;
class RenderPassFactory;


/**@defgroup RenderPasses Render Passes
@brief Rendering pipeline.

@ingroup Rendering*/




/**@brief Base class for render passes.

@ingroup RenderPasses*/
class IRenderPass : public EngineObject
{
	friend void		SetAssetManager		( AssetsManager* manager );
	friend void		SetFactory			( RenderPassFactory* manager );
protected:
	static AssetsManager*		s_assetsManager;		///< Definition in RenderPassFactory.cpp file.
	static RenderPassFactory*	s_renderPassFactory;	///< Definition in RenderPassFactory.cpp file.

public:
	enum class ActorAddPolicy
	{
		All,
		None,
		Static,
		Dynamic
	};

private:
protected:

	ActorAddPolicy						m_addPolicy;

public:

	explicit		IRenderPass	() = default;
	virtual			~IRenderPass() {}

	void			AddActor	( StaticActor* actor, bool isDynamic );
	void			DeleteActor	( StaticActor* actor );

	/**@brief Prepares for rendering. This function should make all initialization.
	@return If this function returns false, functions Render and PostRender won't be called.*/
	virtual bool	PreRender	( IRenderer* renderer, RenderContext& context ) = 0;

	/**@brief Object rendering function.*/
	virtual void	Render		( IRenderer* renderer, RenderContext& context, Size rangeStart, Size rangeEnd ) = 0;

	/**@brief Function will be called after rendering will be completed.*/
	virtual void	PostRender	( IRenderer* renderer, RenderContext& context ) = 0;


	virtual void	NestedPasses( std::vector< Ptr< IRenderPass > >& passes ) = 0;

protected:
	template< typename PassType >
	void			FillWithNestedPasses	( std::vector< Ptr< IRenderPass > >& dest,  std::vector< Ptr< PassType > >& passes );
};

//====================================================================================//
//			Implementation	
//====================================================================================//

template< typename PassType >
inline void			IRenderPass::FillWithNestedPasses	( std::vector< Ptr< IRenderPass > >& dest, std::vector< Ptr< PassType > >& passes )
{
	for( auto& pass : passes )
	{
		dest.push_back( pass );
		pass->NestedPasses( dest );
	}
}
