#pragma once
#include "shared.h"
#include <fstream>

namespace LAM {
    class Shader final {
    public:
        Shader() = default;

        Shader(const std::string& vs_path, const std::string& fs_path) {
            auto vertex_shader = Compile(GL_VERTEX_SHADER, LoadShader(vs_path));
            auto fragment_shader = Compile(GL_FRAGMENT_SHADER, LoadShader(fs_path));

            this->_ID = CreateProgram(vertex_shader, fragment_shader);

            glDeleteShader(vertex_shader);
            glDeleteShader(fragment_shader);
        }

        ~Shader() {
            glDeleteProgram(this->_ID);
        }

        void Use() const {
            glUseProgram(this->_ID);
        }

        void Unuse() const {
            ; // ?
        }

        GLuint ID() const noexcept {
            return _ID;
        }

        void setBool(const std::string &name, bool value) const {
            glUniform1i(glGetUniformLocation(_ID, name.c_str()), (int)value);
        }

        void setInt(const std::string &name, int value) const {
            glUniform1i(glGetUniformLocation(_ID, name.c_str()), value);
        }

        void setFloat(const std::string &name, float value) const {
            glUniform1f(glGetUniformLocation(_ID, name.c_str()), value);
        }

        void setVec2(const std::string &name, const glm::vec2 &value) const {
            glUniform2fv(glGetUniformLocation(_ID, name.c_str()), 1, &value[0]);
        }

        void setVec2(const std::string &name, float x, float y) const {
            glUniform2f(glGetUniformLocation(_ID, name.c_str()), x, y);
        }

        void setVec3(const std::string &name, const glm::vec3 &value) const {
            glUniform3fv(glGetUniformLocation(_ID, name.c_str()), 1, &value[0]);
        }

        void setVec3(const std::string &name, float x, float y, float z) const {
            glUniform3f(glGetUniformLocation(_ID, name.c_str()), x, y, z);
        }

        void setVec4(const std::string &name, const glm::vec4 &value) const {
            glUniform4fv(glGetUniformLocation(_ID, name.c_str()), 1, &value[0]);
        }

        void setVec4(const std::string &name, float x, float y, float z, float w) {
            glUniform4f(glGetUniformLocation(_ID, name.c_str()), x, y, z, w);
        }

        void setMat2(const std::string &name, const glm::mat2 &mat) const {
            glUniformMatrix2fv(glGetUniformLocation(_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }

        void setMat3(const std::string &name, const glm::mat3 &mat) const {
            glUniformMatrix3fv(glGetUniformLocation(_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }

        void setMat4(const std::string &name, const glm::mat4 &mat) const {
            glUniformMatrix4fv(glGetUniformLocation(_ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
        }

    private:
        GLuint _ID;

        static std::string LoadShader(const std::string& path) {
            static int shader_count = 0;
            std::ifstream source_file(path);

            if (!source_file.is_open()) {
                throw std::runtime_error(std::string("Shader source file not found. Shader #") + std::to_string(shader_count));
            }

            std::string buffer, result_shader = "";
            while (std::getline(source_file, buffer)) {
                result_shader += buffer + '\n';
            }
            ++shader_count;
            return result_shader;
        }

        static GLuint Compile(GLenum type, const std::string& src) {
            unsigned int id = glCreateShader(type);

            int result;
            const char* local_src = src.c_str();

            glShaderSource(id, 1, &local_src, nullptr);
            glCompileShader(id);

            glGetShaderiv(id, GL_COMPILE_STATUS, &result);
            if (result == GL_FALSE) {
                int length;
                glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
                char* log_message = (char*)malloc(length * sizeof(char));
                glGetShaderInfoLog(id, length, &length, log_message);
                auto err = std::runtime_error((std::string)"Failed to compile "
                    + (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
                    + " shader!\n"
                    + (std::string)log_message);
                free(log_message);
                throw err;
            }

            return id;
        }

        static GLuint CreateProgram(GLuint vs, GLuint fs) {
            unsigned int program =	glCreateProgram();

            glAttachShader(program, vs);
            glAttachShader(program, fs);
            glLinkProgram(program);
            glValidateProgram(program);

            glDeleteShader(vs);
            glDeleteShader(fs);

            return program;
        }
    };
}
