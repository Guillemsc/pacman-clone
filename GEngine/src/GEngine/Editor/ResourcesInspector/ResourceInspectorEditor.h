//
// Created by guillem on 6/18/25.
//

#ifndef RESOURCEINSPECTOREDITOR_H
#define RESOURCEINSPECTOREDITOR_H

#include <memory>

namespace GEngine
{
	class Resource;
	class GEngineCoreApplication;

	class IResourceInspectorEditor
	{
	public:
		virtual ~IResourceInspectorEditor() = default;

		virtual void Draw(const std::shared_ptr<Resource>& inspect) = 0;
	};

	// -------------------------------------------------------
	// -------------------------------------------------------

	template <class T>
	class ResourceInspectorEditor : public IResourceInspectorEditor
	{
	public:
		explicit ResourceInspectorEditor(const std::weak_ptr<GEngineCoreApplication>& app);

		void Draw(const std::shared_ptr<Resource>& inspect) override;

	protected:
		virtual void DrawSpecific(const std::shared_ptr<T>& inspect) = 0;

	protected:
		std::weak_ptr<GEngineCoreApplication> _app;
	};

	// -------------------------------------------------------
	// -------------------------------------------------------

	template<class T>
	ResourceInspectorEditor<T>::ResourceInspectorEditor(const std::weak_ptr<GEngineCoreApplication> &app)
	{
		_app = app;
	}

	template<class T>
	void ResourceInspectorEditor<T>::Draw(const std::shared_ptr<Resource> &inspect)
	{
		std::shared_ptr<T> derived = std::dynamic_pointer_cast<T>(inspect);
		if (!derived) return;

		DrawSpecific(derived);
	}
}

#endif //RESOURCEINSPECTOREDITOR_H
