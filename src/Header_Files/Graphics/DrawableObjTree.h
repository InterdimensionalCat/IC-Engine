namespace ic {
	class DrawableObjTree {



		void removeChild();
		void addBackChild();
		void addFrontChild();
		void addDrawableObject();

		void preRender(const float interpol);
		void render();
		void postRender();

		std::unique_ptr<DrawableObject> drawable;

		std::vector<std::unique_ptr<DrawableObjTree>> frontchildren;
		std::vector<std::unique_ptr<DrawableObjTree>> backchildren;
	};
}