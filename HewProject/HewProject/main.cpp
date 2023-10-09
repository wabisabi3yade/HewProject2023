#undef UNICODE  // Unicode�ł͂Ȃ��A�}���`�o�C�g�������g��

#include <Windows.h>
#include <stdio.h>
#include "direct3d.h"
#include "CInput.h"
#include "CSceneManager.h"

// �}�N����`
#define CLASS_NAME    "DX21Smpl"// �E�C���h�E�N���X�̖��O
#define WINDOW_NAME  "��"// �E�B���h�E�̖��O

#define SCREEN_WIDTH (1280)	// �E�C���h�E�̕�
#define SCREEN_HEIGHT (720)	// �E�C���h�E�̍���

#define FPS 60	

// �֐��̃v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// �O���[�o���ϐ��̐錾
CSceneManager* gSceneManager;
CInput* gInput = new CInput();

// �G���g���|�C���g�����̃A�v���P�[�V�����ōŏ��Ɏ��s�����֐�
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
	hWnd = CreateWindowEx(0,// �g���E�B���h�E�X�^�C��
		CLASS_NAME,// �E�B���h�E�N���X�̖��O
		WINDOW_NAME,// �E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW - WS_THICKFRAME,// �E�B���h�E�X�^�C��
		CW_USEDEFAULT,// �E�B���h�E�̍���w���W
		CW_USEDEFAULT,// �E�B���h�E�̍���x���W 
		SCREEN_WIDTH,// �E�B���h�E�̕�
		SCREEN_HEIGHT,// �E�B���h�E�̍���
		NULL,// �e�E�B���h�E�̃n���h��
		NULL,// ���j���[�n���h���܂��͎q�E�B���h�EID
		hInstance,// �C���X�^���X�n���h��
		NULL);// �E�B���h�E�쐬�f�[�^

	// �w�肳�ꂽ�E�B���h�E�̕\����Ԃ�ݒ�(�E�B���h�E��\��)
	ShowWindow(hWnd, nCmdShow);
	// �E�B���h�E�̏�Ԃ𒼂��ɔ��f(�E�B���h�E�̃N���C�A���g�̈���X�V)
	UpdateWindow(hWnd);

	// Direct3D�̏�����
	D3D_Create(hWnd);
	
	int nFpsCounter = 0;
	// fps�𑪒肷�鎞�Ɏg�p
	ULONGLONG o_ms = GetTickCount64();	// �P�b�ԑ��肷��Ƃ��Ɏg���ϐ�
	ULONGLONG n_ms = o_ms;	// �V�X�e�����N�����Ă���̎��Ԃ��󂯎��ϐ�
	char str[14] = "";

	// FPS�Œ�p�ϐ�
	LARGE_INTEGER liWork;	// �֐�����l���󂯎��p�iWork�ƕt���Ă�ϐ��͍�Ɨp�ϐ��̂��Ƃ������j
	long long frequency;	// �v�����x

	// �v�����x���擾
	QueryPerformanceFrequency(&liWork);
	frequency = liWork.QuadPart;	// 1�b������̉𑜓x������
	// 1�t���[��������̃J�E���g�l���v�Z
	long long numCount_1frame = frequency / FPS;	
	// ���ݎ���(�P�ʁF�J�E���g)���擾
	QueryPerformanceCounter(&liWork);
	long long oldCount = liWork.QuadPart;
	long long nowCount = oldCount;

	MSG msg;

	gSceneManager = CSceneManager::GetInstance();
	gSceneManager->SceneChange(CSceneManager::SELECT);
	
	// �Q�[�����[�v
	for (;;) {
		BOOL isAnyMessage = PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);

		if (isAnyMessage) // �������b�Z�[�W���͂������H
		{
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT) {
				break;
			}
		}
		else
		{
			// ���Ԃ��擾
			QueryPerformanceCounter(&liWork);
			nowCount = liWork.QuadPart;

			if (nowCount >= oldCount + numCount_1frame)	// 1 / FPS�b�o�߂������H
			{
				// �Q�[���������s
				gSceneManager->Act();
				// ���݂̃L�[���͏�Ԃ�old_KeyState�ɓ����
				gInput->UpdateKeyState();
				oldCount = nowCount;
				nFpsCounter++;
			}

			n_ms = GetTickCount64();

			if (n_ms > o_ms + 1000)		// �O�̂Ƃ����1�b�Ԃ�������
			{
				/*sprintf_s(str, 14, "fps:%d", nFpsCounter);
				SetWindowText(hWnd, str);*/
				sprintf_s(str, 14, "�V�[���ԍ��F%d", gSceneManager->GetNowScene());
				SetWindowText(hWnd, str);

				nFpsCounter = 0;	// �J�E���g���Z�b�g����
				o_ms = n_ms;	// ������1�b�ԑ��肷�邽�߂ɍ��̎��Ԃ������Ă���
			}

		}
	}	// �Q�[�����[�v�̕��J�b�R

	// �V�[���}�l�[�W���[�̉������
	CSceneManager::Delete();
	delete gInput;

	// DirectX�I������
	D3D_Release();

	UnregisterClass(CLASS_NAME, hInstance);

	return (int)msg.wParam;
}

// wParam�F���͂���Ă�L�[�R�[�h
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:// �E�B���h�E�j���̃��b�Z�[�W
		PostQuitMessage(0);// �gWM_QUIT�h���b�Z�[�W�𑗂�@���@�A�v���I��
		break;

	case WM_CLOSE:  // x�{�^���������ꂽ��
		DestroyWindow(hWnd);  // �gWM_DESTROY�h���b�Z�[�W�𑗂�
		break;

	
	case WM_KEYDOWN:	// �L�[�������ꂽ��
		gInput->SetKeyDownState(wParam);	// �����ꂽ�̂��L�^����
		break;

	case WM_KEYUP:	// �L�[�������ꂽ��
		gInput->SetKeyUpState(wParam);	// �����ꂽ�̂��L�^����

	default:
		// ���case�ȊO�̏ꍇ�̏��������s
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}

	return 0;
}
