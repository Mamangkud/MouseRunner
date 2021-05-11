#include "Demo2.h"
extern int status;
SDL_Window* win;

Demo::Demo() {}

Demo::~Demo() {}

void Demo::Init()
{
	InitText();
	InitButton();
	this->programG = BuildShader("shader.vert", "shader.frag");
	InputMapping("SelectButton", SDLK_RETURN);
	InputMapping("NextButton", SDLK_DOWN);
	InputMapping("PrevButton", SDLK_UP);
	BuildPlayerSprite();
	BuildFood1();
	BuildWallLeft();
	BuildWallBottom();
	BuildWallRight();
	BuildWallTop();
	BuildObst1();
	BuildObst2();
	BuildObst3();
	BuildObst4();
	BuildInnerWall1();
	BuildInnerWall2();
	BuildInnerWall3();
	BuildInnerWall4();
}


void Demo::DeInit() {

}

void Demo::Update(float deltaTime)
{
	if (IsKeyDown("SelectButton")) {
		if (activeButtonIndex == 0) {
			status = true;
		}
		if (activeButtonIndex == 1) {
			SDL_Quit();
			exit(0);
		}
	}

	if (IsKeyUp("NextButton")) {
		if (activeButtonIndex < NUM_BUTTON - 1) {
			activeButtonIndex++;
			SDL_Delay(150);
		}
	}

	if (IsKeyUp("PrevButton")) {
		if (activeButtonIndex > 0) {
			activeButtonIndex--;
			SDL_Delay(150);
		}
	}
	UpdatePlayerSpriteAnim(deltaTime);
	ControlPlayerSprite(deltaTime);
}

void Demo::Render()
{
	//Setting Viewport
	glViewport(0, 0, GetScreenWidth(), GetScreenHeight());

	//Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Set the background color
	glClearColor(102.0f/255.0f, 51.0f/255.0f, 0.0f/255.0f, 1.0f);

	// Set orthographic projection
	mat4 projection;
	projection = ortho(0.0f, static_cast<GLfloat>(GetScreenWidth()), static_cast<GLfloat>(GetScreenHeight()), 0.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(this->programG, "projection"), 1, GL_FALSE, value_ptr(projection));


	RenderText("Mouse Runner", 65, 100, 1.0f, vec3(0.0f, 0.0f, 0.0f));

	RenderButton();

}

void Demo::RenderGame()
{
	//Setting Viewport
	glViewport(0, 0, GetScreenWidth(), GetScreenHeight());

	//Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Set the background color
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	DrawPlayerSprite();
	DrawWallLeft();
	DrawWallBottom();
	DrawWallRight();
	DrawWallTop();
	DrawObst1();
	DrawObst2();
	DrawObst3();
	DrawObst4();
	DrawInnerWall1();
	DrawInnerWall2();
	DrawInnerWall3();
	DrawInnerWall4();
	DrawFood1();
}

int main(int argc, char** argv) {

	Engine::Game &game = Demo();
	game.Start("Mouse Runner [Menu : Use Arrow Key | Gameplay : Use W, A, S, D]", 800, 600, true, WindowFlag::WINDOWED, false, 1);

	return 0;
}