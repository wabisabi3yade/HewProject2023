//=============================================================================
//
// サウンド処理 [xa2.cpp]
//
//=============================================================================

#include "xa2.h"

// パラメータ構造体
typedef struct
{
	LPCSTR filename;	// 音声ファイルまでのパスを設定
	float volume;
	bool bLoop;			// trueでループ。通常BGMはture、SEはfalse。
} PARAM;
//====================================================//
//========================BGM,SE======================//
PARAM g_param[SOUND_LABEL_MAX] =
{
	// BGM（ループさせるのでtrue設定）
	{"BGM/Title.wav", 0.5f,true},
	{"BGM/WorldSelect.wav", 0.2f, true},
	{"BGM/StageSelect.wav",0.4f, true},
	{"BGM/World1.wav", 0.5f,true},
	{"BGM/World2.wav", 0.5f,true},
	{"BGM/World3.wav", 0.2f,true},
	{"BGM/WorldEx.wav", 0.5f,true},
	

	// SE（ループしないのでfalse設定)
	{"SE/PushButton.wav", 0.3f,false},
	{"SE/CursorMove.wav", 0.6f,false},
	{"SE/PushStageBtn.wav", 0.3f,false},
};
//===================================================//
//===================================================//
#ifdef _XBOX //Big-Endian
#define fourccRIFF 'RIFF'
#define fourccDATA 'data'
#define fourccFMT 'fmt '
#define fourccWAVE 'WAVE'
#define fourccXWMA 'XWMA'
#define fourccDPDS 'dpds'
#endif
#ifndef _XBOX //Little-Endian
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'
#endif


//-----------------------------------------------------------------
//    グローバル変数
//-----------------------------------------------------------------
IXAudio2* g_pXAudio2 = NULL;
IXAudio2MasteringVoice* g_pMasteringVoice = NULL;
IXAudio2SourceVoice* g_pSourceVoice[SOUND_LABEL_MAX];

WAVEFORMATEXTENSIBLE	g_wfx[SOUND_LABEL_MAX];			// WAVフォーマット
XAUDIO2_BUFFER			g_buffer[SOUND_LABEL_MAX];
BYTE* g_DataBuffer[SOUND_LABEL_MAX];

//-----------------------------------------------------------------
//    プロトタイプ宣言
//-----------------------------------------------------------------
HRESULT FindChunk(HANDLE, DWORD, DWORD&, DWORD&);
HRESULT ReadChunkData(HANDLE, void*, DWORD, DWORD);

//=============================================================================
// 初期化
//=============================================================================
HRESULT XA_Initialize()
{
	HRESULT      hr;

	HANDLE               hFile;
	DWORD                dwChunkSize;
	DWORD                dwChunkPosition;
	DWORD                filetype;

	// ＣＯＭの初期化
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	/**** Create XAudio2 ****/
	hr = XAudio2Create(&g_pXAudio2, 0);		// 第二引数は､動作フラグ デバッグモードの指定(現在は未使用なので0にする)
	//hr=XAudio2Create(&g_pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);		// 第三引数は、windowsでは無視
	if (FAILED(hr)) {
		CoUninitialize();
		return -1;
	}

	/**** Create Mastering Voice ****/
	hr = g_pXAudio2->CreateMasteringVoice(&g_pMasteringVoice);			// 今回はＰＣのデフォルト設定に任せている
	/*, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE, 0, 0, NULL*/		// 本当６個の引数を持っている
	if (FAILED(hr)) {
		if (g_pXAudio2)	g_pXAudio2->Release();
		CoUninitialize();
		return -1;
	}

	/**** Initalize Sound ****/
	for (int i = 0; i < SOUND_LABEL_MAX; i++)
	{
		memset(&g_wfx[i], 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&g_buffer[i], 0, sizeof(XAUDIO2_BUFFER));

		hFile = CreateFileA(g_param[i].filename, GENERIC_READ, FILE_SHARE_READ, NULL,
			OPEN_EXISTING, 0, NULL);
		if (hFile == INVALID_HANDLE_VALUE) {
			return HRESULT_FROM_WIN32(GetLastError());
		}
		if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) {
			return HRESULT_FROM_WIN32(GetLastError());
		}

		//check the file type, should be fourccWAVE or 'XWMA'
		FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition);
		ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition);
		if (filetype != fourccWAVE)		return S_FALSE;

		FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition);
		ReadChunkData(hFile, &g_wfx[i], dwChunkSize, dwChunkPosition);

		//fill out the audio data buffer with the contents of the fourccDATA chunk
		FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition);
		g_DataBuffer[i] = new BYTE[dwChunkSize];
		ReadChunkData(hFile, g_DataBuffer[i], dwChunkSize, dwChunkPosition);

		CloseHandle(hFile);

		// 	サブミットボイスで利用するサブミットバッファの設定
		g_buffer[i].AudioBytes = dwChunkSize;
		g_buffer[i].pAudioData = g_DataBuffer[i];
		g_buffer[i].Flags = XAUDIO2_END_OF_STREAM;
		if (g_param[i].bLoop)
			g_buffer[i].LoopCount = XAUDIO2_LOOP_INFINITE;
		else
			g_buffer[i].LoopCount = 0;

		g_pXAudio2->CreateSourceVoice(&g_pSourceVoice[i], &(g_wfx[i].Format));
	}

	return hr;
}

