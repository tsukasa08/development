#pragma once

#include <Windows.h>

class NextWindow
{
public:

	//メンバ関数

	NextWindow();

	~NextWindow();

	//コンストラクタ（引数あり）
	NextWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

	//CreateWindowメイン処理
	bool CreateWindowMain();

	//ウィンドウ作成
	bool Create();

	//ウィンドウ表示
	static void Show(HWND hwnd, int ncmd);

	//ウィンドウプロシージャ
	static LRESULT CALLBACK Wndproc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);





	//メンバ変数

	static HINSTANCE m_nxhInstance;

	HINSTANCE m_nxhprevInstance;

	LPSTR m_nxlpCmdLine;

	static int m_nxnCmdShow;

	//親ウィンドウハンドル
	HWND m_nxhwnd;
};

