#pragma once

//using Float3 = System::Numerics::;

#include "PropertyHelper.h"
#include "EngineCore/Actors/BasicActors/EngineObject.h"

#include <memory>

class EngineObject;

namespace EditorPlugin
{
using namespace System::Collections::Generic;

	public ref class PropertyWrapper
	{
	protected:

		System::String^			m_name;
		PropertyType			m_type;

		EngineObject*			m_actorPtr;		///< Wskaźnik używany do pobierania parametrów obiektu klasy.

	protected:
		
		const rttr::detail::property_wrapper_base*			m_metaProperty;

	public:
		PropertyWrapper( PropertyType type, rttr::property prop, const char* name )
			: m_type( type )
			, m_actorPtr( nullptr )
		{
			m_metaProperty = RTTRPropertyRapist::GetWrapperBase( prop );
			m_name = gcnew System::String( name );
		}


		virtual void			ResetActor		( System::IntPtr objectPtr );
		PropertyType			GetPropertyType	( rttr::property prop )
		{
			auto propertyType = prop.get_type();
			if( propertyType == rttr::type::get< int >() )
				return PropertyType::PropertyInt;
			else if( propertyType == rttr::type::get< float >() )
				return PropertyType::PropertyFloat;
			else if( propertyType == rttr::type::get< bool >() )
				return PropertyType::PropertyBool;
			else if( propertyType == rttr::type::get< double >() )
				return PropertyType::PropertyDouble;
			else if( propertyType == rttr::type::get< DirectX::XMFLOAT2 >() )
				return PropertyType::PropertyFloat2;
			else if( propertyType == rttr::type::get< DirectX::XMFLOAT3 >() )
				return PropertyType::PropertyFloat3;
			else if( propertyType == rttr::type::get< DirectX::XMFLOAT4 >() )
				return PropertyType::PropertyFloat4;
			else if( propertyType.is_derived_from< EngineObject >() )
				return PropertyType::PropertyActor;
			else
				return PropertyType::PropertyUnknown;
		}

	public:
		property PropertyType		Type
		{
			PropertyType		get() { return m_type; }
		}

		property System::String^	PropertyName
		{
			System::String^		get() { return m_name; }
		}
	};


//====================================================================================//
//			Classes derived from PropertyWrapper	
//====================================================================================//

	/**@brief Property typu DirectX::XMFLOAT2.
	@attention KLasa nieużywana.*/
	public ref class Float2PropertyWrapper : PropertyWrapper
	{
	public:
		Float2PropertyWrapper( rttr::property prop )
			: PropertyWrapper( PropertyType::PropertyFloat2, prop, prop.get_name().c_str() )
		{}

		float		GetValueX		( System::IntPtr refObject );
		void		SetValueX		( System::IntPtr refObject, float newValue );

		float		GetValueY		( System::IntPtr refObject );
		void		SetValueY		( System::IntPtr refObject, float newValue );

	};

	/**@brief Property typu DirectX::XMFLOAT3.
	@attention KLasa nieużywana.*/
	public ref class Float3PropertyWrapper : PropertyWrapper
	{
	public:
		Float3PropertyWrapper( rttr::property prop )
			: PropertyWrapper( PropertyType::PropertyFloat3, prop, prop.get_name().c_str() )
		{}

		float		GetValueX		( System::IntPtr refObject );
		void		SetValueX		( System::IntPtr refObject, float newValue );

		float		GetValueY		( System::IntPtr refObject );
		void		SetValueY		( System::IntPtr refObject, float newValue );

		float		GetValueZ		( System::IntPtr refObject );
		void		SetValueZ		( System::IntPtr refObject, float newValue );
	};

	/**@brief Property typu DirectX::XMFLOAT4.
	@attention KLasa nieużywana.*/
	public ref class Float4PropertyWrapper : PropertyWrapper
	{
	public:
		Float4PropertyWrapper( rttr::property prop )
			: PropertyWrapper( PropertyType::PropertyFloat4, prop, prop.get_name().c_str() )
		{}


		float		GetValueX		( System::IntPtr refObject );
		void		SetValueX		( System::IntPtr refObject, float newValue );

		float		GetValueY		( System::IntPtr refObject );
		void		SetValueY		( System::IntPtr refObject, float newValue );

		float		GetValueZ		( System::IntPtr refObject );
		void		SetValueZ		( System::IntPtr refObject, float newValue );

		float		GetValueW		( System::IntPtr refObject );
		void		SetValueW		( System::IntPtr refObject, float newValue );
	};

