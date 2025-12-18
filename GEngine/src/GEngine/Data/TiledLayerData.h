//
// Created by guillem on 6/26/25.
//

#ifndef TILEDLAYERDATA_H
#define TILEDLAYERDATA_H
#include <memory>

namespace GEngine
{
	class TextureResource;

	struct TiledLayerData
	{
		static const TiledLayerData Default;

		bool Visible = true;
		std::int32_t RenderLayerOffset = 0;
	};
}

#endif //TILEDLAYERDATA_H
