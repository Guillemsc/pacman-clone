//
// Created by guillem on 6/9/25.
//

#ifndef INSPECTORGENGINEOBJECTFACTORY_H
#define INSPECTORGENGINEOBJECTFACTORY_H

#include <memory>

namespace GEngine
{
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
		GEngineObjectInspectorEditor(const std::weak_ptr<GEngineCoreApplication>& app);

		void Draw(const std::shared_ptr<GEngineObject>& inspect) override;

	protected:
		virtual void DrawSpecific(const std::shared_ptr<T>& inspect) = 0;

	protected:
		std::weak_ptr<GEngineCoreApplication> _app;;
	};

	// -------------------------------------------------------
	// -------------------------------------------------------

	template<class T>
	GEngineObjectInspectorEditor<T>::GEngineObjectInspectorEditor(const std::weak_ptr<GEngineCoreApplication>& app)
	{
		_app = app;
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
