#pragma once

#include <array>
#include <utility>
#include <memory>
#include <map>
#include <deque>
#include <string>


#include "common.hpp"
#include "components.hpp"
#include "tiny_ecs.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H



// System responsible for setting up OpenGL and for rendering all the
// visual entities in the game
class RenderSystem {
	/**
	 * The following arrays store the assets the game will use. They are loaded
	 * at initialization and are assumed to not be modified by the render loop.
	 *
	 * Whenever possible, add to these lists instead of creating dynamic state
	 * it is easier to debug and faster to execute for the computer.
	 */
	std::array<GLuint, texture_count> texture_gl_handles;
	std::array<ivec2, texture_count> texture_dimensions;

	// Make sure these paths remain in sync with the associated enumerators.
	// Associated id with .obj path
	const std::vector < std::pair<GEOMETRY_BUFFER_ID, std::string>> mesh_paths =
	{
		  std::pair<GEOMETRY_BUFFER_ID, std::string>(GEOMETRY_BUFFER_ID::SALMON, mesh_path("salmon.obj")),
		  // specify meshes of other assets here
		  std::pair<GEOMETRY_BUFFER_ID, std::string>(GEOMETRY_BUFFER_ID::SQUARE, mesh_path("square.obj")),

		   std::pair<GEOMETRY_BUFFER_ID, std::string>(GEOMETRY_BUFFER_ID::PORTAL, mesh_path("portal.obj"))
	};

	// Make sure these paths remain in sync with the associated enumerators.
const std::array<std::string, texture_count> texture_paths = {
			textures_path("green_fish.png"),
			textures_path("eel.png"),
			textures_path("city.png"),
			textures_path("/redRun/redRun1.png"),
			textures_path("/redRun/redRun2.png"),
			textures_path("/redRun/redRun3.png"),
			textures_path("/blueRun/blueRun1.png"),
			textures_path("/blueRun/blueRun2.png"),
			textures_path("/blueRun/blueRun3.png"),
			textures_path("bullet.png"),
			textures_path("block.png"),
			textures_path("pad.png"),
			textures_path("/assets/2 Guns/6_1.png"),
			textures_path("/assets/2 Guns/4_1.png"),
			textures_path("help.png"),
			textures_path("desert.png"),
			textures_path("intro.jpg"),
			textures_path("intro1.jpg"),
			textures_path("grenade.png"),
			textures_path("potion.png"),
			textures_path("laser.png"),
			textures_path("long_laser.png"),
			textures_path("explosion.png"),
			textures_path("icemountain.jpg"),
			textures_path("icepad.png"),
			textures_path("scifi.png"),
			textures_path("crossHair.png"),
			textures_path("jungle.jpg"),
			textures_path("rainbow.jpg"),
			textures_path("space.jpg"),
			//textures_path("grass.png");
			textures_path("bluewin.jpg"),
			textures_path("redwin.jpg"),
			textures_path("tutorial.png"),
			textures_path("black.png")
		};
	std::array<GLuint, effect_count> effects;
	// Make sure these paths remain in sync with the associated enumerators.
	const std::array<std::string, effect_count> effect_paths = {
		shader_path("coloured"),
		shader_path("egg"),
		shader_path("font"),
		shader_path("salmon"),
		shader_path("textured"),
		shader_path("water"),
		shader_path("laser_beam")};

		// font character structure
struct Character {
	unsigned int TextureID;  // ID handle of the glyph texture
	glm::ivec2   Size;       // Size of glyph
	glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
	unsigned int Advance;    // Offset to advance to next glyph
	char character;
};

	GLuint vao;

	std::array<GLuint, geometry_count> vertex_buffers;
	std::array<GLuint, geometry_count> index_buffers;
	std::array<Mesh, geometry_count> meshes;

		// font elements
	std::map<char, Character> m_ftCharacters;
	GLuint m_font_shaderProgram;
	GLuint m_font_VAO;
	GLuint m_font_VBO;

public:
	// Initialize the window
	bool init(GLFWwindow* window);

	template <class T>
	void bindVBOandIBO(GEOMETRY_BUFFER_ID gid, std::vector<T> vertices, std::vector<uint16_t> indices);

	void initializeGlTextures();

	void initializeGlEffects();

	void initializeGlMeshes();
	Mesh& getMesh(GEOMETRY_BUFFER_ID id) { return meshes[(int)id]; };

	float getTextWidth(const std::string& text, float scale);

	void initializeGlGeometryBuffers();
	// Initialize the screen texture used as intermediate render target
	// The draw loop first renders to this texture, then it is used for the wind
	// shader
	bool initScreenTexture();
	bool fontInit(GLFWwindow* window, const std::string& font_filename, unsigned int font_default_size);

	// Destroy resources associated to one or all entities created by the system
	~RenderSystem();

	// Draw all entities
	void draw();

	mat3 createProjectionMatrix();

	void renderText(std::string text, float x, float y, float scale, const glm::vec3& color, const glm::mat4& trans);


	void renderMatchRecords(const std::deque<std::string>& match_records);

	void renderHealthBar(vec2 position, vec2 size, vec3 color);

	void renderSegmentedHealthBar(vec2 position, vec2 segment_size, int current_health, int max_health, vec3 color, vec3 background_color);

	void renderPlayerHealthUI(Entity player_entity);

	void renderHealthBarBorder(vec2 position, vec2 size, vec3 border_color);

	std::vector<std::string> wrapText(const std::string& text, float max_width, float scale);
	
private:
	// Internal drawing functions for each entity type
	void drawTexturedMesh(Entity entity, const mat3& projection);
	void drawToScreen();
	std::string readShaderFile(const std::string& filepath);

	// Window handle
	GLFWwindow* window;

	// Screen texture handles
	GLuint frame_buffer;
	GLuint off_screen_render_buffer_color;
	GLuint off_screen_render_buffer_depth;

	Entity screen_state_entity;

};

bool loadEffectFromFile(
	const std::string& vs_path, const std::string& fs_path, GLuint& out_program);

