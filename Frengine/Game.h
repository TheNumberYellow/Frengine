#pragma once
#include <vector>
#include <map>

#include "Window.h"
#include "Drawable.h"
#include "ShaderProgram.h"
#include "Keyboard.h"
#include "Timer.h"
#include "GLTexture.h"
#include "ResourceManager.h"
#include "Camera2D.h"
#include "Sprite.h"

namespace FR {
	struct GameElement {
		Drawable* drawable;
		ShaderProgram* shader;
	};


	class Game {
	public:
		Game();
		~Game();

		int RunGame();

	protected:
		virtual void AddDrawableElement(Drawable* drawable, ShaderProgram* shader, std::string name) final;
		virtual void AddDrawableElement(Drawable* drawable, std::string name) final;

		virtual Drawable* GetDrawable(std::string name) final;
		virtual bool IsKeyPressed(FR::Key key) final;


		void SetWindowSize(int x, int y);
		void SetWindowTitle(std::string title);
		
	private:
		std::map <std::string, GameElement> elements;

		Keyboard keyboard;
		Window window;
		Timer timer;
		Camera2D camera;
		bool gameRunning = true;

		void Initialize();
		int GameLoop();
		void DrawElements();
		void PollEvents();

		virtual void SetUp() = 0;
		virtual void Update(double delta) = 0;

		virtual void KeyDown(SDL_Keycode keycode);
		virtual void KeyUp(SDL_Keycode keycode);

		virtual void MouseClicked(int x, int y);
	};
}