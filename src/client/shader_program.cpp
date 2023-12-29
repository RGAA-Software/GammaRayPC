#include "shader_program.h"

#include <iostream>

namespace tc
{

	std::shared_ptr<ShaderProgram> ShaderProgram::Make(QOpenGLFunctions_3_3_Core* fk, const std::string& vertex, const std::string& fragment) {
		return std::make_shared<ShaderProgram>(fk, vertex, fragment);
	}

	ShaderProgram::ShaderProgram(QOpenGLFunctions_3_3_Core* fk, const std::string& vertex, const std::string& fragment) {
		this->fk = fk;

		GLuint vertex_shader = fk->glCreateShader(GL_VERTEX_SHADER);
		char const* vertex_source = vertex.c_str();
		fk->glShaderSource(vertex_shader, 1, &vertex_source, NULL);
		fk->glCompileShader(vertex_shader);
		CheckShaderError(vertex_shader, "vertex");

		GLuint fragment_shader = fk->glCreateShader(GL_FRAGMENT_SHADER);
		char const* fragment_source = fragment.c_str();
		fk->glShaderSource(fragment_shader, 1, &fragment_source, NULL);

		fk->glCompileShader(fragment_shader);
		CheckShaderError(fragment_shader, "fragment");

		program_id = fk->glCreateProgram();

		fk->glAttachShader(program_id, vertex_shader);
		fk->glAttachShader(program_id, fragment_shader);

		fk->glLinkProgram(program_id);
		CheckShaderError(program_id, "program");
	}

	ShaderProgram::~ShaderProgram() {

	}

	void ShaderProgram::CheckShaderError(GLuint id, const std::string& type) {
		int check_flag;
		char check_info[1024];
		if (type != "program") {
			fk->glGetShaderiv(id, GL_COMPILE_STATUS, &check_flag);
			if (!check_flag) {
				fk->glGetShaderInfoLog(id, 1024, NULL, check_info);
				std::cout << type << " error:" << check_info << std::endl;;
			}
		}
		else {
			fk->glGetShaderiv(id, GL_LINK_STATUS, &check_flag);
			if (!check_flag) {
				fk->glGetProgramInfoLog(id, 1024, NULL, check_info);
				std::cout << type << " error:" << check_info << std::endl;
			}
		}
	}

	int ShaderProgram::GetProgramId() {
		return program_id;
	}

	void ShaderProgram::Active() {
		fk->glUseProgram(program_id);
	}
}