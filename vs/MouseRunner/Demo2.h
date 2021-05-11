#ifndef DEMO2_H
#define DEMO2_H


#include <SOIL/SOIL.h>

#include <SDL/SDL_mixer.h>
#include <SDL/SDL_thread.h>
#include <ft2build.h>
#include <freetype/freetype.h>
#include <map>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "Game2.h"

#define NUM_FRAMES 8
#define FRAME_DUR 80

using namespace glm;

#define FONTSIZE 85
#define FONTNAME "zorque.ttf"
#define NUM_BUTTON 2

struct Character {
	GLuint TextureID; // ID handle of the glyph texture
	ivec2 Size; // Size of glyph
	ivec2 Bearing; // Offset from baseline to left/top of glyph
	GLuint Advance; // Offset to advance to next glyph
};

class Demo :
	public Engine::Game
{
public:
	Demo();
	~Demo();
	virtual void Init();
	virtual void DeInit();
	virtual void Update(float deltaTime);
	virtual void Render();
	

	float frame_width = 0, frame_height = 0, frame_width2 = 0, frame_height2 = 0, framew3 = 0, frameh3 = 0, framew4, frameh4,
		  framew_obs5, frameh_obs5, framew_obs6, frameh_obs6, framew_obs7, frameh_obs7, framew_obs8, frameh_obs8, framew_wleft, 
		  frameh_wleft, framew_wright, frameh_wright, framew_obs1, frameh_obs1, framew_obs2, frameh_obs2, framew_obs3, frameh_obs3, 
		  framew_obs4, frameh_obs4, framew_fd1, frameh_fd1;

private:
	
	float frame_dur = 0, oldxpos = 0, oldypos = 0, xpos = 0, ypos = 0, xpos2 = 0, ypos2 = 0, xpos_obs5 = 0, ypos_obs5 = 0, xpos_obs6 = 0, 
		  ypos_obs6 = 0, xpos_obs7 = 0, ypos_obs7 = 0, xpos_obs8 = 0, ypos_obs8 = 0, gravity = 0, xVelocity = 0, yVelocity = 0, yposGround = 0, 
		  xpos3 = 0, ypos3 = 0, xpos4, ypos4, xpos_wleft = 0, ypos_wleft = 0, xpos_wright, ypos_wright, xpos_obs1, ypos_obs1, xpos_obs2, ypos_obs2, 
		  xpos_obs3, ypos_obs3, xpos_obs4, ypos_obs4, xpos_fd1, ypos_fd1, score;
	
	GLuint VBO, VAO, EBO, texture, program, VBO2, VAO2, EBO2, texture2, program2, VBO3, VAO3, EBO3, texture3, program3, 
		   VBO4, VAO4, EBO4, texture4, program4, VBO5, VAO5, EBO5, texture5, program5, VBO6, VAO6, EBO6, texture6, program6, 
		   VBO7, VAO7, EBO7, texture7, program7, VBO8, VAO8, EBO8, texture8, program8, VBO9, VAO9, EBO9, texture9, program9, 
		   VBOi1, VAOi1, EBOi1, texturei1, programi1, VBOi2, VAOi2, EBOi2, texturei2, programi2, 
		   VBOi3, VAOi3, EBOi3, texturei3, programi3, VBOi4, VAOi4, EBOi4, texturei4, programi4, 
		   VBO_Food1, VAO_Food1, EBO_Food1, texture_Food1, program_Food1;
	
	void InitText();
	void RenderText(string text, GLfloat x, GLfloat y, GLfloat scale, vec3 color);
	void InitButton();
	void RenderButton();
	void RenderGame();
	map<GLchar, Character> Characters;
	GLuint textureG[NUM_BUTTON], hover_texture[NUM_BUTTON], VBOG, VBO2G, VAOG, VAO2G, programG;
	float button_width[NUM_BUTTON], button_height[NUM_BUTTON], hover_button_width[NUM_BUTTON], hover_button_height[NUM_BUTTON];
	int activeButtonIndex = -2;
	
	bool walk_anim = false, onGround = true;
	unsigned int frame_idx = 0, flip = 0;
	void BuildPlayerSprite();
	void BuildWallLeft();
	void DrawWallLeft();
	void BuildWallBottom();
	void DrawWallBottom();
	void BuildWallRight();
	void DrawWallRight();
	void BuildWallTop();
	void DrawWallTop();
	void BuildObst1();
	void DrawObst1();
	void BuildObst2();
	void DrawObst2();
	void BuildObst3();
	void DrawObst3();
	void BuildObst4();
	void DrawObst4();
	void BuildInnerWall1();
	void DrawInnerWall1();
	void BuildInnerWall2();
	void DrawInnerWall2();
	void BuildInnerWall3();
	void DrawInnerWall3();
	void BuildInnerWall4();
	void DrawInnerWall4();
	void BuildFood1();
	void DrawFood1();
	bool IsCollided(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2);
	void DrawPlayerSprite();
	void UpdatePlayerSpriteAnim(float deltaTime);
	void ControlPlayerSprite(float deltaTime);
};
#endif

