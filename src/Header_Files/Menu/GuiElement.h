#pragma once
#include "WindowEventListener.h"

namespace ic {

	//window stores canvas, canvas manages all
	//gui elements

	class GuiElement : public WindowEventListener {
	public:
		virtual void update();
		virtual void draw(const float interpol);
	protected:
		s2d::Point2p center;
		s2d::Dim2p size;
		s2d::Point2<s2d::Percent> anchor;
		std::shared_ptr<GuiElement> parent;
		std::vector<std::shared_ptr<GuiElement>> children;
	};

	class Canvas : public GuiElement {
	public:
		Canvas();
		void update();
		void draw(const float interpol);
	};

}