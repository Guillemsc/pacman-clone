//
// Created by guillem on 11/21/25.
//

#ifndef GENGINECOREMODULES_H
#define GENGINECOREMODULES_H

namespace GEngine
{
	class ConfigurationModule;
	class GuizmosModule;
	class ExamplesModule;
	class EditorModule;
	class CoroutinesModule;
	class UiModule;
	class InputModule;
	class TickablesModule;
	class TimeModule;
	class ResourcesModule;
	class RenderingModule;
	class WindowModule;
	class CameraModule;
	class GameModule;
	class EntitiesModule;
	class TweensModule;
	class Collisions2dModule;

	// All core modules provided by GEngine.
	class GEngineCoreModules
	{
	public:
		explicit GEngineCoreModules(
			ConfigurationModule* configuration,
			EntitiesModule* entities,
			GameModule* game,
			CameraModule* camera,
			WindowModule* window,
			RenderingModule* rendering,
			ResourcesModule* resources,
			TimeModule* time,
			TickablesModule* systems,
			InputModule* input,
			UiModule* ui,
			CoroutinesModule* coroutines,
			EditorModule* editor,
			ExamplesModule* examples,
			TweensModule* tweens,
			GuizmosModule* guizmos,
			Collisions2dModule* collisions2d
			) : configuration(configuration),
			entities(entities),
			game(game),
			camera(camera),
			window(window),
			rendering(rendering),
			resources(resources),
			time(time),
			tickables(systems),
			input(input),
			ui(ui),
			coroutines(coroutines),
			editor(editor),
			examples(examples),
			tweens(tweens),
			guizmos(guizmos),
			collisions2d(collisions2d)
		{}

	public:
		ConfigurationModule* const configuration;
		EntitiesModule* const entities;
		GameModule* const game;
		CameraModule* const camera;
		WindowModule* const window;
		RenderingModule* const rendering;
		ResourcesModule* const resources;
		TimeModule* const time;
		TickablesModule* const tickables;
		InputModule* const input;
		UiModule* const ui;
		CoroutinesModule* const coroutines;
		EditorModule* const editor;
		ExamplesModule* const examples;
		TweensModule* const tweens;
		GuizmosModule* const guizmos;
		Collisions2dModule* const collisions2d;
	};

} // GEngine

#endif //GENGINECOREMODULES_H
