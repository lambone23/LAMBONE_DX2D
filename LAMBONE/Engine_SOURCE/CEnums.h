#pragma once

namespace yha::enums
{
	enum class eComponentType
	{
		None,
		Transform,
		Mesh,
		Particle,
		MeshRenderer,
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
		Player,
		Monster,
		UI,
		End,
	};

	enum class eResourceType
	{
		Texture,
		Shader,
		Material,
		Mesh,
		End,
	};
}