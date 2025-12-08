//
// Created by guillem on 6/18/25.
//

#ifndef RESOURCEINSPECTOREDITOR_H
#define RESOURCEINSPECTOREDITOR_H

#include <memory>

namespace GEngine
{
	class Resource;
	class GEngineCoreModules;

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
		explicit ResourceInspectorEditor(GEngineCoreModules* modules);

		void Draw(const std::shared_ptr<Resource>& inspect) override;

	protected:
		virtual void DrawSpecific(const std::shared_ptr<T>& inspect) = 0;

	protected:
		GEngineCoreModules* const _modules;
	};

	// -------------------------------------------------------
	// -------------------------------------------------------

	template<class T>
	ResourceInspectorEditor<T>::ResourceInspectorEditor(GEngineCoreModules* modules)
		: _modules(modules)
	{

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