//=============================================================================
// 開放処理
//=============================================================================
void XA_Release(void)
{
	for (int i = 0; i < SOUND_LABEL_MAX; i++)
	{
		if (g_pSourceVoice[i])
		{
			g_pSourceVoice[i]->Stop(0);
			g_pSourceVoice[i]->FlushSourceBuffers();
			g_pSourceVoice[i]->DestroyVoice();			// オーディオグラフからソースボイスを削除
			delete[]  g_DataBuffer[i];
		}
	}

	g_pMasteringVoice->DestroyVoice();

	if (g_pXAudio2) g_pXAudio2->Release();

	// ＣＯＭの破棄
	CoUninitialize();
}



//=============================================================================
// 再生
//=============================================================================
void XA_Play(SOUND_LABEL label)
{

	IXAudio2SourceVoice*& pSV = g_pSourceVoice[(int)label];

	if (pSV != nullptr)
	{
		pSV->DestroyVoice();
		pSV = nullptr;
	}

	// ソースボイス作成
	g_pXAudio2->CreateSourceVoice(&pSV, &(g_wfx[(int)label].Format));
	pSV->SubmitSourceBuffer(&(g_buffer[(int)label]));	// ボイスキューに新しいオーディオバッファーを追加

	// ボリューム
	pSV->SetVolume(g_param[label].volume);

	// 再生
	pSV->Start(0);

}

//=============================================================================
// 停止
//=============================================================================
void XA_Stop(SOUND_LABEL label)
{
	if (g_pSourceVoice[(int)label] == NULL) return;

	XAUDIO2_VOICE_STATE xa2state;
	g_pSourceVoice[(int)label]->GetState(&xa2state);
	if (xa2state.BuffersQueued)
	{
		g_pSourceVoice[(int)label]->Stop(0);
	}
}

//=============================================================================
// 一時停止
//=============================================================================
void XA_Resume(SOUND_LABEL label)
{
	IXAudio2SourceVoice*& pSV = g_pSourceVoice[(int)label];
	pSV->Start();
}
//=============================================================================
// ユーティリティ関数群
//=============================================================================
HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition)
{
	HRESULT hr = S_OK;
	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
		return HRESULT_FROM_WIN32(GetLastError());
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD bytesRead = 0;
	DWORD dwOffset = 0;
	while (hr == S_OK)
	{
		DWORD dwRead;
		if (0 == ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL))
			hr = HRESULT_FROM_WIN32(GetLastError());
		if (0 == ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL))
			hr = HRESULT_FROM_WIN32(GetLastError());
		switch (dwChunkType)
		{
		case fourccRIFF:
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (0 == ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL))
				hr = HRESULT_FROM_WIN32(GetLastError());
			break;
		default:
			if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT))
				return HRESULT_FROM_WIN32(GetLastError());
		}
		dwOffset += sizeof(DWORD) * 2;
		if (dwChunkType == fourcc)
		{
			dwChunkSize = dwChunkDataSize;
			dwChunkDataPosition = dwOffset;
			return S_OK;
		}
		dwOffset += dwChunkDataSize;
		if (bytesRead >= dwRIFFDataSize) return S_FALSE;
	}
	return S_OK;
}

HRESULT ReadChunkData(HANDLE hFile, void* buffer, DWORD buffersize, DWORD bufferoffset)
{
	HRESULT hr = S_OK;
	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, bufferoffset, NULL, FILE_BEGIN))
		return HRESULT_FROM_WIN32(GetLastError());
	DWORD dwRead;
	if (0 == ReadFile(hFile, buffer, buffersize, &dwRead, NULL))
		hr = HRESULT_FROM_WIN32(GetLastError());
	return hr;
}
