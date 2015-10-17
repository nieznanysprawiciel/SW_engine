/**@file EngineInterface.cpp
@author nieznanysprawiciel
@copyright Plik jest cz�ci� silnika graficznego SWEngine.

@brief Plik zawiera implementacj� interfejsu EngineInterface dla klasy Engine
*/
#include "EngineCore/stdafx.h"
#include "Engine.h"
#include "EngineCore/EventsManager/Event.h"
#include "EngineCore/CollisionEngine/CollisionEngine.h"
#include "EngineCore/ControllersEngine/ControllersEngine.h"
#include "EngineCore/GamePlay/FableEngine.h"
#include "EngineCore/DisplayEngine/DisplayEngine.h"
#include "EngineCore/ModelsManager/ModelsManager.h"
#include "EngineCore/PhysicEngine/PhysicEngine.h"
#include "EngineCore/PhysicEngine/MovementEngine.h"
#include "EngineCore/SoundEngine/SoundEngine.h"
#include "EngineCore/UIEngine/UI_Engine.h"

#include <mutex>

#include "Common/memory_leaks.h"



Engine* EngineInterface::InterfaceGroup::m_engine = nullptr;


EngineInterface::EngineInterface()
{
	EngineInterface::InterfaceGroup::m_engine = static_cast<Engine*>( this );		// EngineInterface jest tak na prawd� klas� Engine, wi�c takie rzutowanie jest legalne.
}

#ifdef __TEST

#include "EngineCore/ControllersEngine/camera_controller_PROTOTYPE.h"
#include "EngineCore/Features/HosekSkylightModel/HosekSkyDome.h"

