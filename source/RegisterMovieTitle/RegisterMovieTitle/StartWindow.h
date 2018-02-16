#pragma once

#include <Windows.h>
#include <map>

#include "NextWindow.h"
#include "XMLWindow.h"

//StartWindowクラス
//StartWindowを表示

class StartWindow
{
public:

	//メンバ関数

	//コンストラクタ
	StartWindow();

	//コンストラクタ（引数あり）
	StartWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

	//デストラクタ
	~StartWindow();

	//CreateWindowメイン処理
	bool CreateWindowMain();

	//ウィンドウ作成
	bool Create();

	//ウィンドウ表示
	void Show(HWND hwnd, int ncmd);

	//ウィンドウレイアウト（テキストボックスやボタンの作成）
	static bool WindowLayout(HWND hwnd);

	//ウィンドウプロシージャ
	static LRESULT CALLBACK Wndproc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);





	//メンバ変数

	static HINSTANCE m_hInstance;

	HINSTANCE m_hprevInstance;

	LPSTR m_lpCmdLine;

	int m_nCmdShow;

	//親ウィンドウハンドル
	HWND m_hwnd;

	//確認画面クラスのオブジェクト
	static NextWindow *m_obj;

	//XMLウィンドウのオブジェクト
	static XMLWindow *m_xmlobj;

	//親ウィンドウに属するテキストボックスやボタンのウィンドウハンドルのリスト
	static std::map<std::string, HWND> m_HandleList;
};

