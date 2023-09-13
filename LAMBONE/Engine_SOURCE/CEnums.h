#pragma once

namespace yha::enums
{
	enum class eComponentType
	{
		None,
		Transform,
		Mesh,
		Collider2D,
		Particle,
		MeshRenderer,
		Animator,
		Script,
		Light,
		Camera,
		AudioListener,
		AudioSource,
		End,
	};

	enum class eSceneType
	{
		Intro,
		Loading,
		MainMenu,
		Ending,

		GrassDay,
		GrassNight,
		PoolDay,
		PoolNight,
		//RoofDay,
		//RoofNight,
		End
	};

	enum class eLayerType
	{
		BG,
		Grid,
		Camera,
		Player,
		//PlayerNearbyAttack,
		//PlayerFarAttack,
		Monster,
		SunLight,
		SunLightNatural,
		Light,
		UI,
		UI2,
		End = 16,
	};

	enum class eResourceType
	{
		Texture,
		Shader,
		Material,
		Mesh,
		Animation,
		ComputeShader,
		AudioClip,
		End,
	};

	enum class eColliderType
	{
		Rect,
		Circle,
		Sphere,
		Cube,
		End,
	};

	enum class eLightType
	{
		Directional,
		Point,
		Spot,
		End,
	};

	enum class eColor
	{
		Red,
		Green,
		Blue,
		End,
	};

	enum class eColliderStateType
	{
		Start,
		Ing,
		Fin,
		End,
	};

	enum class eStatusType
	{
		Idle,
		Attack,
		Attacked,
		Dead,
		Bright_OnlySunflower,
		End,
	};

	enum class eAttackType
	{
		None,
		Nearby,
		Far,
		End,
	};

	enum class eDirection
	{
		Right,
		Left,
		End,
	};

	enum class ePlantsType
	{
		SunFlower,
		PeaShooter,
		WallNut,
		Chomper,
		Jalapeno,
		CherryBomb,
		End,
	};

	enum class eZombiesType
	{
		Normal,
		End,
	};

	enum class eStepMode
	{
		Choose,
		Play,
		End,
	};

}