	/**@brief Property typy in.*/
	public ref class IntPropertyWrapper : PropertyWrapper
	{
	public:
		IntPropertyWrapper( rttr::property prop )
			: PropertyWrapper( PropertyType::PropertyInt, prop, prop.get_name().c_str() )
		{}

		int						GetValue		( System::IntPtr refObject );
		void					SetValue		( System::IntPtr refObject, int newValue );
	};

	/**@brief Property typu bool.*/
	public ref class BoolPropertyWrapper : PropertyWrapper
	{
	public:
		BoolPropertyWrapper( rttr::property prop )
			: PropertyWrapper( PropertyType::PropertyBool, prop, prop.get_name().c_str() )
		{}

		bool		GetValue		( System::IntPtr refObject );
		void		SetValue		( System::IntPtr refObject, bool newValue );
	};

	/**@brief Property typu float.*/
	public ref class FloatPropertyWrapper : PropertyWrapper
	{
	public:
		FloatPropertyWrapper( rttr::property prop )
			: PropertyWrapper( PropertyType::PropertyFloat, prop, prop.get_name().c_str() )
		{}

		float		GetValue		( System::IntPtr refObject );
		void		SetValue		( System::IntPtr refObject, float newValue );
	};

	/**@brief Property typu double.*/
	public ref class DoublePropertyWrapper : PropertyWrapper
	{
	public:
		DoublePropertyWrapper( rttr::property prop )
			: PropertyWrapper( PropertyType::PropertyDouble, prop, prop.get_name().c_str() )
		{}

		double		GetValue		( System::IntPtr refObject );
		void		SetValue		( System::IntPtr refObject, double newValue );

	public:
		//property double		Value
		//{
		//	double get()
		//	{
		//		if( m_actorPtr )
		//			return GetValue( m_actorPtr );
		//		return std::numeric_limits< double >::max();
		//	}

		//	void set( double value )
		//	{
		//		if( m_actorPtr )
		//			SetValue( m_actorPtr, value );
		//		else
		//			SetValue( m_actorPtr, std::numeric_limits< double >::max() );
		//	}
		//}
	};

//====================================================================================//
//			Generic object wrapper	
//====================================================================================//

	/**@brief Klasa będąca zbiorem Property należących do jednej kategorii.*/
	public ref class CategoryPropertyWrapper : PropertyWrapper
	{
	private:

		List< PropertyWrapper^ >^			m_properties;

	protected:

		CategoryPropertyWrapper( PropertyType type, rttr::property prop, const char* name )
			: PropertyWrapper( type, prop, name )
		{
			m_properties = gcnew List< PropertyWrapper^ >();
		}

	public:
		CategoryPropertyWrapper( const char* name )
			: PropertyWrapper( PropertyType::PropertyCategory, RTTRPropertyRapist::MakeProperty( nullptr ), name )
		{
			m_properties = gcnew List< PropertyWrapper^ >();
		}

		virtual void			ResetActor		( System::IntPtr objectPtr ) override;
		virtual void			BuildHierarchy	( rttr::type classType );

	protected:
		PropertyWrapper^		BuildProperty	( rttr::property property );

	public:
		property List< PropertyWrapper^ >^	Properties
		{
			List< PropertyWrapper^ >^		get() { return m_properties; }
		}
	};



	/**@brief Property dla obiektów złożonych dziedziczących po EngineObject.*/
	public ref class ObjectPropertyWrapper : CategoryPropertyWrapper
	{
	private:

		List< PropertyWrapper^ >^			m_properties;

	public:
		ObjectPropertyWrapper( rttr::property prop )
			: CategoryPropertyWrapper( PropertyType::PropertyActor, prop, prop.get_name().c_str() )
		{}

		void					BuildHierarchy	();

	};

	/**@brief Property typu DirectX::XMFLOAT2, XMFLOAT3, XMFLOAT4.*/
	public ref class XMFloatPropertyWrapper : CategoryPropertyWrapper
	{
	private:
	public:
		XMFloatPropertyWrapper( rttr::property prop )
			: CategoryPropertyWrapper( GetPropertyType( prop ), prop, prop.get_name().c_str() )
		{}

		void			BuildHierarchy	( rttr::type classType ) override;
		void			BuildHierarchy	();
	};


}
