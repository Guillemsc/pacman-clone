//
// Created by guillem on 6/15/25.
//

#ifndef CAMERAMODULE_H
#define CAMERAMODULE_H

#include <memory>
#include <vector>

#include "GEngine/Core/GEngineCoreModules.h"
#include "GEngine/Extensions/Vec2Extensions.h"
#include "glm/vec2.hpp"

namespace GEngine
{
    class Camera2d;
    class Camera;
}

namespace GEngine
{
    // Manages 2d and 3d cameras.
    // Handles camera stacking, and the editor camera.
    class CameraModule
    {
    public:
        CameraModule();

        void Init(GEngineCoreModules* modules);
        void Tick(float deltaTime);

        bool IsUsing2dMode() const;

        std::weak_ptr<Camera> CreateCamera();
        void RemoveCamera(const std::weak_ptr<Camera>& removing);

        std::weak_ptr<Camera2d> CreateCamera2d();
        void RemoveCamera2d(const std::weak_ptr<Camera2d>& removing);

        std::weak_ptr<Camera> GetCurrentCamera();
        std::weak_ptr<Camera> GetCurrentRenderingCamera();

        std::weak_ptr<Camera2d> GetCurrentCamera2d();
        std::weak_ptr<Camera2d> GetCurrentRenderingCamera2d();

        bool GetIsUsingEditorCamera() const;
        void SetIsUsingEditorCamera(bool value);

    private:
        void TickEditorCamera(float deltaTime);

    private:
        GEngineCoreModules* _modules = nullptr;

        bool _isUsing2dMode = true;

        std::vector<std::shared_ptr<Camera>> _cameras;
        std::shared_ptr<Camera> _editorCamera;

        std::vector<std::shared_ptr<Camera2d>> _cameras2d;
        std::shared_ptr<Camera2d> _editorCamera2d;

        std::weak_ptr<Camera> _currentCamera;

        std::weak_ptr<Camera2d> _currentCamera2d;

        bool _isUsingEditorCamera = false;
        glm::vec2 _lastMousePos = Vec2Extensions::Zero;
    };
}

#endif //CAMERAMODULE_H
