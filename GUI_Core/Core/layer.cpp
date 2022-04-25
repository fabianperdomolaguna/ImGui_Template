module;

export module Layer;

export struct layer
{
	virtual ~layer() = default;

	virtual void on_attach() {}
	virtual void on_detach() {}

	virtual void on_ui_render() {}
};