#include "Layer.h"

namespace Lobster
{
	Layer::Layer(const std::string& name) : _name(name) {}


	LayerStack::LayerStack()
	{
		_layer_insert = _layers.begin();
	}

	LayerStack::~LayerStack()
	{
		for(Layer* layer : _layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		_layer_insert = _layers.emplace(_layer_insert,layer);
		layer->OnAttach();
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		_layers.emplace_back(overlay);
		overlay->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(_layers.begin(),_layers.end(),layer);

		if(it != _layers.end())
		{
			_layers.erase(it);
			_layer_insert--;
		}

		layer->OnDetach();
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(_layers.begin(),_layers.end(),overlay);

		if(it != _layers.end())
			_layers.erase(it);

		overlay->OnDetach();
	}
}