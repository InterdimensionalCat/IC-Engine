


namespace ic {

	class Window;

	class Renderer {

	public:
		Renderer() {
			window = std::make_shared<Window>();
		}

		static Renderer* get() {
			if (instance.get() == nullptr) {
				instance = std::make_unique<Renderer>();
			}
			return instance.get();
		}

		void draw() {

		}

		/**
		 * @brief the window for the program
		*/
		std::shared_ptr<Window> window;

	private:
		inline static std::unique_ptr<Renderer> instance;
	};
}