//
// Created by guillem on 11/21/25.
//

#ifndef GENGINECOREMODULES_H
#define GENGINECOREMODULES_H

namespace GEngine
{
	class ExamplesModule;
	class EditorModule;
	class CoroutinesModule;
	class UiModule;
	class InputModule;
	class SystemsModule;
	class TimeModule;
	class ResourcesModule;
	class RenderingModule;
	class WindowModule;
	class CameraModule;
	class GameModule;
	class EntitiesModule;
	class TweensModule;

	class GEngineCoreModules
	{
	public:
		explicit GEngineCoreModules(
			EntitiesModule* entities,
			GameModule* game,
			CameraModule* camera,
			WindowModule* window,
			RenderingModule* rendering,
			ResourcesModule* resources,
			TimeModule* time,
			SystemsModule* systems,
			InputModule* input,
			UiModule* ui,
			CoroutinesModule* coroutines,
			EditorModule* editor,
			ExamplesModule* examples,
			TweensModule* tweens
			) : entities(entities),
				game(game),
				camera(camera),
				window(window),
				rendering(rendering),
				resources(resources),
				time(time),
				systems(systems),
				input(input),
				ui(ui),
				coroutines(coroutines),
				editor(editor),
				examples(examples),
				tweens(tweens)
		{}

	public:
		EntitiesModule* const entities;
		GameModule* const game;
		CameraModule* const camera;
		WindowModule* const window;
		RenderingModule* const rendering;
		ResourcesModule* const resources;
		TimeModule* const time;
		SystemsModule* const systems;
		InputModule* const input;
		UiModule* const ui;
		CoroutinesModule* const coroutines;
		EditorModule* const editor;
		ExamplesModule* const examples;
		TweensModule* const tweens;
	};

} // GEngine

#endif //GENGINECOREMODULES_H
