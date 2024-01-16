#pragma once

#include <unordered_map>
#include <string>
#include "direct3d.h"

typedef std::unordered_map<std::wstring, D3DTEXTURE> TexHash;

// �C�[�g���[�g�̃e�N�X�`�����ꌳ�Ǘ�����N���X
class TextureFactory
{
	static TextureFactory* instance;

	// <�摜�̃p�X�A�摜���>
	static TexHash* texList;	// �摜�̓����Ă��郊�X�g

	static void Init();	// �������ϐ�

	// �e�N�X�`����Load����֐�
	static void Load();

	TextureFactory() { };
	~TextureFactory();
public:
	// TextureFactory�̃C���X�^���X���擾����
	static TextureFactory* GetInstance();

	static void Delete();

	/// <summary>
	/// TextureFactory�ɂ���摜���擾����
	/// </summary>
	/// <param name="_texPath">�擾����摜�̃p�X</param>
	/// <returns>�摜���/returns>
	D3DTEXTURE Fetch(std::wstring _texPath);
};

