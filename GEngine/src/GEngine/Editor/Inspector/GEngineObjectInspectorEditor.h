//
// Created by guillem on 6/9/25.
//

#ifndef INSPECTORGENGINEOBJECTFACTORY_H
#define INSPECTORGENGINEOBJECTFACTORY_H

#include <memory>

namespace GEngine
{
	class GEngineCoreModules;
	class GEngineCoreApplication;
	class GEngineObject;

	class IGEngineObjectInspectorEditor
	{
	public:
		virtual ~IGEngineObjectInspectorEditor() = default;

		virtual void Draw(const std::shared_ptr<GEngineObject>& inspect) = 0;
	};

	template <class T>
	class GEngineObjectInspectorEditor : public IGEngineObjectInspectorEditor
	{
	public:
		GEngineObjectInspectorEditor(GEngineCoreModules* modules);

		void Draw(const std::shared_ptr<GEngineObject>& inspect) override;

	protected:
		virtual void DrawSpecific(const std::shared_ptr<T>& inspect) = 0;

	protected:
		GEngineCoreModules* const _modules;
	};

	// -------------------------------------------------------
	// -------------------------------------------------------

	template<class T>
	GEngineObjectInspectorEditor<T>::GEngineObjectInspectorEditor(GEngineCoreModules* modules)
		: _modules(modules)
	{

	}

	template<class T>
	void GEngineObjectInspectorEditor<T>::Draw(const std::shared_ptr<GEngineObject> &inspect)
	{
		std::shared_ptr<T> derived = std::dynamic_pointer_cast<T>(inspect);
		if (!derived) return;

		DrawSpecific(derived);
	}
}

#endif //INSPECTORGENGINEOBJECTFACTORY_H
