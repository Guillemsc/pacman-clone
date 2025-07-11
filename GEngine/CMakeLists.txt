cmake_minimum_required(VERSION 3.31)
project(GEngineCore)

set(CMAKE_CXX_STANDARD 20)

# Add raylib
add_subdirectory(vendor/raylib)

# Add rlImGui
add_subdirectory(vendor/rlImGui)

# Add imgui
add_subdirectory(vendor/imgui)

# Add gml
add_subdirectory(vendor/glm)

# Add tmxlite
add_subdirectory(vendor/tmxlite)

# Add ourselves
add_library(GEngineCore STATIC
        src/GEngine/Core/GEngineCoreApplication.cpp
        src/GEngine/Core/GEngineCoreApplication.h
        src/GEngine/Modules/EntitiesModule.cpp
        src/GEngine/Modules/EntitiesModule.h
        src/GEngine/Entities/Entity.h
        src/GEngine/Components/Component.cpp
        src/GEngine/Components/Component.h
        src/GEngine/Components/TransformComponent.cpp
        src/GEngine/Components/TransformComponent.h
        src/GEngine/Extensions/UnorderedMapExtensions.h
        src/GEngine/Events/EventBus.h
        src/GEngine/Events/ModuleEvent.h
        src/GEngine/Events/EntityDestroyedEvent.h
        src/GEngine/Events/EventBuses.h
        src/GEngine/Modules/GameModule.cpp
        src/GEngine/Modules/GameModule.h
        src/GEngine/Games/Game.h
        src/GEngine/Modules/WindowModule.cpp
        src/GEngine/Modules/WindowModule.h
        src/GEngine/Modules/RenderingModule.cpp
        src/GEngine/Modules/RenderingModule.h
        src/GEngine/Rendering/LayeredRenderQueue.cpp
        src/GEngine/Rendering/LayeredRenderQueue.h
        src/GEngine/Extensions/MapExtensions.h
        src/GEngine/Rendering/Renderer2d.cpp
        src/GEngine/Rendering/Renderer2d.h
        src/GEngine/Modules/SystemsModule.cpp
        src/GEngine/Modules/SystemsModule.h
        src/GEngine/Systems/System.h
        src/GEngine/Components/Shape2dRendererComponent.cpp
        src/GEngine/Components/Shape2dRendererComponent.h
        src/GEngine/Systems/TickShapeRenderer2dComponentsSystem.cpp
        src/GEngine/Systems/TickShapeRenderer2dComponentsSystem.h
        src/GEngine/Entities/Entity.cpp
        src/GEngine/Events/Event.h
        src/GEngine/Rendering/ImGuiRenderer.cpp
        src/GEngine/Rendering/ImGuiRenderer.h
        src/GEngine/Modules/EditorModule.cpp
        src/GEngine/Modules/EditorModule.h
        src/GEngine/Editor/Windows/EditorWindow.cpp
        src/GEngine/Editor/Windows/EditorWindow.h
        src/GEngine/Rendering/SimpleRenderQueue.cpp
        src/GEngine/Rendering/SimpleRenderQueue.h
        src/GEngine/Editor/Windows/HierarchyEditorWindow.cpp
        src/GEngine/Editor/Windows/HierarchyEditorWindow.h
        src/GEngine/Editor/Windows/InspectorEditorWindow.cpp
        src/GEngine/Editor/Windows/InspectorEditorWindow.h
        src/GEngine/Objects/GEngineObject.h
        src/GEngine/Objects/GEngineObjectType.h
        src/GEngine/Editor/Inspector/GEngineObjectInspectorEditor.h
        src/GEngine/Editor/Inspector/EntityInspectorEditor.cpp
        src/GEngine/Editor/Inspector/EntityInspectorEditor.h
        src/GEngine/Editor/Extensions/ImGuiExtensions.cpp
        src/GEngine/Editor/Extensions/ImGuiExtensions.h
        src/GEngine/Editor/ComponentsInspector/ComponentInspectorEditor.h
        src/GEngine/Editor/ComponentsInspector/TransformComponentInspectorEditor.cpp
        src/GEngine/Editor/ComponentsInspector/TransformComponentInspectorEditor.h
        src/GEngine/Components/Texture2dRendererComponent.cpp
        src/GEngine/Components/Texture2dRendererComponent.h
        src/GEngine/Modules/ResourcesModule.cpp
        src/GEngine/Modules/ResourcesModule.h
        src/GEngine/Resources/Resource.h
        src/GEngine/Resources/ResourceType.h
        src/GEngine/Resources/Resource.cpp
        src/GEngine/ResourceImporters/ResourceImporter.cpp
        src/GEngine/ResourceImporters/ResourceImporter.h
        src/GEngine/ResourceImporters/TextureResourceImporter.cpp
        src/GEngine/ResourceImporters/TextureResourceImporter.h
        src/GEngine/Resources/TextureResource.cpp
        src/GEngine/Resources/TextureResource.h
        src/GEngine/Extensions/StringExtensions.h
        src/GEngine/Editor/Windows/ResourcesEditorWindow.cpp
        src/GEngine/Editor/Windows/ResourcesEditorWindow.h
        src/GEngine/Extensions/RayLibExtensions.cpp
        src/GEngine/Extensions/RayLibExtensions.h
        src/GEngine/Modules/InputModule.cpp
        src/GEngine/Modules/InputModule.h
        src/GEngine/Modules/CameraModule.cpp
        src/GEngine/Modules/CameraModule.h
        src/GEngine/Cameras/Camera.cpp
        src/GEngine/Cameras/Camera.h
        src/GEngine/Constants/MathConstants.h
        src/GEngine/Editor/MenuBar/MenuBarEditor.cpp
        src/GEngine/Editor/MenuBar/MenuBarEditor.h
        src/GEngine/Components/CameraComponent.cpp
        src/GEngine/Components/CameraComponent.h
        src/GEngine/Editor/Inspector/ResourcesInspectorEditor.cpp
        src/GEngine/Editor/Inspector/ResourcesInspectorEditor.h
        src/GEngine/Editor/ResourcesInspector/ResourceInspectorEditor.h
        src/GEngine/Editor/ResourcesInspector/TextureResourceInspectorEditor.cpp
        src/GEngine/Editor/ResourcesInspector/TextureResourceInspectorEditor.h
        src/GEngine/Resources/TiledMapResource.cpp
        src/GEngine/Resources/TiledMapResource.h
        src/GEngine/ResourceImporters/TiledMapResourceImporter.cpp
        src/GEngine/ResourceImporters/TiledMapResourceImporter.h
        src/GEngine/Editor/ResourcesInspector/TiledMapResourceInspectorEditor.cpp
        src/GEngine/Editor/ResourcesInspector/TiledMapResourceInspectorEditor.h
        src/GEngine/Components/TiledMap2dRendererComponent.cpp
        src/GEngine/Components/TiledMap2dRendererComponent.h
        src/GEngine/Extensions/MathExtensions.h
        src/GEngine/Editor/ComponentsInspector/TiledMap2dRendererComponentInspectorEditor.cpp
        src/GEngine/Editor/ComponentsInspector/TiledMap2dRendererComponentInspectorEditor.h
        src/GEngine/Editor/Extensions/EditorExtensions.cpp
        src/GEngine/Editor/Extensions/EditorExtensions.h
        src/GEngine/Extensions/Vec2Extensions.h
        src/GEngine/Data/TiledLayerData.h
        src/GEngine/Data/TiledLayerData.cpp
        src/GEngine/Coroutines/Coroutine.h
        src/GEngine/Coroutines/NestedCoroutine.cpp
        src/GEngine/Coroutines/NestedCoroutine.h
        src/GEngine/Coroutines/CoroutineRunner.cpp
        src/GEngine/Coroutines/CoroutineRunner.h
        src/GEngine/Coroutines/WaitFramesCoroutine.cpp
        src/GEngine/Coroutines/WaitFramesCoroutine.h
        src/GEngine/Timers/Timer.cpp
        src/GEngine/Timers/Timer.h
        src/GEngine/Timers/ITimeSource.h
        src/GEngine/Timers/ChronoTimeSource.cpp
        src/GEngine/Timers/ChronoTimeSource.h
        src/GEngine/Timers/ChronoTimer.cpp
        src/GEngine/Timers/ChronoTimer.h
        src/GEngine/Coroutines/WaitSecondsCoroutine.cpp
        src/GEngine/Coroutines/WaitSecondsCoroutine.h
        src/GEngine/Coroutines/CoroutineBuilder.cpp
        src/GEngine/Coroutines/CoroutineBuilder.h
        src/GEngine/Coroutines/CallbackCoroutine.cpp
        src/GEngine/Coroutines/CallbackCoroutine.h
        src/GEngine/Coroutines/CoroutineTask.cpp
        src/GEngine/Coroutines/CoroutineTask.h
        src/GEngine/Coroutines/TimeSlicedCoroutine.cpp
        src/GEngine/Coroutines/TimeSlicedCoroutine.h
        src/GEngine/Data/CellPosition.h
        src/GEngine/SerializedProperties/Property.h
        src/GEngine/SerializedProperties/PropertiesContainer.h
        src/GEngine/Extensions/Vec3Extensions.h
        src/GEngine/Editor/PropertyDrawers/PropertyDrawerEditor.h
        src/GEngine/Editor/PropertyDrawers/Vec3PropertyDrawerEditor.cpp
        src/GEngine/Editor/PropertyDrawers/Vec3PropertyDrawerEditor.h
        src/GEngine/Directions/CardinalDirection.h
        src/GEngine/Extensions/CardinalDirectionExtensions.h
        src/GEngine/Coroutines/Coroutine.cpp
        src/GEngine/Modules/CoroutinesModule.cpp
        src/GEngine/Modules/CoroutinesModule.h
        src/GEngine/ServiceLocators/ServiceLocator.h
        src/GEngine/Shapes2d/Shape2d.h
        src/GEngine/Shapes2d/RectShape2d.cpp
        src/GEngine/Shapes2d/RectShape2d.h
        src/GEngine/Editor/PropertyDrawers/IntPropertyDrawerEditor.cpp
        src/GEngine/Editor/PropertyDrawers/IntPropertyDrawerEditor.h
        src/GEngine/Editor/PropertyDrawers/Vec2PropertyDrawerEditor.cpp
        src/GEngine/Editor/PropertyDrawers/Vec2PropertyDrawerEditor.h
        src/GEngine/Components/UiTransformComponent.cpp
        src/GEngine/Components/UiTransformComponent.h
        src/GEngine/Components/UiShapeRendererComponent.cpp
        src/GEngine/Components/UiShapeRendererComponent.h
        src/GEngine/Rendering/UiRenderer.cpp
        src/GEngine/Rendering/UiRenderer.h
        src/GEngine/Extensions/Vec4Extensions.h
        src/GEngine/Colors/Color01.cpp
        src/GEngine/Colors/Color01.h
        src/GEngine/Extensions/Color01Extensions.h
        src/GEngine/UiRaycasting/UiRaycastTarget.h
        src/GEngine/Modules/UiModule.cpp
        src/GEngine/Modules/UiModule.h
        src/GEngine/Components/UiShapeButtonComponent.cpp
        src/GEngine/Components/UiShapeButtonComponent.h
        src/GEngine/UiRaycasting/UiRaycastTargetState.h
        src/GEngine/Editor/PropertyDrawers/FloatPropertyDrawerEditor.cpp
        src/GEngine/Editor/PropertyDrawers/FloatPropertyDrawerEditor.h
        src/GEngine/Editor/PropertyDrawers/Vec4PropertyDrawerEditor.cpp
        src/GEngine/Editor/PropertyDrawers/Vec4PropertyDrawerEditor.h
        src/GEngine/Data/UiRect.cpp
        src/GEngine/Data/UiRect.h
        src/GEngine/Rendering/GuizmoUiRenderer.cpp
        src/GEngine/Rendering/GuizmoUiRenderer.h
        src/GEngine/Data/CornersRect.cpp
        src/GEngine/Data/CornersRect.h
)

# Link raylib
target_link_libraries(GEngineCore PUBLIC raylib)

# Link rlImGui
target_link_libraries(GEngineCore PUBLIC rlImGui)

# Link imgui
target_link_libraries(GEngineCore PUBLIC imgui)

# Link gml
target_link_libraries(GEngineCore PUBLIC glm::glm-header-only)

# Link imgui
target_link_libraries(GEngineCore PUBLIC tmxlite)

# Include spdlog
target_include_directories(GEngineCore PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/vendor/")

target_include_directories(GEngineCore PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/")