void Engine::test()
{
	const wchar_t CLONE_FIGHTER[] = L"tylko_do_testow/ARC.FBX";
	const wchar_t MOON[] = L"tylko_do_testow/moon/moon.FBX";
	const wchar_t NEBULON[] = L"tylko_do_testow/Nebulon/Nebulon.FBX";
	const wchar_t VADER_TIE[] = L"tylko_do_testow/VadersTIE.FBX";
	const wchar_t TIE_FIGHTER[] = L"tylko_do_testow/TIE_Fighter/TIE_Fighter.FBX";
	const wchar_t IMPERIAL_STAR_DESTROYER[] = L"tylko_do_testow/ImperialStarDestroyer.FBX";

	models_manager->LoadModelFromFile( CLONE_FIGHTER );
	models_manager->LoadModelFromFile( MOON );
	models_manager->LoadModelFromFile( NEBULON );
	models_manager->LoadModelFromFile( VADER_TIE );
	models_manager->LoadModelFromFile( TIE_FIGHTER );
	//models_manager->LoadModelFromFile( IMPERIAL_STAR_DESTROYER );
	
	//models_manager->test();			// Tu sie odbywa wczytywanie

	//dodawanie ksi�yca
	DynamicMeshObject* moon = new DynamicMeshObject;
	XMVECTOR position = XMVectorSet( 4000.0, 0.0, 8000.0, 0.0 );
	moon->teleport( position );

	moon->set_model( models_manager->GetModel( MOON ) );
	moon->set_scale( 30.0 );

	object_list.push_back( moon );
	display_engine->add_dynamic_mesh_object( moon );

	//dodawanie Nebulona
	DynamicMeshObject* nebulon = new DynamicMeshObject;
	position = XMVectorSet( 400.0, 0.0, -6000.0, 0.0 );
	nebulon->teleport( position );

	nebulon->set_model( models_manager->GetModel( NEBULON ) );
	nebulon->set_scale( 1 );	//Nebulon ma �le ustawiony pivot, wi�c jak si� przeskaluje to odleci gdzie� w kosmos i go nie wida�.

	object_list.push_back( nebulon );
	display_engine->add_dynamic_mesh_object( nebulon );

	//dodawanie TIE Fightera
	DynamicMeshObject* TIE = new DynamicMeshObject;
	position = XMVectorSet( -400.0, 0.0, 800.0, 0.0 );
	TIE->teleport( position );

	TIE->set_model( models_manager->GetModel( TIE_FIGHTER ) );
	TIE->set_scale( 10 );

	object_list.push_back( TIE );
	display_engine->add_dynamic_mesh_object( TIE );


	//dodawanie TIE Fightera Vadera
	DynamicMeshObject* VaderTIE = new DynamicMeshObject;
	position = XMVectorSet( -400.0, 0.0, -3000.0, 0.0 );
	VaderTIE->teleport( position );

	VaderTIE->set_model( models_manager->GetModel( VADER_TIE ) );
	//VaderTIE->set_scale( 1.0 );

	object_list.push_back( VaderTIE );
	display_engine->add_dynamic_mesh_object( VaderTIE );

	//dodawanie my�liwca
	DynamicMeshObject* clone_fighter = new DynamicMeshObject;
	position = XMVectorSet(0.0, 0.0, 6000.0, 0.0);
	clone_fighter->teleport( position );

#ifdef _QUATERNION_SPEED
	XMVECTOR rot_vector = { 1.0f, 0.0f, 0.0f, 0.0f };
	XMVECTOR axis_angle = XMQuaternionRotationAxis(rot_vector, XMConvertToRadians(30));
#else
	XMFLOAT4 axis_angle;
	axis_angle.x = 1.0;
	axis_angle.y = 0.0;
	axis_angle.z = 0.0;
	axis_angle.w = XMConvertToRadians(30);
#endif
	clone_fighter->set_rotation_speed( axis_angle );

	clone_fighter->set_model( models_manager->GetModel( CLONE_FIGHTER ) );

	object_list.push_back( clone_fighter );
	display_engine->add_dynamic_mesh_object( clone_fighter );
	movement_engine->add_moveable_object( clone_fighter );


	// Dodawanie gwiezdnego niszczyciela Imperial
	/*DynamicMeshObject* Imperial = new DynamicMeshObject;
	position = XMVectorSet( -4000.0, 0.0, -3000.0, 0.0 );
	Imperial->set_position( position );

	Imperial->set_model( models_manager->GetModel( IMPERIAL_STAR_DESTROYER ) );

	object_list.push_back( Imperial );
	display_engine->add_dynamic_mesh_object( Imperial );
	*/

	/*
	//dodawanie skrzyni
	DynamicMeshObject* skrzynia = new DynamicMeshObject;
	position = XMVectorSet( 0.0, 0.0, 2.0, 0.0 );
	skrzynia->set_position( position );

#ifdef _QUATERNION_SPEED
	XMVECTOR rot_vector = { 1.0f, 0.0f, 0.0f, 0.0f };
	XMVECTOR axis_angle = XMQuaternionRotationAxis( rot_vector, XMConvertToRadians( 30 ) );
#else
	XMFLOAT4 axis_angle2;
	axis_angle2.x = 1.0;
	axis_angle2.y = 0.0;
	axis_angle2.z = 0.0;
	axis_angle2.w = XMConvertToRadians( 30 );
#endif
	//skrzynia->set_rotation_speed( axis_angle2 );

	Model3DFromFile* new_model = models_manager->GetModel( L"skrzynia" );
	skrzynia->set_model( new_model );
	//skrzynia->set_scale( 0.1 );

	object_list.push_back( skrzynia );
	display_engine->add_dynamic_mesh_object( skrzynia );
	movement_engine->add_moveable_object( skrzynia );

	*/

	//ustawienie aktywnej kamery
	CameraObject* camera = new CameraObject();
	XMVECTOR camera_pos = XMVectorSet( 0.0, 0.0, 0.0, 0.0 );
	camera->teleport( camera_pos );
	//przypisujemy kontroler ( dla kontroler�w trzeba zrobi� jaki� mechanizm przechowywania i zwalniania)
	camera_controller_PROTOTYPE* controller = new camera_controller_PROTOTYPE(
		ui_engine->get_standard_abstraction_layer( STANDARD_ABSTRACTION_LAYER::PROTOTYPE_BUTTONS ) );
	camera->set_controller(controller);

	//wstawiamy kamer� do odpowiednich modu��w
	display_engine->add_camera( camera );
	display_engine->set_current_camera( camera );
	movement_engine->add_moveable_object( camera );
	controllers_engine->add_pre_controlled( camera );

	double albedo[3] = { 0.8, 0.8, 0.8 };
	double turbidity = 4;
	XMVECTOR sun_dir = XMVectorSet( -0.2f, 0.6f, 0.6f, 1.0f );
	HosekSkyDome* sky_dome = new HosekSkyDome(models_manager);
	sky_dome->init_sky_dome( sun_dir, turbidity, albedo, 101, 101, 100, 5.0 );
	display_engine->set_skydome( sky_dome );

	sun_dir = XMVectorNegate( sun_dir );

	DirectX::XMFLOAT4 color( 0.8f, 0.8f, 0.8f, 1.0f );
	DirectX::XMFLOAT4 direction;
	XMStoreFloat4( &direction, sun_dir );

	// Ustawiamy �wiat�o pod indeksem 0
	display_engine->set_directional_light( direction, color, 0 );
	display_engine->set_ambient_light( DirectX::XMFLOAT4( 0.2f, 0.2f, 0.2f, 1.0f ) );



}

#endif

//=====================================================================================================================//
//								EngineInterface::Assets
//=====================================================================================================================//


/**@brief Pobiera z ModelsManager model o podanej nazwie.

@param[in] name Nazwa pliku z modelem.
@return Obiekt zawieraj�cy model lub nullptr w przypadku niepowodzenia.*/
Model3DFromFile* EngineInterface::Assets::GetModel( const std::wstring& name )
{
	std::lock_guard<SpinLock> guard( m_engine->m_engineAccess );

	return m_engine->models_manager->GetModel( name );
}


/**@brief Pobiera z ModelsManager model o podanej nazwie.

Tworzony jest VertexShader o domy�lnej nazwie funkcji g��wnej shadera zdefiniowanej
przez sta�� @ref DEFAULT_VERTEX_SHADER_ENTRY.

@param[in] name Nazwa pliku z shaderem.
@return Zwraca obiekt vertex shadera lub nullptr w przypadku niepowodzenia.
*/
VertexShaderObject* EngineInterface::Assets::GetVertexShader( const std::wstring& name )
{
	std::lock_guard<SpinLock> guard( m_engine->m_engineAccess );
	
	return m_engine->models_manager->AddVertexShader( name, DEFAULT_VERTEX_SHADER_ENTRY );
}
