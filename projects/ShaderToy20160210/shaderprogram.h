#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <GLES3/gl3.h>
#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <sstream>
#include <vector>
#include <QVector2D>


class Shader {

	public:

		enum CreationMethod {

			FROM_CODE,
			FROM_FILE
		};

	public:

		Shader( GLenum p_shaderType, std::string const &p_text, CreationMethod const &p_method = FROM_CODE );

		~Shader( );

	private:

		GLenum
		__type;			// GL_VERTEX_SHADER or GL_FRAGMENT_SHADER

		GLint
		__success;

		std::string
		__fname,
		__code;

		GLuint
		__id;

		GLchar
		*__infoLog;

	private:

		bool
		createFromCode( std::string const &p_code );

		bool
		createFromFile( std::string const &p_fileName );

	public:

		std::string
		code( ) const;

		GLuint
		id( ) const;

		std::string
		fileName( ) const;

		bool
		ok( ) const;

		GLenum
		type( ) const;
};

class ShaderProgram {

	public:

		ShaderProgram( std::string const &p_vertexText, std::string const &p_fragmentText, Shader::CreationMethod const &p_method );

		ShaderProgram( std::string const &p_vertexText, std::string const &p_fragmentText, Shader::CreationMethod const &p_method, std::vector< GLuint > const &p_locId, std::vector< std::string > const &p_names );

		~ShaderProgram( );

	private:

		Shader
		*__vertexShader,
		*__fragmentShader;

		GLint
		__success;

		GLuint
		__id;

		GLchar
		*__infoLog;

	public:

		GLuint
		id( ) const;

		bool
		ok( ) const;

		void
		bind( );

		void
		release( );

		void
		setFragDataLocation( GLchar const *p_name );

		void
		setUniformInt( GLchar const *p_name, GLint const &p_value );

		void
		setUniformFloat( GLchar const *p_name, GLfloat const &p_value );

		GLint
		setVertexAttrib( std::string const &p_name, GLint p_size, GLenum p_type, GLboolean p_normalized, GLsizei p_stride, void const *p_offset );
};

#endif // SHADERPROGRAM_H
