//
// Created by guillem on 6/15/25.
//

#ifndef CAMERAMODULE_H
#define CAMERAMODULE_H
#include <memory>
#include <vector>

#include "glm/vec2.hpp"

namespace GEngineCore
{
    class Camera;
}

namespace GEngineCore
{
    class CameraModule
    {
    public:
        CameraModule();

        void Tick(float deltaTime);

        std::weak_ptr<Camera> CreateCamera();
        void RemoveCamera(const std::weak_ptr<Camera>& cameraPtr);

        std::weak_ptr<Camera> GetCurrentCamera();
        std::weak_ptr<Camera> GetCurrentRenderingCamera();

        bool GetIsUsingEditorCamera() const;
        void SetIsUsingEditorCamera(bool value);

    private:
        void TickEditorCamera(float deltaTime);

    private:
        std::vector<std::shared_ptr<Camera>> _cameras;
        std::shared_ptr<Camera> _editorCamera;

        std::weak_ptr<Camera> _currentCamera;
        std::weak_ptr<Camera> _currentRenderingCamera;

        bool _isUsingEditorCamera;
        glm::vec2 _lastMousePos;
    };
}

#endif //CAMERAMODULE_H
