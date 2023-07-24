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
		Camera,
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
		Player,
		Monster,
		UI,
		End = 16,
	};

	enum class eResourceType
	{
		Texture,
		Shader,
		Material,
		Mesh,
		Animation,
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

	enum class eColor
	{
		Red,
		Green,
		Blue,
		End,
	};

	enum class eColliderStateType
	{
		None,
		Start,
		Ing,
		Fin,
		End,
	};
}