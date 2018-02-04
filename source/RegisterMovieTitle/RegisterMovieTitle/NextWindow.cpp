#include "NextWindow.h"
#include <vector>

//static変数定義
HINSTANCE NextWindow::m_nxhInstance;
int NextWindow::m_nxnCmdShow;

NextWindow::NextWindow()
{
}

//コンストラクタ（引数あり）
NextWindow::NextWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){

	m_nxhInstance = hInstance;
	m_nxhprevInstance = hPrevInstance;
	m_nxlpCmdLine = lpCmdLine;
	m_nxnCmdShow = nCmdShow;

	m_nxhwnd = nullptr;
}

NextWindow::~NextWindow()
{
}


//StartWindowメイン処理
bool NextWindow::CreateWindowMain(){

	//ウィンドウ作成
	//if (!Create()){
	//	return false;
	//}

	//ウィンドウ表示
	Show(m_nxhwnd, m_nxnCmdShow);


	return true;
}

//ウィンドウ作成
bool NextWindow::Create(){

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);			// 構造体のサイズ
	wcex.style = CS_HREDRAW | CS_VREDRAW;		// クラスのスタイル
	wcex.lpfnWndProc = Wndproc;				// プロシージャ名
	wcex.cbClsExtra = 0;						// 補助メモリ
	wcex.cbWndExtra = 0;						// 補助メモリ
	wcex.hInstance = m_nxhInstance;					// インスタンス
	wcex.hIcon = (HICON)LoadImage(			// アイコン
		NULL, MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
	wcex.hCursor = (HCURSOR)LoadImage(		// カーソル
		NULL, MAKEINTRESOURCE(IDC_ARROW),
		IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
	wcex.hbrBackground =						// 背景ブラシ
		(HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wcex.lpszMenuName = NULL;					// メニュー名
	wcex.lpszClassName = TEXT("NextWindow");	// クラス名
	wcex.hIconSm = (HICON)LoadImage(			// 小さいアイコン
		NULL, MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);


	if (RegisterClassEx(&wcex) == 0){
		return false;
	}

	HWND NextWindowhWnd = CreateWindow(
		TEXT("NextWindow"), // ウインドウクラス名
		TEXT("NextWindow"), // キャプション文字列
		WS_OVERLAPPEDWINDOW,	// ウインドウのスタイル
		CW_USEDEFAULT,	// 水平位置
		CW_USEDEFAULT,	// 垂直位置
		500,	// 幅
		500,	// 高さ
		NULL,	// 親ウインドウ
		NULL,	// ウインドウメニュー
		m_nxhInstance,	// インスタンスハンドル
		NULL);	// WM_CREATE情報

	if (NextWindowhWnd == NULL){
		return false;
	}

	m_nxhwnd = NextWindowhWnd;

	return true;

}

//ウィンドウ表示
void NextWindow::Show(HWND hwnd, int ncmd){

	ShowWindow(hwnd, ncmd);
	UpdateWindow(hwnd);
}



//ウィンドウプロシージャ
LRESULT CALLBACK NextWindow::Wndproc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){

	static RECT* rc = new RECT;
	static HDC* hdc = new HDC;
	static PAINTSTRUCT* ps = new PAINTSTRUCT;
	static COPYDATASTRUCT* cs = new COPYDATASTRUCT;
	static std::vector<LPWSTR>* StartWindowContents = new std::vector < LPWSTR >;

	switch (msg){

	case WM_DESTROY:
		::ShowWindow(hwnd, SW_HIDE);
		//::PostQuitMessage(0);
		break;

	case WM_PAINT:{

		if (::GetClientRect(hwnd, rc) == 0){
			::MessageBox(hwnd, TEXT("ウィンドウ描写エラー\n"), TEXT("ErrorInfo"), MB_OK);
			delete rc;
			delete hdc;
			delete ps;
			delete cs;

			::PostQuitMessage(0);
			return 0L;
		}

		*hdc = ::BeginPaint(hwnd, ps);

		rc->top = rc->top + 103;
		rc->left = rc->left + 100;
		::DrawText(*hdc, TEXT("映画タイトル："), -1, rc, DT_LEFT | DT_WORDBREAK);

		HWND RESULT_MovieTitle = CreateWindow(
			TEXT("EDIT"),
			StartWindowContents->at(0),
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
			240,
			100,
			200,
			25,
			hwnd,
			(HMENU)1,
			m_nxhInstance,
			NULL);

		rc->top = rc->top + 100;
		rc->left = rc->left + 35;
		::DrawText(*hdc, TEXT("レビュー："), -1, rc, DT_LEFT | DT_WORDBREAK);

		HWND RESULT_Review = CreateWindow(
			TEXT("EDIT"),
			StartWindowContents->at(1),
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
			240,
			200,
			200,
			25,
			hwnd,
			(HMENU)2,
			m_nxhInstance,
			NULL);

		rc->top = rc->top + 100;
		rc->left = rc->left + 35;
		::DrawText(*hdc, TEXT("メモ："), -1, rc, DT_LEFT | DT_WORDBREAK);
		
		HWND RESULT_Memo = CreateWindow(
			TEXT("EDIT"),
			StartWindowContents->at(2),
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
			240,
			300,
			200,
			25,
			hwnd,
			(HMENU)3,
			m_nxhInstance,
			NULL);

		rc->top = rc->top + 50;
		rc->left = rc->left - 10;
		::DrawText(*hdc, TEXT("以上の内容で登録しますか？"), -1, rc, DT_LEFT | DT_WORDBREAK);

		::EndPaint(hwnd, ps);

		HWND BT_YES = CreateWindow(
			TEXT("BUTTON"),
			TEXT("はい"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			160,
			400,
			80,
			25,
			hwnd,
			(HMENU)4,
			m_nxhInstance,
			NULL);

		HWND BT_NO = CreateWindow(
			TEXT("BUTTON"),
			TEXT("いいえ"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			270,
			400,
			80,
			25,
			hwnd,
			(HMENU)5,
			m_nxhInstance,
			NULL);

		break;

	}

	case WM_COMMAND:

		switch (LOWORD(wp)){

		case 4:

			//XMLファイルに書き込み

			break;

		case 5:
			::ShowWindow(hwnd, SW_HIDE);
			break;

		}

		break;

	case WM_CREATE:
		break;

	case WM_COPYDATA:{

		cs = (COPYDATASTRUCT*)lp;
	
		StartWindowContents = (std::vector<LPWSTR>*)cs->lpData;

		Show(hwnd, m_nxnCmdShow);

		break;
	}

	default:
		return ::DefWindowProc(hwnd, msg, wp, lp);
	}

	return 0L;
}
