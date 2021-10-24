#ifndef ___SHADER_HPP_
#define ___SHADER_HPP_
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>
/*#########################################################################
# シェーダークラス

説明
	継承してシェーダーを実装
###########################################################################*/
namespace FrameWork
{
	class Shader
	{

	public:
		Shader();  //コンストラクタ
		~Shader(); //デストラクタ

		bool Input(GLchar *vert, GLchar *frag); //シェーダー読み込み

		void setEnable();	 //有効
		void setDisable(); //無効

		void setBindAttribLocation(const char *str); //頂点シェーダーに属性変数を関連ずける
		void setBindAttribFragment(const char *str); //フラグメントシェーダーに属性変数を関連ずける
		GLint getAttribLocation(const char *str);	   // locationを取得

		// Uniform 設定
		void setUniform1f(const char *name, const float vec);
		void setUniform2f(const char *name, const glm::vec2 vec);
		void setUniform3f(const char *name, const glm::vec3 vec);
		void setUniform4f(const char *name, const glm::vec4 vec);

		// Unform行列　設定
		void setUniformMatrix2fv(const char *name, const glm::mat2 m);
		void setUniformMatrix3fv(const char *name, const glm::mat3 m);
		void setUniformMatrix4fv(const char *name, const glm::mat4 m);

	private:
		GLuint CreateProgram(GLchar *vert, GLchar *frag);			    //プログラムオブジェクトを作成
		GLboolean CompileInfoLog(GLuint shader, const char *str);		    //コンパイルエラーログを取得
		GLboolean ProgramInfoLog(GLuint program);					    //プログラムログを取得
		bool ReadShaderSource(const char *name, std::vector<GLchar> &buffer); //ソースファイルを読み込み
		GLuint loadProgram(const char *vert, const char *frag);		    //プログラムをオブジェクトをロード

		GLuint program; //プログラムオブジェクト
	};
}
#endif
