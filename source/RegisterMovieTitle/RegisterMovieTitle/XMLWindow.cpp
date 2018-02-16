#include "XMLWindow.h"

//static変数定義
HINSTANCE XMLWindow::m_xmlhInstance;

XMLWindow::XMLWindow()
{
}


XMLWindow::~XMLWindow()
{
}

//コンストラクタ（引数あり）
XMLWindow::XMLWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	m_xmlhInstance = hInstance;
	m_hprevInstance = hPrevInstance;
	m_lpCmdLine = lpCmdLine;
	m_nCmdShow = nCmdShow;
}

//StartWindowメイン処理
bool XMLWindow::CreateWindowMain() {

	//ウィンドウ作成
	if (!Create()) {
		return false;
	}

	//ウィンドウ表示
	Show(m_xmlhwnd, m_nCmdShow);


	return true;
}

//ウィンドウ作成
bool XMLWindow::Create() {

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);			// 構造体のサイズ
	wcex.style = CS_HREDRAW | CS_VREDRAW;		// クラスのスタイル
	wcex.lpfnWndProc = Wndproc;				// プロシージャ名
	wcex.cbClsExtra = 0;						// 補助メモリ
	wcex.cbWndExtra = 0;						// 補助メモリ
	wcex.hInstance = m_xmlhInstance;					// インスタンス
	wcex.hIcon = (HICON)LoadImage(			// アイコン
		NULL, MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
	wcex.hCursor = (HCURSOR)LoadImage(		// カーソル
		NULL, MAKEINTRESOURCE(IDC_ARROW),
		IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
	wcex.hbrBackground =						// 背景ブラシ
		(HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.lpszMenuName = NULL;					// メニュー名
	wcex.lpszClassName = TEXT("XMLWindow");	// クラス名
	wcex.hIconSm = (HICON)LoadImage(			// 小さいアイコン
		NULL, MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);


	if (RegisterClassEx(&wcex) == 0) {
		return false;
	}

	HWND XMLWindowhWnd = CreateWindow(
		TEXT("XMLWindow"), // ウインドウクラス名
		TEXT("XMLWindow"), // キャプション文字列
		WS_OVERLAPPEDWINDOW | WS_VSCROLL,	// ウインドウのスタイル
		CW_USEDEFAULT,	// 水平位置
		CW_USEDEFAULT,	// 垂直位置
		700,	// 幅
		500,	// 高さ
		NULL,	// 親ウインドウ
		NULL,	// ウインドウメニュー
		m_xmlhInstance,	// インスタンスハンドル
		NULL);	// WM_CREATE情報

	if (XMLWindowhWnd == NULL) {
		return false;
	}

	m_xmlhwnd = XMLWindowhWnd;

	return true;

}

//ウィンドウ表示
void XMLWindow::Show(HWND hwnd, int ncmd) {

	ShowWindow(hwnd, ncmd);
	UpdateWindow(hwnd);
}

//XMLデータ表示関数
bool XMLWindow::ShowXMLData(XML* obj) {

	if (!obj->ReadXMLFile()) {
		return false;
	}

	return true;
}

LRESULT XMLWindow::Wndproc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {

	static SCROLLINFO scinfo;
	static RECT *rc = new RECT;
	static HDC *hdc = new HDC;
	static PAINTSTRUCT *ps = new PAINTSTRUCT;


	static TCHAR strScroll[32];

	switch (msg) {

	case WM_PAINT: {

		XML* obj = new XML();

		if (!ShowXMLData(obj)) {
			return 0L;
		}		
		

		if (::GetClientRect(hwnd, rc) == 0) {
			::MessageBox(hwnd, TEXT("ウィンドウ描写エラー\n"), TEXT("ErrorInfo"), MB_OK);

			delete rc;
			delete hdc;
			delete ps;

			::PostQuitMessage(0);
			return 0L;
		}

		*hdc = ::BeginPaint(hwnd, ps);

		int Defleft = rc->left;

		rc->left -= 400;
		rc->top += 50;

		int Deftop = rc->top;

		::DrawText(*hdc, TEXT("映画タイトル"), -1, rc, DT_CENTER | DT_WORDBREAK);
		
		rc->top += 50;
		for (int i = 0; i < obj->m_XmlDataNum; i++) {
			::DrawText(*hdc, obj->m_TitleValue[i], -1, rc, DT_CENTER | DT_WORDBREAK);
			rc->top += 30;
		}

		rc->left = Defleft;
		rc->top = Deftop;
		::DrawText(*hdc, TEXT("レビュー"), -1, rc, DT_CENTER | DT_WORDBREAK);

		rc->top += 50;
		for (int i = 0; i < obj->m_XmlDataNum; i++) {
			::DrawText(*hdc, obj->m_ReviewValue[i], -1, rc, DT_CENTER | DT_WORDBREAK);
			rc->top += 30;
		}

		rc->left = Defleft;
		rc->left += 400;
		rc->top = Deftop;
		::DrawText(*hdc, TEXT("メモ"), -1, rc, DT_CENTER | DT_WORDBREAK);
		rc->top += 50;
		for (int i = 0; i < obj->m_XmlDataNum; i++) {
			::DrawText(*hdc, obj->m_MemoValue[i], -1, rc, DT_CENTER | DT_WORDBREAK);
			rc->top += 30;
		}

		::EndPaint(hwnd, ps);

		

		break;

	}

	case WM_CREATE:


		//スクロールバー初期設定
		scinfo.cbSize = sizeof(SCROLLINFO);
		scinfo.fMask = SIF_POS |SIF_RANGE;
		scinfo.nMin = 0;
		scinfo.nMax = 100;
		scinfo.nPage = 2;

		SetScrollInfo(hwnd, SB_VERT, &scinfo, TRUE);

		break;

	case WM_SIZE:
		GetClientRect(hwnd, rc);
		scinfo.nPage = (*rc).bottom;
		scinfo.nPos = max(scinfo.nMin, min(scinfo.nMax - (signed)scinfo.nPage, scinfo.nPos));
		SetScrollInfo(hwnd, SB_VERT, &scinfo, TRUE);

		InvalidateRect(hwnd, NULL, TRUE);
		UpdateWindow(hwnd);

		break;

	case WM_VSCROLL:
		switch (LOWORD(wp)) {
		case SB_LINEUP:   scinfo.nPos -= 16; break;
		case SB_LINEDOWN: scinfo.nPos += 16; break;
		case SB_PAGEUP:   scinfo.nPos -= scinfo.nPage / 2; break;
		case SB_PAGEDOWN: scinfo.nPos += scinfo.nPage / 2; break;
		case SB_THUMBPOSITION:
		case SB_THUMBTRACK: scinfo.nPos = HIWORD(wp); break;
		}
		scinfo.nPos = max(scinfo.nMin, min(scinfo.nMax - (signed)scinfo.nPage, scinfo.nPos));
		SetScrollInfo(hwnd, SB_VERT, &scinfo, TRUE);

		InvalidateRect(hwnd, NULL, TRUE);
		UpdateWindow(hwnd);
		break;

	case WM_DESTROY:
		delete rc;
		delete hdc;
		delete ps;

		//::DestroyWindow(hwnd);
		::ShowWindow(hwnd, SW_HIDE);
		break;

	default:
		return ::DefWindowProc(hwnd, msg, wp, lp);

	}

	return 0L;
}