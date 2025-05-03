#pragma once
#include "Event.h"

namespace Lobster
{
	class Layer
	{
	public:
		Layer(const std::string& name = "null");
		virtual ~Layer() {}

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(float dt) {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return _name; }
	private:
		std::string _name;
	};

	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return _layers.begin(); }
		std::vector<Layer*>::iterator end() { return _layers.end(); }
		std::vector<Layer*>::reverse_iterator rbegin() { return _layers.rbegin(); }
		std::vector<Layer*>::reverse_iterator rend() { return _layers.rend(); }

		std::vector<Layer*>::const_iterator begin() const { return _layers.begin(); }
		std::vector<Layer*>::const_iterator end() const { return _layers.end(); }
		std::vector<Layer*>::const_reverse_iterator rbegin() const { return _layers.rbegin(); }
		std::vector<Layer*>::const_reverse_iterator rend() const { return _layers.rend(); }
	private:
		std::vector<Layer*> _layers;
		std::vector<Layer*>::iterator _layer_insert;
	};
}