#pragma once

#include <memory>
#include <string>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <QOpenGLFunctions_3_3_Core>

namespace tc
{

	class ShaderProgram {

	public:

		static std::shared_ptr<ShaderProgram> Make(QOpenGLFunctions_3_3_Core* fk, const std::string& vertex, const std::string& fragment);

		ShaderProgram(QOpenGLFunctions_3_3_Core* fk, const std::string& vertex, const std::string& fragment);
		~ShaderProgram();

		void Active();
		int GetProgramId();

		void Release() {
			this->fk->glUseProgram(0);
		}

		int GetAttribLocation(const std::string& name) {
			return this->fk->glGetAttribLocation(program_id, name.c_str());
		}

		int GetUniformLocation(const std::string& name) {
			return this->fk->glGetUniformLocation(program_id, name.c_str());
		}

		void SetUniform1i(const std::string& name, int value) {
			this->fk->glUniform1i(GetUniformLocation(name), value);
		}

		void SetUniform1f(const std::string& name, float value) {
			this->fk->glUniform1f(GetUniformLocation(name), value);
		}

		void SetUniform2fv(const std::string& name, const glm::vec2& vec) {
			this->fk->glUniform2f(GetUniformLocation(name), vec.x, vec.y);
		}

		void SetUniform3fv(const std::string& name, const glm::vec3& vec) {
			this->fk->glUniform3f(GetUniformLocation(name), vec.x, vec.y, vec.z);
		}

		void SetUniformMatrix(const std::string& name, const glm::mat4& m) {
			auto loc = GetUniformLocation(name);
			this->fk->glUniformMatrix4fv(loc, 1, false, glm::value_ptr(m));
		}

		void CheckShaderError(GLuint id, const std::string& type);

	private:

		GLuint program_id;
		QOpenGLFunctions_3_3_Core* fk;

	};

	typedef std::shared_ptr<ShaderProgram> ShaderProgramPtr;
}