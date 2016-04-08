// PropertiesTest.cpp : Defines the entry point for the console application.
//

#include "DerivedClass.h"

#include <iostream>
#include <memory>


#define SEPARATOR std::cout << std::endl;



int main()
{
	BaseClass		base;
	DerivedClass	derived;
	//auto type = rttr::type( rttr::type::get<BaseClass>().get_id() );

	std::cout << rttr::type::get<BaseClass>().get_name() << rttr::type::get<BaseClass>().get_id() << std::endl;
	std::cout << rttr::type::get<BaseClass*>().get_name() << rttr::type::get<BaseClass*>().get_id() << std::endl;
	std::cout << rttr::type::get<const BaseClass*>().get_name() << rttr::type::get< const BaseClass*>().get_id() << std::endl;

	SEPARATOR

	std::cout << "List all BaseClass properties" << std::endl;
	for( auto& prop : rttr::type::get( base ).get_properties() )
	{
		std::cout << prop.get_name() << "		type: " << prop.get_type().get_id() << std::endl;
	}

	SEPARATOR

	std::cout << "List all DerivedClass properties" << std::endl;
	for( auto& prop : rttr::type::get( derived ).get_properties() )
	{
		std::cout << prop.get_name() << "		type: " << prop.get_type().get_id() << std::endl;
		//prop.set_value(;
	}

	SEPARATOR

	auto rotProperty = rttr::type::get<BaseClass>().get_property( "Rotation" );
		
	auto value = rotProperty.get_value( base );
	bool isArray = value.is_array();
	auto arrayView = value.get_value< DirectX::XMFLOAT4 >();
	//std::cout << "Rotation x: " << arrayView.get_value( 0 ).to_float() << std::endl;
	//std::cout << "Rotation y: " << arrayView.get_value( 1 ).to_float() << std::endl;
	//std::cout << "Rotation z: " << arrayView.get_value( 2 ).to_float() << std::endl;
	//std::cout << "Rotation w: " << arrayView.get_value( 3 ).to_float() << std::endl;

	auto propertyX = rttr::type::get< DirectX::XMFLOAT4 >().get_property( "X" );
	auto propertyY = rttr::type::get< DirectX::XMFLOAT4 >().get_property( "Y" );
	auto propertyZ = rttr::type::get< DirectX::XMFLOAT4 >().get_property( "Z" );
	auto propertyW = rttr::type::get< DirectX::XMFLOAT4 >().get_property( "W" );

	std::cout << "Rotation x: " << propertyX.get_value( arrayView ).to_float() << std::endl;
	std::cout << "Rotation y: " << propertyY.get_value( arrayView ).to_float() << std::endl;
	std::cout << "Rotation z: " << propertyZ.get_value( arrayView ).to_float() << std::endl;
	std::cout << "Rotation w: " << propertyW.get_value( arrayView ).to_float() << std::endl;


	std::cout << "		Set Rotation" << std::endl;
	bool result = rotProperty.set_value( base, DirectX::XMFLOAT4( 3.0f, 4.0f, 6.0f, 32.4f ) );

	value = rotProperty.get_value( base );
	arrayView = value.get_value< DirectX::XMFLOAT4 >();
	std::cout << "Rotation x: " << arrayView.x << std::endl;
	std::cout << "Rotation y: " << arrayView.y << std::endl;
	std::cout << "Rotation z: " << arrayView.z << std::endl;
	std::cout << "Rotation w: " << arrayView.w << std::endl;

	SEPARATOR

	Property< float > typedPropertyX = base.GetTypedProperty< float >( "PositionX" );
	Property< float > typedPropertyY = base.GetTypedProperty< float >( "PositionY" );
	Property< float > typedPropertyZ = base.GetTypedProperty< float >( "PositionZ" );

	Property< bool > typedPropertySerialize = base.GetTypedProperty< bool >( "SerializeObject" );
	Property< int > typedPropertyNum = base.GetTypedProperty< int >( "NumObjects" );

	std::cout << "PositionX: " << typedPropertyX << std::endl;
	std::cout << "PositionY: " << typedPropertyY << std::endl;
	std::cout << "PositionZ: " << typedPropertyZ << std::endl;
	
	std::cout << "SerializeObject: " << typedPropertySerialize << std::endl;
	std::cout << "NumObjects: " << typedPropertyNum << std::endl;

	SEPARATOR

	// Nested properties and property pointer
	Property< IEnableProperty > PhysicalProperty = derived.GetTypedProperty< IEnableProperty >( "PhysicalProperty" );
	Property< IEnableProperty* > PhysicalPropertyPrev = derived.GetTypedProperty< IEnableProperty* >( "PhysicalPropertyPrev" );


	std::cout << "Nested property type id: " << PhysicalProperty.GetPropertyType().get_id() << std::endl;
	std::cout << "Nested property type raw id: " << PhysicalProperty.GetPropertyType().get_raw_type().get_id() << std::endl;

	std::cout << "Property ptr type id: " << PhysicalPropertyPrev.GetPropertyType().get_id() << std::endl;
	std::cout << "Property ptr type raw id: " << PhysicalPropertyPrev.GetPropertyType().get_raw_type().get_id() << std::endl;

	SEPARATOR

	Property< float > MassProperty = PhysicalProperty().GetTypedProperty< float >( "Mass" );
	Property< float > MomentProperty = PhysicalProperty().GetTypedProperty< float >( "Moment" );
	Property< float > RadiusProperty = PhysicalProperty().GetTypedProperty< float >( "Radius" );

	Property< float > MassPropertyPrev = PhysicalPropertyPrev()->GetTypedProperty< float >( "Mass" );
	Property< float > MomentPropertyPrev = PhysicalPropertyPrev()->GetTypedProperty< float >( "Moment" );
	Property< float > RadiusPropertyPrev = PhysicalPropertyPrev()->GetTypedProperty< float >( "Radius" );

	std::cout << "Mass: " << MassProperty << std::endl;
	std::cout << "Moment: " << MomentProperty << std::endl;
	std::cout << "Radius: " << RadiusProperty << std::endl;

	SEPARATOR

	std::cout << "MassPrev: " << MassPropertyPrev << std::endl;
	std::cout << "MomentPrev: " << MomentPropertyPrev << std::endl;
	std::cout << "RadiusPrev: " << RadiusPropertyPrev << std::endl;

	SEPARATOR

	Property< bool > MassPropertyWrongType = PhysicalProperty().GetTypedProperty< bool >( "Mass" );
	Property< int > MomentPropertyWrongType = PhysicalProperty().GetTypedProperty< int >( "Moment" );
	Property< double > RadiusPropertyWrongType = PhysicalProperty().GetTypedProperty< double >( "Radius" );

	if( MassPropertyWrongType.IsValid() )
		std::cout << "Mass casted to bool shouldn't be valid" << std::endl;

	if( MomentPropertyWrongType.IsValid() )
		std::cout << "Mass casted to int shouldn't be valid" << std::endl;

	if( MomentPropertyWrongType.IsValid() )
		std::cout << "Mass casted to double shouldn't be valid" << std::endl;


	SEPARATOR

	char end;
	std::cout << "Press any key to end...";
	std::cin >> end;

	return 0;
}

