//
// Created by guillem on 12/4/25.
//

#ifndef PELLETSLOADINGMANAGER_H
#define PELLETSLOADINGMANAGER_H

namespace GEngine
{
	class GEngineCoreModules;
	class Scene;
}

namespace PacMan
{
	struct LoadedMapData;
	class MapMovementManager;

	class PelletsLoadingManager
	{
	public:
		PelletsLoadingManager(
			GEngine::GEngineCoreModules* modules,
			GEngine::Scene* scene,
			MapMovementManager* mapMovementManager
		);

		void LoadPellets(const LoadedMapData& loadedMapData);

	private:
		GEngine::GEngineCoreModules* const _modules;
		GEngine::Scene* const _scene;
		MapMovementManager* const _mapMovementManager;
	};
}

#endif //PELLETSLOADINGMANAGER_H
