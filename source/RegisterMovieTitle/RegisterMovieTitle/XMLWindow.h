#pragma once

#include <Windows.h>
#include "XML.h"

class XMLWindow
{
public:
	XMLWindow();
	~XMLWindow();

	//コンストラクタ（引数あり）
	XMLWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);


	//CreateWindowメイン処理
	bool CreateWindowMain();

	//ウィンドウ作成
	bool Create();

	//ウィンドウ表示
	void Show(HWND hwnd, int ncmd);

	//XMLファイルデータ表示
	static bool ShowXMLData(XML* obj);

	//ウィンドウプロシージャ
	static LRESULT CALLBACK Wndproc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

	//親ウィンドウハンドル
	HWND m_xmlhwnd;

	static HINSTANCE m_xmlhInstance;

	HINSTANCE m_hprevInstance;

	LPSTR m_lpCmdLine;

	int m_nCmdShow;
};

