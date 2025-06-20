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
        src/Core/GEngineCoreApplication.cpp
        src/Core/GEngineCoreApplication.h
        src/Modules/EntitiesModule.cpp
        src/Modules/EntitiesModule.h
        src/Entities/Entity.h
        src/Components/Component.cpp
        src/Components/Component.h
        src/Components/ComponentType.h
        src/Helpers/PointersList.h
        src/Helpers/PointerRef.h
        src/Components/TransformComponent.cpp
        src/Components/TransformComponent.h
        src/Extensions/UnorderedMapExtensions.h
        src/Events/EventBus.h
        src/Events/ModuleEvent.h
        src/Events/EntityDestroyedEvent.h
        src/Events/EventBuses.h
        src/Modules/GameModule.cpp
        src/Modules/GameModule.h
        src/Games/Game.h
        src/Modules/WindowModule.cpp
        src/Modules/WindowModule.h
        src/Modules/ComponentsModule.cpp
        src/Modules/ComponentsModule.h
        src/Modules/RenderingModule.cpp
        src/Modules/RenderingModule.h
        src/Rendering/LayeredRenderQueue.cpp
        src/Rendering/LayeredRenderQueue.h
        src/Extensions/MapExtensions.h
        src/Rendering/Renderer2d.cpp
        src/Rendering/Renderer2d.h
        src/Modules/SystemsModule.cpp
        src/Modules/SystemsModule.h
        src/Systems/System.h
        src/Components/Shape2dRendererComponent.cpp
        src/Components/Shape2dRendererComponent.h
        src/Systems/TickShapeRenderer2dComponentsSystem.cpp
        src/Systems/TickShapeRenderer2dComponentsSystem.h
        src/Entities/Entity.cpp
        src/Events/Event.h
        src/Components/ComponentFactory.h
        src/Rendering/ImGuiRenderer.cpp
        src/Rendering/ImGuiRenderer.h
        src/Modules/EditorModule.cpp
        src/Modules/EditorModule.h
        src/Editor/Windows/EditorWindow.cpp
        src/Editor/Windows/EditorWindow.h
        src/Rendering/SimpleRenderQueue.cpp
        src/Rendering/SimpleRenderQueue.h
        src/Editor/Windows/HierarchyEditorWindow.cpp
        src/Editor/Windows/HierarchyEditorWindow.h
        src/Editor/Windows/InspectorEditorWindow.cpp
        src/Editor/Windows/InspectorEditorWindow.h
        src/Objects/GEngineObject.h
        src/Objects/GEngineObjectType.h
        src/Editor/Inspector/GEngineObjectInspectorEditor.h
        src/Editor/Inspector/EntityInspectorEditor.cpp
        src/Editor/Inspector/EntityInspectorEditor.h
        src/Editor/Extensions/ImGuiExtensions.cpp
        src/Editor/Extensions/ImGuiExtensions.h
        src/Editor/ComponentsInspector/ComponentInspectorEditor.h
        src/Editor/ComponentsInspector/TransformComponentInspectorEditor.cpp
        src/Editor/ComponentsInspector/TransformComponentInspectorEditor.h
        src/Components/Texture2dRendererComponent.cpp
        src/Components/Texture2dRendererComponent.h
        src/Modules/ResourcesModule.cpp
        src/Modules/ResourcesModule.h
        src/Resources/Resource.h
        src/Resources/ResourceType.h
        src/Resources/Resource.cpp
        src/ResourceImporters/ResourceImporter.cpp
        src/ResourceImporters/ResourceImporter.h
        src/ResourceImporters/TextureResourceImporter.cpp
        src/ResourceImporters/TextureResourceImporter.h
        src/Resources/TextureResource.cpp
        src/Resources/TextureResource.h
        src/Extensions/StringExtensions.h
        src/Editor/Windows/ResourcesEditorWindow.cpp
        src/Editor/Windows/ResourcesEditorWindow.h
        src/Extensions/RayLibExtensions.cpp
        src/Extensions/RayLibExtensions.h
        src/Modules/InputModule.cpp
        src/Modules/InputModule.h
        src/Modules/CameraModule.cpp
        src/Modules/CameraModule.h
        src/Cameras/Camera.cpp
        src/Cameras/Camera.h
        src/Constants/MathConstants.h
        src/Editor/MenuBar/MenuBarEditor.cpp
        src/Editor/MenuBar/MenuBarEditor.h
        src/Components/CameraComponent.cpp
        src/Components/CameraComponent.h
        src/Editor/Inspector/ResourcesInspectorEditor.cpp
        src/Editor/Inspector/ResourcesInspectorEditor.h
        src/Editor/ResourcesInspector/ResourceInspectorEditor.h
        src/Editor/ResourcesInspector/TextureResourceInspectorEditor.cpp
        src/Editor/ResourcesInspector/TextureResourceInspectorEditor.h
        src/Resources/TiledMapResource.cpp
        src/Resources/TiledMapResource.h
        src/ResourceImporters/TiledMapImporter.cpp
        src/ResourceImporters/TiledMapImporter.h
        src/Editor/ResourcesInspector/TiledMapResourceInspectorEditor.cpp
        src/Editor/ResourcesInspector/TiledMapResourceInspectorEditor.h
        src/Components/TiledMap2dRendererComponent.cpp
        src/Components/TiledMap2dRendererComponent.h
        src/Extensions/MathExtensions.h
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

target_include_directories(GEngineCore PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
