#include "Serializer.h"


#define RAPIDJSON_HAS_STDSTRING 1
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include <fstream>
#include <stack>

struct SerializerImpl
{
	rapidjson::Document				root;
	std::stack<rapidjson::Value>	valuesStack;
};


/**@brief Konstruktor*/
ISerializer::ISerializer()
{
	impl = new SerializerImpl;
	rapidjson::Value newObject( rapidjson::kObjectType );
	impl->valuesStack.push( std::move( newObject ) );
}

/**@brief Destruktor*/
ISerializer::~ISerializer()
{ delete impl; }

std::string	ISerializer::SaveString()
{
	while( impl->valuesStack.size() > 1 )
		this->Exit();

	rapidjson::Value& topValue = impl->valuesStack.top();
	rapidjson::Value& documentObject = impl->root.SetObject();
	documentObject = std::move( topValue );

	rapidjson::StringBuffer stringBuffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer( stringBuffer );

	return stringBuffer.GetString();
}


/**@brief Zapisuje zserializowane dane do pliku.
@param[in] fileName Nazwa pliku docelowego.
@return Zwraca true, je�eli zapisywanie powiedzie si�.*/
bool ISerializer::SaveFile( const std::string& fileName )
{
	std::fstream file;
	file.open( fileName );
	if( !file.fail() )
	{
		while( impl->valuesStack.size() > 1 )
			this->Exit();

		rapidjson::Value& topValue = impl->valuesStack.top();
		rapidjson::Value& documentObject = impl->root.SetObject();
		documentObject = std::move( topValue );

		rapidjson::StringBuffer stringBuffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer( stringBuffer );
		impl->root.Accept( writer );

		file << stringBuffer.GetString();

		file.close();
		return true;
	}
	return false;
}

/**@brief Tworzy obiekt o podanej nazwie.

@param[in] name Nazwa obiektu.*/
void ISerializer::EnterObject( const std::string& name )
{
	rapidjson::Value newObject( rapidjson::kObjectType );
	rapidjson::Value newName( rapidjson::kStringType );
	newName.SetString( name.c_str(), (rapidjson::SizeType)name.length(), impl->root.GetAllocator() );

	// Wrzucamy nazw� jako pierwsz�, a potem sam obiekt.
	impl->valuesStack.push( std::move( newName ) );
	impl->valuesStack.push( std::move( newObject ) );
}

/**@brief Koniec tworzenia obiektu.
EnterObject i ExitObject powinny by� stosowane parami.*/
void ISerializer::Exit()
{
	rapidjson::Value& objectValue = impl->valuesStack.top();		// Obiekt, kt�re go konstruowanie skonczyli�my.
	impl->valuesStack.pop();
	rapidjson::Value& objectName = impl->valuesStack.top();			// Nazwa obiektu.
	impl->valuesStack.pop();

	rapidjson::Value& newCurrentObject = impl->valuesStack.top();
	newCurrentObject.AddMember( std::move( objectName ), std::move( objectValue ), impl->root.GetAllocator() );
}

/**@brief Tworzy tablic� o podanej nazwie.

@param[in] name Nazwa tablicy.*/
void ISerializer::EnterArray( const std::string& name )
{ }

/**@brief Ustawia par� ( nazwa, warto�� ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] value Warto��, jaka zostanie wpisana do podanej zmiennej.*/
void ISerializer::SetValue( const std::string& name, const std::string& value )
{
	rapidjson::Value& currentObject = impl->valuesStack.top();	// Obiekt, do kt�rego przyczepiamy atrybut.
	rapidjson::Value newObject;
	rapidjson::Value valueName;
	valueName.SetString( name.c_str(), (rapidjson::SizeType)name.length(), impl->root.GetAllocator() );
	newObject.SetString( value.c_str(), (rapidjson::SizeType)value.length(), impl->root.GetAllocator() );
	currentObject.AddMember( std::move( valueName ), std::move( newObject ), impl->root.GetAllocator() );
}

/**@brief Ustawia par� ( nazwa, warto�� ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] value Warto��, jaka zostanie wpisana do podanej zmiennej.*/
void ISerializer::SetValue( const std::string& name, const char* value )
{
	rapidjson::Value& currentObject = impl->valuesStack.top();	// Obiekt, do kt�rego przyczepiamy atrybut.
	rapidjson::Value newObject;
	rapidjson::Value valueName;
	valueName.SetString( name.c_str(), (rapidjson::SizeType)name.length(), impl->root.GetAllocator() );
	newObject.SetString( value, (rapidjson::SizeType)strlen( value ), impl->root.GetAllocator() );
	currentObject.AddMember( std::move( valueName ), std::move( newObject ), impl->root.GetAllocator() );
}

/**@brief Ustawia par� ( nazwa, warto�� ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] value Warto��, jaka zostanie wpisana do podanej zmiennej.*/
void ISerializer::SetValue( const std::string& name, uint32 value )
{ }

/**@brief Ustawia par� ( nazwa, warto�� ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] value Warto��, jaka zostanie wpisana do podanej zmiennej.*/
void ISerializer::SetValue( const std::string& name, uint64 value )
{ }

/**@brief Ustawia par� ( nazwa, warto�� ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] value Warto��, jaka zostanie wpisana do podanej zmiennej.*/
void ISerializer::SetValue( const std::string& name, int32 value )
{ }

/**@brief Ustawia par� ( nazwa, warto�� ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] value Warto��, jaka zostanie wpisana do podanej zmiennej.*/
void ISerializer::SetValue( const std::string& name, int64 value )
{ }

/**@brief Ustawia par� ( nazwa, warto�� ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] value Warto��, jaka zostanie wpisana do podanej zmiennej.*/
void ISerializer::SetValue( const std::string& name, bool value )
{ }

/**@brief Ustawia par� ( nazwa, warto�� ) w aktualnym obiekcie.

@param[in] name Nazwa ustawianej zmiennej.
@param[in] value Warto��, jaka zostanie wpisana do podanej zmiennej.*/
void ISerializer::SetValue( const std::string& name, double value )
{ }


