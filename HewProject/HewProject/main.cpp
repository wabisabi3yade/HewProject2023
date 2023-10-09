#undef UNICODE  // Unicodeではなく、マルチバイト文字を使う

#include <Windows.h>
#include <stdio.h>
#include "direct3d.h"
#include "CInput.h"
#include "CSceneManager.h"

// マクロ定義
#define CLASS_NAME    "DX21Smpl"// ウインドウクラスの名前
#define WINDOW_NAME  "あ"// ウィンドウの名前

#define SCREEN_WIDTH (1280)	// ウインドウの幅
#define SCREEN_HEIGHT (720)	// ウインドウの高さ

#define FPS 60	

// 関数のプロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// グローバル変数の宣言
CSceneManager* gSceneManager;
CInput* gInput = new CInput();

// エントリポイント＝このアプリケーションで最初に実行される関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_CLASSDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd;
	hWnd = CreateWindowEx(0,// 拡張ウィンドウスタイル
		CLASS_NAME,// ウィンドウクラスの名前
		WINDOW_NAME,// ウィンドウの名前
		WS_OVERLAPPEDWINDOW - WS_THICKFRAME,// ウィンドウスタイル
		CW_USEDEFAULT,// ウィンドウの左上Ｘ座標
		CW_USEDEFAULT,// ウィンドウの左上Ｙ座標 
		SCREEN_WIDTH,// ウィンドウの幅
		SCREEN_HEIGHT,// ウィンドウの高さ
		NULL,// 親ウィンドウのハンドル
		NULL,// メニューハンドルまたは子ウィンドウID
		hInstance,// インスタンスハンドル
		NULL);// ウィンドウ作成データ

	// 指定されたウィンドウの表示状態を設定(ウィンドウを表示)
	ShowWindow(hWnd, nCmdShow);
	// ウィンドウの状態を直ちに反映(ウィンドウのクライアント領域を更新)
	UpdateWindow(hWnd);

	// Direct3Dの初期化
	D3D_Create(hWnd);
	
	int nFpsCounter = 0;
	// fpsを測定する時に使用
	ULONGLONG o_ms = GetTickCount64();	// １秒間測定するときに使う変数
	ULONGLONG n_ms = o_ms;	// システムを起動してからの時間を受け取る変数
	char str[14] = "";

	// FPS固定用変数
	LARGE_INTEGER liWork;	// 関数から値を受け取る用（Workと付いてる変数は作業用変数のことが多い）
	long long frequency;	// 計測精度

	// 計測制度を取得
	QueryPerformanceFrequency(&liWork);
	frequency = liWork.QuadPart;	// 1秒あたりの解像度が入る
	// 1フレームあたりのカウント値を計算
	long long numCount_1frame = frequency / FPS;	
	// 現在時間(単位：カウント)を取得
	QueryPerformanceCounter(&liWork);
	long long oldCount = liWork.QuadPart;
	long long nowCount = oldCount;

	MSG msg;

	gSceneManager = CSceneManager::GetInstance();
	gSceneManager->SceneChange(CSceneManager::SELECT);
	
	// ゲームループ
	for (;;) {
		BOOL isAnyMessage = PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);

		if (isAnyMessage) // 何かメッセージが届いたか？
		{
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT) {
				break;
			}
		}
		else
		{
			// 時間を取得
			QueryPerformanceCounter(&liWork);
			nowCount = liWork.QuadPart;

			if (nowCount >= oldCount + numCount_1frame)	// 1 / FPS秒経過したか？
			{
				// ゲーム処理実行
				gSceneManager->Act();
				// 現在のキー入力状態をold_KeyStateに入れる
				gInput->UpdateKeyState();
				oldCount = nowCount;
				nFpsCounter++;
			}

			n_ms = GetTickCount64();

			if (n_ms > o_ms + 1000)		// 前のときより1秒間たったら
			{
				/*sprintf_s(str, 14, "fps:%d", nFpsCounter);
				SetWindowText(hWnd, str);*/
				sprintf_s(str, 14, "シーン番号：%d", gSceneManager->GetNowScene());
				SetWindowText(hWnd, str);

				nFpsCounter = 0;	// カウントリセットする
				o_ms = n_ms;	// 今から1秒間測定するために今の時間を代入しておく
			}

		}
	}	// ゲームループの閉じカッコ

	// シーンマネージャーの解放処理
	CSceneManager::Delete();
	delete gInput;

	// DirectX終了処理
	D3D_Release();

	UnregisterClass(CLASS_NAME, hInstance);

	return (int)msg.wParam;
}

// wParam：入力されてるキーコード
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:// ウィンドウ破棄のメッセージ
		PostQuitMessage(0);// “WM_QUIT”メッセージを送る　→　アプリ終了
		break;

	case WM_CLOSE:  // xボタンが押されたら
		DestroyWindow(hWnd);  // “WM_DESTROY”メッセージを送る
		break;

	
	case WM_KEYDOWN:	// キーが押されたら
		gInput->SetKeyDownState(wParam);	// 押されたのを記録する
		break;

	case WM_KEYUP:	// キーが離されたら
		gInput->SetKeyUpState(wParam);	// 離されたのを記録する

	default:
		// 上のcase以外の場合の処理を実行
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}

	return 0;
}
