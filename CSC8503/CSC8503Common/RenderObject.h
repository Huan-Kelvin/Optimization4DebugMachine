#pragma once
#include "../../Common/Matrix4.h"
#include "../../Common/TextureBase.h"
#include "../../Common/ShaderBase.h"
#include "../../Common/Vector4.h"
#include "../../Common/Vector3.h"
/*
渲染目标需要提供 网格体、贴图、shader、变换、颜色
因为我们使用的是简单的光照模型 所以贴图没有指向Bump贴图的部分 （在复制的游戏引擎中贴图也许会被换做是一个指向材料的指针数组）
*/
namespace NCL {
	using namespace NCL::Rendering;

	class MeshGeometry;
	namespace CSC8503 {
		class Transform;
		using namespace Maths;

		class RenderObject
		{
		public:
			RenderObject(Transform* parentTransform, MeshGeometry* mesh, TextureBase* tex, ShaderBase* shader,Vector3 off=Vector3(0,0,0));
			~RenderObject();

			void SetDefaultTexture(TextureBase* t) {
				texture = t;
			}

			TextureBase* GetDefaultTexture() const {
				return texture;
			}

			MeshGeometry*	GetMesh() const {
				return mesh;
			}

			Transform*		GetTransform() const {
				return transform;
			}

			ShaderBase*		GetShader() const {
				return shader;
			}

			void SetColour(const Vector4& c) {
				colour = c;
			}

			Vector4 GetColour() const {
				return colour;
			}
			Vector3 GetOff() const
			{
				return offset;
			}
		protected:
			MeshGeometry*	mesh;
			TextureBase*	texture;
			ShaderBase*		shader;
			Transform*		transform;
			Vector4			colour;//颜色用来表达 如果物体被点击或者物体发生碰撞的时候 给出反应
			Vector3         offset;
		};
	}
}
