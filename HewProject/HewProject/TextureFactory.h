#pragma once

#include <unordered_map>
#include <string>
#include "direct3d.h"

typedef std::unordered_map<std::wstring, D3DTEXTURE> TexHash;

// イートルートのテクスチャを一元管理するクラス
class TextureFactory
{
	static TextureFactory* instance;

	// <画像のパス、画像情報>
	static TexHash* texList;	// 画像の入っているリスト

	static void Init();	// 初期化変数

	// テクスチャをLoadする関数
	static void Load();

	TextureFactory() { };
	~TextureFactory();
public:
	// TextureFactoryのインスタンスを取得する
	static TextureFactory* GetInstance();

	static void Delete();

	/// <summary>
	/// TextureFactoryにある画像を取得する
	/// </summary>
	/// <param name="_texPath">取得する画像のパス</param>
	/// <returns>画像情報/returns>
	D3DTEXTURE Fetch(std::wstring _texPath);
};

