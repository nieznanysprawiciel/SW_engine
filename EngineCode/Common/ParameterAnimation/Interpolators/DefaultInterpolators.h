#pragma once
/**
@file DefaultInterpolators.h
@author nieznanysprawiciel
@copyright File is part of graphic engine SWEngine.
*/


#include "IInterpolator.h"
#include "Common/ParameterAnimation/Key.h"


/**@brief Interpolators helpers functions.*/
namespace DefaultInterpolators
{

	template< typename KeyType >
	UPtr< IInterpolator< KeyType > >	CreateLinear	( const Key< KeyType >& leftKey,
														  const Key< KeyType >& rightKey,
														  UPtr< const IInterpolator< KeyType > >& leftInterpolator,
														  UPtr< const IInterpolator< KeyType > >& rightInterpolator );

	template< typename KeyType >
	UPtr< IInterpolator< KeyType > >	CreateDiscrete	( const Key< KeyType >& leftKey,
														  const Key< KeyType >& rightKey,
														  UPtr< const IInterpolator< KeyType > >& leftInterpolator,
														  UPtr< const IInterpolator< KeyType > >& rightInterpolator );

	/**@brief Function for creating default interpolators for different types of keys.
	Specialize this template in .cpp file.
	
	@note Left or right interpolator can be nullptr, but keys always exist.*/
	template< typename KeyType >
	UPtr< IInterpolator< typename std::enable_if< !std::is_arithmetic< KeyType >::value, KeyType >::type > >
		Create		( const Key< KeyType >& leftKey,
					  const Key< KeyType >& rightKey,
					  UPtr< const IInterpolator< KeyType > >& leftInterpolator,
					  UPtr< const IInterpolator< KeyType > >& rightInterpolator );

	template< typename KeyType >
	UPtr< IInterpolator< typename std::enable_if< std::is_floating_point< KeyType >::value, KeyType >::type > >
		Create		( const Key< KeyType >& leftKey,
					  const Key< KeyType >& rightKey,
					  UPtr< const IInterpolator< KeyType > >& leftInterpolator,
					  UPtr< const IInterpolator< KeyType > >& rightInterpolator );

	template< typename KeyType >
	UPtr< IInterpolator< typename std::enable_if< std::is_integral< KeyType >::value, KeyType >::type > >
		Create		( const Key< KeyType >& leftKey,
					  const Key< KeyType >& rightKey,
					  UPtr< const IInterpolator< KeyType > >& leftInterpolator,
					  UPtr< const IInterpolator< KeyType > >& rightInterpolator );


//====================================================================================//
//			Specialization declarations	
//====================================================================================//

#define DECLARE_SPECIALIZATON( type, Function )																	\
template																										\
UPtr< IInterpolator< type > >		Function< type >(	const Key< type >& leftKey,								\
														const Key< type >& rightKey,							\
														UPtr< const IInterpolator< type > >& leftInterpolator,	\
														UPtr< const IInterpolator< type > >& rightInterpolator );

DECLARE_SPECIALIZATON( float, CreateLinear );
DECLARE_SPECIALIZATON( double, CreateLinear );
DECLARE_SPECIALIZATON( char, CreateLinear );
DECLARE_SPECIALIZATON( uint8, CreateLinear );
DECLARE_SPECIALIZATON( int8, CreateLinear );
DECLARE_SPECIALIZATON( uint16, CreateLinear );
DECLARE_SPECIALIZATON( int16, CreateLinear );
DECLARE_SPECIALIZATON( uint32, CreateLinear );
DECLARE_SPECIALIZATON( int32, CreateLinear );
DECLARE_SPECIALIZATON( uint64, CreateLinear );
DECLARE_SPECIALIZATON( int64, CreateLinear );

#undef DECLARE_SPECIALIZATON

//====================================================================================//
//			Implementation	
//====================================================================================//

// ================================ //
//
template< typename KeyType >
inline UPtr< IInterpolator< typename std::enable_if< !std::is_arithmetic< KeyType >::value, KeyType >::type > >
	Create		( const Key< KeyType >& leftKey,
					const Key<KeyType>& rightKey,
					UPtr< const IInterpolator< KeyType > >& leftInterpolator,
					UPtr< const IInterpolator< KeyType > >& rightInterpolator )
{
	static_assert( false, "Implement specialization" );
	return UPtr<IInterpolator<KeyType>>();
}


// ================================ //
//
template< typename KeyType >
inline UPtr< IInterpolator< typename std::enable_if< std::is_floating_point< KeyType >::value, KeyType >::type > >
	Create		( const Key< KeyType >& leftKey,
					const Key<KeyType>& rightKey,
					UPtr< const IInterpolator< KeyType > >& leftInterpolator,
					UPtr< const IInterpolator< KeyType > >& rightInterpolator )
{
	return CreateLinear( leftKey, rightKey, leftInterpolator, rightInterpolator );
}


// ================================ //
//
template< typename KeyType >
inline UPtr< IInterpolator< typename std::enable_if< std::is_integral< KeyType >::value, KeyType >::type > >
	Create		( const Key< KeyType >& leftKey,
					const Key<KeyType>& rightKey,
					UPtr< const IInterpolator< KeyType > >& leftInterpolator,
					UPtr< const IInterpolator< KeyType > >& rightInterpolator )
{
	return CreateLinear( leftKey, rightKey, leftInterpolator, rightInterpolator );
}



}	// DefaultInterpolators
