
#include "Demo2.h"

void Demo::UpdatePlayerSpriteAnim(float deltaTime)
{
	// Update animation
	frame_dur += deltaTime;

	if (walk_anim && frame_dur > FRAME_DUR) {
		frame_dur = 0;
		if (frame_idx == NUM_FRAMES - 1) frame_idx = 0;  else frame_idx++;

		// Pass frameIndex to shader
		UseShader(this->program);
		glUniform1i(glGetUniformLocation(this->program, "frameIndex"), frame_idx);
	}
}

void Demo::ControlPlayerSprite(float deltaTime)
{
	walk_anim = false;
	oldxpos = xpos;
	oldypos = ypos;

	if (IsKeyDown("Move Right")) {
		xpos += deltaTime * xVelocity;
		flip = 0;
		walk_anim = true;
	}

	if (IsKeyDown("Move Left")) {
		xpos -= deltaTime * xVelocity;
		flip = 1;
		walk_anim = true;
	}

	if (IsKeyDown("Move Down")) {
		ypos += deltaTime * xVelocity;
		flip = 3;
		walk_anim = true;
	}

	if (IsKeyDown("Move Up")) {
		ypos -= deltaTime * xVelocity;
		flip = 2;
		walk_anim = true;
	}


	//// cek collision dengan player 

	// Wall
	if (IsCollided(xpos, ypos, frame_width, frame_height, xpos3, ypos3, framew3, frameh3)) {
		xpos = oldxpos;
		ypos = oldypos;
	}
	if (IsCollided(xpos, ypos, frame_width, frame_height, xpos4, ypos4, framew4, frameh4)) {
		xpos = oldxpos;
		ypos = oldypos;
	}

	if (IsCollided(xpos, ypos, frame_width, frame_height, xpos_wleft, ypos_wleft, framew_wleft, frameh_wleft)) {
		xpos = oldxpos;
		ypos = oldypos;
	}

	if (IsCollided(xpos, ypos, frame_width, frame_height, xpos_wright, ypos_wright, framew_wright, frameh_wright)) {
		xpos = oldxpos;
		ypos = oldypos;
	}

	// Obstacle
	if (IsCollided(xpos, ypos, frame_width, frame_height, xpos_obs1, ypos_obs1, framew_obs1, frameh_obs1)) {
		xpos = oldxpos;
		ypos = oldypos;
	}

	if (IsCollided(xpos, ypos, frame_width, frame_height, xpos_obs2, ypos_obs2, framew_obs2, frameh_obs2)) {
		xpos = oldxpos;
		ypos = oldypos;
	}
	if (IsCollided(xpos, ypos, frame_width, frame_height, xpos_obs3, ypos_obs3, framew_obs3, frameh_obs3)) {
		xpos = oldxpos;
		ypos = oldypos;
	}
	if (IsCollided(xpos, ypos, frame_width, frame_height, xpos_obs4, ypos_obs4, framew_obs4, frameh_obs4)) {
		xpos = oldxpos;
		ypos = oldypos;
	}

	if (IsCollided(xpos, ypos, frame_width, frame_height, xpos_obs5, ypos_obs5, framew_obs5, frameh_obs5)) {
		xpos = oldxpos;
		ypos = oldypos;
	}

	if (IsCollided(xpos, ypos, frame_width, frame_height, xpos_obs6, ypos_obs6, framew_obs6, frameh_obs6)) {
		xpos = oldxpos;
		ypos = oldypos;
	}
	
	if (IsCollided(xpos, ypos, frame_width, frame_height, xpos_obs8, ypos_obs8, framew_obs8, frameh_obs8)) {
		xpos = oldxpos;
		ypos = oldypos;
	}

	// Pintu Finish 
	if (IsCollided(xpos, ypos, frame_width, frame_height, xpos_obs7, ypos_obs7, framew_obs7, frameh_obs7)) {
		xpos = oldxpos;
		ypos = oldypos;
		SDL_Quit();
		exit(0);
	}

	// Food
	if (IsCollided(xpos, ypos, frame_width, frame_height, xpos_fd1, ypos_fd1, framew_fd1, frameh_fd1)) {
		glDeleteTextures(1, &texture_Food1);
		glDeleteVertexArrays(1, &VAO_Food1);
		score++;
	}

}

void Demo::DrawPlayerSprite() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	UseShader(this->program);
	glUniform1i(glGetUniformLocation(this->program, "ourTexture"), 0);

	// set flip
	glUniform1i(glGetUniformLocation(this->program, "flip"), flip);
	mat4 model;
	// Translate sprite along x-axis
	model = translate(model, vec3(xpos, ypos, 0.0f));
	// Scale sprite 
	model = scale(model, vec3(frame_width, frame_height, 1));
	glUniformMatrix4fv(glGetUniformLocation(this->program, "model"), 1, GL_FALSE, value_ptr(model));

	// Draw sprite
	glBindVertexArray(VAO);
	glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
	glDisable(GL_BLEND);
}

void Demo::BuildPlayerSprite()
{
	this->program = BuildShader("playerSprite.vert", "playerSprite.frag");

	// Pass n to shader
	UseShader(this->program);
	glUniform1f(glGetUniformLocation(this->program, "n"), 1.0f / NUM_FRAMES);

	// Load and create a texture 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Load, create texture 
	int width, height;
	unsigned char* image = SOIL_load_image("anim45.png", &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	// Set up vertex data (and buffer(s)) and attribute pointers
	frame_width = ((float)width-8) / NUM_FRAMES;
	frame_height = (float)height-8;
	GLfloat vertices[] = {
		// Positions   // Colors           // Texture Coords
		1,  1, 0.0f,   1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // Bottom Right
		1,  0, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Top Right
		0,  0, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f, // Top Left
		0,  1, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // Bottom Left 
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 3, 2, 1
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

	// Set orthographic projection
	mat4 projection;
	projection = ortho(0.0f, static_cast<GLfloat>(GetScreenWidth()), static_cast<GLfloat>(GetScreenHeight()), 0.0f, -1.0f, 1.0f);
	glUniformMatrix4fv(glGetUniformLocation(this->program, "projection"), 1, GL_FALSE, value_ptr(projection));

	// set sprite position, gravity, velocity
	xpos = (GetScreenWidth() - frame_width) / 2;
	/*yposGround = GetScreenHeight() - frame_height;*/
	ypos = 495;
	gravity = 0.05f;
	xVelocity = 0.1f;

	// Add input mapping
	// to offer input change flexibility you can save the input mapping configuration in a configuration file (non-hard code) !
	InputMapping("Move Right", SDLK_RIGHT);
	InputMapping("Move Left", SDLK_LEFT);
	InputMapping("Move Right", SDLK_d);
	InputMapping("Move Left", SDLK_a);
	InputMapping("Move Right", SDL_BUTTON_RIGHT);
	InputMapping("Move Left", SDL_BUTTON_LEFT);
	InputMapping("Move Right", SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
	InputMapping("Move Left", SDL_CONTROLLER_BUTTON_DPAD_LEFT);
	InputMapping("Move Up", SDLK_w);
	InputMapping("Move Down", SDLK_s);

	InputMapping("Quit", SDLK_ESCAPE);
}