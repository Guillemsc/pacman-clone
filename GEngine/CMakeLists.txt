cmake_minimum_required(VERSION 3.31)
project(GEngineCore)

set(CMAKE_CXX_STANDARD 20)

if (MSVC)
    add_compile_options(/utf-8)
endif()

# Add raylib
add_subdirectory(vendor/raylib)

target_compile_definitions(raylib PUBLIC RAYLIB_NO_WINDOWS_FUNCTIONS)

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
        src/GEngine/Events/Event.h
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
        src/GEngine/Modules/TickablesModule.cpp
        src/GEngine/Modules/TickablesModule.h
        src/GEngine/Tickables/Tickable.h
        src/GEngine/Components/Shape2dRendererComponent.cpp
        src/GEngine/Components/Shape2dRendererComponent.h
        src/GEngine/Entities/Entity.cpp
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
        src/GEngine/Timers/Timer.cpp
        src/GEngine/Timers/Timer.h
        src/GEngine/Timers/ITimeSource.h
        src/GEngine/Timers/ChronoTimeSource.cpp
        src/GEngine/Timers/ChronoTimeSource.h
        src/GEngine/Timers/ChronoTimer.cpp
        src/GEngine/Timers/ChronoTimer.h
        src/GEngine/Data/CellPosition.h
        src/GEngine/SerializedProperties/Property.h
        src/GEngine/SerializedProperties/PropertiesContainer.h
        src/GEngine/Extensions/Vec3Extensions.h
        src/GEngine/Editor/PropertyDrawers/PropertyDrawerEditor.h
        src/GEngine/Editor/PropertyDrawers/Vec3PropertyDrawerEditor.cpp
        src/GEngine/Editor/PropertyDrawers/Vec3PropertyDrawerEditor.h
        src/GEngine/Directions/CardinalDirection.h
        src/GEngine/Extensions/CardinalDirectionExtensions.h
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
        src/GEngine/Examples/UiTransform/AnchorsUiTransformExample.cpp
        src/GEngine/Examples/UiTransform/AnchorsUiTransformExample.h
        src/GEngine/Modules/ExamplesModule.cpp
        src/GEngine/Modules/ExamplesModule.h
        src/GEngine/Data/ExampleData.h
        src/GEngine/Editor/Windows/ExamplesEditorWindow.cpp
        src/GEngine/Editor/Windows/ExamplesEditorWindow.h
        src/GEngine/UiShapes2d/UiShape2d.h
        src/GEngine/UiShapes2d/RectUiShape2d.cpp
        src/GEngine/UiShapes2d/RectUiShape2d.h
        src/GEngine/Editor/PropertyDrawers/Color01PropertyDrawerEditor.cpp
        src/GEngine/Editor/PropertyDrawers/Color01PropertyDrawerEditor.h
        src/GEngine/Modules/TimeModule.cpp
        src/GEngine/Modules/TimeModule.h
        src/GEngine/Editor/Windows/DemoEditorWindow.cpp
        src/GEngine/Editor/Windows/DemoEditorWindow.h
        src/GEngine/Editor/Windows/UiEditorWindow.cpp
        src/GEngine/Editor/Windows/UiEditorWindow.h
        src/GEngine/Resources/JsonResource.cpp
        src/GEngine/Resources/JsonResource.h
        src/GEngine/ResourceImporters/JsonResourceImporter.cpp
        src/GEngine/ResourceImporters/JsonResourceImporter.h
        src/GEngine/Data/JsonData.cpp
        src/GEngine/Data/JsonData.h
        src/GEngine/Resources/FontResource.cpp
        src/GEngine/Resources/FontResource.h
        src/GEngine/ResourceImporters/FontResourceImporter.cpp
        src/GEngine/ResourceImporters/FontResourceImporter.h
        src/GEngine/Editor/ResourcesInspector/JsonResourceInspectorEditor.cpp
        src/GEngine/Editor/ResourcesInspector/JsonResourceInspectorEditor.h
        src/GEngine/Editor/ResourcesInspector/FontResourceInspectorEditor.cpp
        src/GEngine/Editor/ResourcesInspector/FontResourceInspectorEditor.h
        src/GEngine/Components/UiTextRendererComponent.cpp
        src/GEngine/Components/UiTextRendererComponent.h
        src/GEngine/Coroutines/Coroutines.h
        src/GEngine/Coroutines/Coroutines.cpp
        src/GEngine/Tweens/Tween.cpp
        src/GEngine/Tweens/Tween.h
        src/GEngine/Tweens/ChildrenTweenSequenceMode.h
        src/GEngine/Tweens/InterpolationTween.h
        src/GEngine/Examples/Tweens/DevelopmentTweensExample.cpp
        src/GEngine/Examples/Tweens/DevelopmentTweensExample.h
        src/GEngine/Tweens/Easing.cpp
        src/GEngine/Tweens/Easing.h
        src/GEngine/Tweens/EasingType.h
        src/GEngine/Tweens/CallbackTween.cpp
        src/GEngine/Tweens/CallbackTween.h
        src/GEngine/Scenes/Scene.cpp
        src/GEngine/Scenes/Scene.h
        src/GEngine/Core/GEngineCoreModules.h
        src/GEngine/Modules/TweensModule.cpp
        src/GEngine/Modules/TweensModule.h
        src/GEngine/Cameras/Camera2d.cpp
        src/GEngine/Cameras/Camera2d.h
        src/GEngine/Components/Camera2dComponent.cpp
        src/GEngine/Components/Camera2dComponent.h
        src/GEngine/Hashes/Vec2IntHash.h
        src/GEngine/Raylib/RaylibWrapper.h
        src/GEngine/Resources/SpriteResource.cpp
        src/GEngine/Resources/SpriteResource.h
        src/GEngine/ResourceImporters/SpriteResourceImporter.cpp
        src/GEngine/ResourceImporters/SpriteResourceImporter.h
        src/GEngine/Editor/ResourcesInspector/SpriteResourceInspectorEditor.cpp
        src/GEngine/Editor/ResourcesInspector/SpriteResourceInspectorEditor.h
        src/GEngine/Components/Sprite2dRendererComponent.cpp
        src/GEngine/Components/Sprite2dRendererComponent.h
        src/GEngine/Components/Sprite2dAnimatorComponent.cpp
        src/GEngine/Components/Sprite2dAnimatorComponent.h
        src/GEngine/Sprite2dAnimator/Sprite2dAnimation.cpp
        src/GEngine/Sprite2dAnimator/Sprite2dAnimation.h
        src/GEngine/Rendering/Guizmo2dRenderer.cpp
        src/GEngine/Rendering/Guizmo2dRenderer.h
        src/GEngine/ComponentsRegister/ComponentsRegister.cpp
        src/GEngine/ComponentsRegister/ComponentsRegister.h
        src/GEngine/Modules/GuizmosModule.cpp
        src/GEngine/Modules/GuizmosModule.h
        src/GEngine/Editor/Windows/GuizmosEditorWindow.cpp
        src/GEngine/Editor/Windows/GuizmosEditorWindow.h
        src/GEngine/Modules/Collisions2dModule.cpp
        src/GEngine/Modules/Collisions2dModule.h
        src/GEngine/Colliders2d/Collider2d.cpp
        src/GEngine/Colliders2d/Collider2d.h
        src/GEngine/Obbs/Obb2d.cpp
        src/GEngine/Obbs/Obb2d.h
        src/GEngine/Components/Collider2dComponent.cpp
        src/GEngine/Components/Collider2dComponent.h
        src/GEngine/Colliders2d/Contact2dData.h
        src/GEngine/Editor/Windows/Collisions2dEditorWindow.cpp
        src/GEngine/Editor/Windows/Collisions2dEditorWindow.h
        src/GEngine/Modules/CoroutinesModule.cpp
        src/GEngine/Modules/CoroutinesModule.h
        src/GEngine/Coroutines/CoroutinesRunner.cpp
        src/GEngine/Coroutines/CoroutinesRunner.h
        src/GEngine/Editor/PropertyDrawers/BoolPropertyDrawerEditor.cpp
        src/GEngine/Editor/PropertyDrawers/BoolPropertyDrawerEditor.h
        src/GEngine/Modules/ConfigurationModule.cpp
        src/GEngine/Modules/ConfigurationModule.h
        src/GEngine/Modules/Module.h
        src/GEngine/Coroutines/CancellationToken.cpp
        src/GEngine/Coroutines/CancellationToken.h
)

# Link raylib
target_link_libraries(GEngineCore PUBLIC raylib)

# Link rlImGui
target_link_libraries(GEngineCore PUBLIC rlImGui)

# Link imgui
target_link_libraries(GEngineCore PUBLIC imgui)

# Link gml
target_link_libraries(GEngineCore PUBLIC glm::glm-header-only)

# Link tmxlite
target_link_libraries(GEngineCore PUBLIC tmxlite)

# Include spdlog
target_include_directories(GEngineCore PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/vendor/")

# Include json
target_include_directories(GEngineCore PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/vendor/json/")

# Include tokoro
target_include_directories(GEngineCore PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/vendor/tokoro")

# Include our source
target_include_directories(GEngineCore PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/")
