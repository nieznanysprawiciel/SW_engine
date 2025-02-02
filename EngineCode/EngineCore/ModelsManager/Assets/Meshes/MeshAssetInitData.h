#pragma once

#include "Common/TypesDefinitions.h"
#include "Common/MemoryChunk.h"
#include "GraphicAPI/MeshResources.h"

#include "MeshPart.h"

#include <vector>



/**@brief Structure used to initialize class @ref MeshAsset.
@ingroup MeshAsset*/
struct MeshInitData
{
	MemoryChunk							VertexBuffer;		///< Data used to fill vertex buffer.
	MemoryChunk							IndexBuffer;		///< Data used to fill index buffer.
	ResourcePtr< ShaderInputLayout >	VertexLayout;		///< Vertex layout descriptor.
	std::vector< MeshPart >				MeshSegments;		///< Mesh segments.
	uint32								NumVerticies;
	uint32								VertexSize;
	uint32								NumIndicies;
	PrimitiveTopology					Topology;			///< Mesh topology.
	bool								ExtendedIndex;		///< 4 bytes index.

	MeshInitData() {}
	MeshInitData( MeshInitData&& init );
};


/**@brief Structure initializes @ref MeshAsset with existing buffers.
@ingroup MeshAsset*/
struct MeshCreateData
{
	ResourcePtr< BufferObject >			VertexBuffer;
	ResourcePtr< BufferObject >			IndexBuffer;
	ResourcePtr< ShaderInputLayout >	VertexLayout;
	std::vector< MeshPart >				MeshSegments;		///< Mesh segments.
};



inline MeshInitData::MeshInitData( MeshInitData&& init )
	:	VertexBuffer( std::move( init.VertexBuffer ) )
	,	IndexBuffer( std::move( init.IndexBuffer ) )
	,	VertexLayout( std::move( init.VertexLayout ) )
	,	MeshSegments( std::move( init.MeshSegments ) )
	,	NumVerticies( init.NumVerticies )
	,	VertexSize( init.VertexSize )
	,	NumIndicies( init.NumIndicies )
	,	Topology( init.Topology )
	,	ExtendedIndex( init.ExtendedIndex )
{}
