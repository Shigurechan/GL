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
		Shader(const char* vert,const char* frag);  //コンストラクタ
		~Shader(); //デストラクタ

		void Delete();	//削除

		void setEnable();	 //有効
		void setDisable(); //無効

		// Uniform float型 設定
		void setUniform1f(const char *name, const float vec);
		void setUniform2f(const char *name, const glm::vec2 vec);
		void setUniform3f(const char *name, const glm::vec3 vec);
		void setUniform4f(const char *name, const glm::vec4 vec);

		// Uniform  int型 設定
		void setUniform1i(const char *name, const int vec);
		void setUniform2i(const char *name, const glm::ivec2 vec);
		void setUniform3i(const char *name, const glm::ivec3 vec);
		void setUniform4i(const char *name, const glm::ivec4 vec);


		// Unform行列　設定
		void setUniformMatrix2fv(const char *name, const glm::mat2 m);
		void setUniformMatrix3fv(const char *name, const glm::mat3 m);
		void setUniformMatrix4fv(const char *name, const glm::mat4 m);

		void setVertexAttributeSize(int num);					//頂点情報の数を指定
		void setVertexAttribute(const char* str,int num);			//頂点情報 設定
		void setVertexAttribute_Reset();						//頂点情報の設定をリセット






		void setBindAttribLocation(const char *str); //頂点シェーダーに属性変数を関連ずける
		void setBindAttribFragment(const char *str); //フラグメントシェーダーに属性変数を関連ずける
		GLint getAttribLocation(const char *str);	   //locationを取得

	private:

		GLuint CreateProgram(GLchar *vert, GLchar *frag);			    //プログラムオブジェクトを作成
		GLboolean CompileInfoLog(GLuint shader, const char *str);		    //コンパイルエラーログを取得
		GLboolean ProgramInfoLog(GLuint program);					    //プログラムログを取得
		bool ReadShaderSource(const char *name, std::vector<GLchar> &buffer); //ソースファイルを読み込み
		GLuint loadProgram(const char *vert, const char *frag);		    //プログラムをオブジェクトをロード

		int offset;			//頂点オフセット
		int attributeSize;	//頂点サイズ
		GLuint program; 		//プログラムオブジェクト
	};
}
#endif
