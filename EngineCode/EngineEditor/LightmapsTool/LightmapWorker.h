#pragma once

#include "EngineEditor/LightmapsTool/ExchangeDataStructs.h"


class LightmapWorker
{
private:
protected:
	SceneData*					m_data;
	LightmapState				m_lightmapState;
	std::vector<MemoryChunk>	m_resultData;			///<Zawiera wsp�rz�dne UV oraz dane kolor�w wierzcho�k�w. (Nie przechowuje wierzcho�k�w!!)

	unsigned int				m_depthResolution;		///< Rozdzielczo�� bufora g��boko�ci.
public:
	LightmapWorker( SceneData* sceneData )
			:	m_data( sceneData ),
				m_lightmapState( LightmapState::Generating ),
				m_depthResolution( 1024 )
	{}
	~LightmapWorker() = default;

	SceneData*					GetSceneData	()	{ return m_data; }
	LightmapState				GetState		()	{ return m_lightmapState; }
	std::vector<MemoryChunk>&&	MoveResult		()	{ return std::move( m_resultData ); }

	void	SetDepthResolution	( unsigned int resolution )		{ m_depthResolution = resolution; }

	/**@brief G��wna funkcja generuj�ca lightmapy. Zaimplementuj w klasie pochodnej.*/
	virtual void				Generate		() = 0;
};

