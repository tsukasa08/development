#include "StartWindow.h"
#include <vector>
#include <string>

//static変数定義
HINSTANCE StartWindow::m_hInstance;

NextWindow* StartWindow::m_obj;
std::map<std::string, HWND> StartWindow::m_HandleList;

//コンストラクタ
StartWindow::StartWindow()
{
}

//コンストラクタ（引数あり）
StartWindow::StartWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){

	m_hInstance = hInstance;
	m_hprevInstance = hPrevInstance;
	m_lpCmdLine = lpCmdLine;
	m_nCmdShow = nCmdShow;

	m_obj = new NextWindow(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}

//デストラクタ
StartWindow::~StartWindow()
{
	delete m_obj;
}

//StartWindowメイン処理
bool StartWindow::CreateWindowMain(){

	//ウィンドウ作成
	if (!Create()){
		return false;
	}

	//ウィンドウ表示
	Show(m_hwnd, m_nCmdShow);


	return true;
}

//ウィンドウ作成
bool StartWindow::Create(){

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);			// 構造体のサイズ
	wcex.style = CS_HREDRAW | CS_VREDRAW;		// クラスのスタイル
	wcex.lpfnWndProc = Wndproc;				// プロシージャ名
	wcex.cbClsExtra = 0;						// 補助メモリ
	wcex.cbWndExtra = 0;						// 補助メモリ
	wcex.hInstance = m_hInstance;					// インスタンス
	wcex.hIcon = (HICON)LoadImage(			// アイコン
		NULL, MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
	wcex.hCursor = (HCURSOR)LoadImage(		// カーソル
		NULL, MAKEINTRESOURCE(IDC_ARROW),
		IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
	wcex.hbrBackground =						// 背景ブラシ
		(HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wcex.lpszMenuName = NULL;					// メニュー名
	wcex.lpszClassName = TEXT("StartWindow");	// クラス名
	wcex.hIconSm = (HICON)LoadImage(			// 小さいアイコン
		NULL, MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);


	if (RegisterClassEx(&wcex) == 0){
		return false;
	}

	HWND StartWindowhWnd = CreateWindow(
		TEXT("StartWindow"), // ウインドウクラス名
		TEXT("StartWindow"), // キャプション文字列
		WS_OVERLAPPED | WS_SYSMENU,	// ウインドウのスタイル
		CW_USEDEFAULT,	// 水平位置
		CW_USEDEFAULT,	// 垂直位置
		700,	// 幅
		500,	// 高さ
		NULL,	// 親ウインドウ
		NULL,	// ウインドウメニュー
		m_hInstance,	// インスタンスハンドル
		NULL);	// WM_CREATE情報

	if (StartWindowhWnd == NULL){
		return false;
	}

	m_hwnd = StartWindowhWnd;

	return true;

}

//ウィンドウ表示
void StartWindow::Show(HWND hwnd, int ncmd){

	ShowWindow(hwnd, ncmd);
	UpdateWindow(hwnd);
}

//ウィンドウレイアウト
bool StartWindow::WindowLayout(HWND hwnd){

	HWND TB_MovieTitle = CreateWindow(
		TEXT("EDIT"),
		NULL,
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
		240,
		100,
		200,
		25,
		hwnd,
		(HMENU)1,
		m_hInstance,
		NULL);

	if (!TB_MovieTitle){
		return false;
	}

	m_HandleList["MovieTitle"] = TB_MovieTitle;


	HWND TB_Review = CreateWindow(
		TEXT("EDIT"),
		TEXT("☆☆☆"),
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
		240,
		180,
		200,
		25,
		hwnd,
		(HMENU)2,
		m_hInstance,
		NULL);

	if (!TB_Review){
		return false;
	}

	m_HandleList["Review"] = TB_Review;

	HWND TB_Memo = CreateWindow(
		TEXT("EDIT"),
		NULL,
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
		240,
		260,
		200,
		25,
		hwnd,
		(HMENU)3,
		m_hInstance,
		NULL);

	if (!TB_Memo){
		return false;
	}

	m_HandleList["Memo"] = TB_Memo;

	HWND BT_Kakutei = CreateWindow(
		TEXT("BUTTON"),
		TEXT("確定"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		350,
		350,
		100,
		30,
		hwnd,
		(HMENU)4,
		m_hInstance,
		NULL
		);

	if (!BT_Kakutei){
		return false;
	}

	HWND BT_close = CreateWindow(
		TEXT("BUTTON"),
		TEXT("閉じる"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		220,
		350,
		100,
		30,
		hwnd,
		(HMENU)5,
		m_hInstance,
		NULL
		);

	if (!BT_close){
		return false;
	}

	return true;

}

//ウィンドウプロシージャ
LRESULT CALLBACK StartWindow::Wndproc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){

	static RECT *rc = new RECT;
	static HDC *hdc = new HDC;
	static PAINTSTRUCT *ps = new PAINTSTRUCT;
	static std::vector<LPWSTR> Contents;
	static int strsize[3];


	switch (msg){

	case WM_DESTROY:
		delete rc;
		delete hdc;
		delete ps;
		::PostQuitMessage(0);
		break;

	case WM_PAINT:
		if (::GetClientRect(hwnd, rc) == 0){
			::MessageBox(hwnd, TEXT("ウィンドウ描写エラー\n"), TEXT("ErrorInfo"), MB_OK);
			::PostQuitMessage(0);
			return 0L;
		}

		*hdc = ::BeginPaint(hwnd, ps);

		::DrawText(*hdc, TEXT("\n登録ウィンドウ"), -1, rc, DT_CENTER | DT_WORDBREAK);
		::DrawText(*hdc, TEXT("\n\n\n\n映画タイトル"), -1, rc, DT_CENTER | DT_WORDBREAK);
		::DrawText(*hdc, TEXT("\n\n\n\n\n\n\n\nレビュー"), -1, rc, DT_CENTER | DT_WORDBREAK);
		::DrawText(*hdc, TEXT("\n\n\n\n\n\n\n\n\n\n\n\n\nメモ"), -1, rc, DT_CENTER | DT_WORDBREAK);

		::EndPaint(hwnd, ps);

		break;

	case WM_CREATE:

		if (!WindowLayout(hwnd)){
			::MessageBox(hwnd, TEXT("WindowLayoutメソッドエラー"), TEXT("ErrorInfo"), MB_OK);
			return 0L;
		}
		break;

	case WM_COMMAND:{
		switch (LOWORD(wp)){
		case 4:{

			strsize[0] = ::GetWindowTextLength(m_HandleList["MovieTitle"]);

			strsize[1] = ::GetWindowTextLength(m_HandleList["Review"]);

			strsize[2] = ::GetWindowTextLength(m_HandleList["Memo"]);

			if (strsize[0] == 0){
				MessageBox(hwnd, TEXT("空白の入力項目があります。"), TEXT("information"), MB_OK);
				return ::DefWindowProc(hwnd, msg, wp, lp);
			}
			else if (strsize[1] == 0){
				MessageBox(hwnd, TEXT("空白の入力項目があります。"), TEXT("information"), MB_OK);
				return ::DefWindowProc(hwnd, msg, wp, lp);
			}
			else if (strsize[2] == 0){
				MessageBox(hwnd, TEXT("空白の入力項目があります。"), TEXT("information"), MB_OK);
				return ::DefWindowProc(hwnd, msg, wp, lp);
			}


			LPWSTR tmpstr0 = new wchar_t[strsize[0] + 2];
			LPWSTR tmpstr1 = new wchar_t[strsize[1] + 2];
			LPWSTR tmpstr2 = new wchar_t[strsize[2] + 2];


			::GetWindowText(m_HandleList["MovieTitle"], tmpstr0, strsize[0] + 2);
			::GetWindowText(m_HandleList["Review"], tmpstr1, strsize[1] + 2);
			::GetWindowText(m_HandleList["Memo"], tmpstr2, strsize[2] + 2);

			Contents.push_back(tmpstr0);
			Contents.push_back(tmpstr1);
			Contents.push_back(tmpstr2);

			if (!m_obj->Create()){
				PostQuitMessage(0);
				break;
			}

			COPYDATASTRUCT cs;
			cs.dwData = 1;
			cs.cbData = sizeof(std::vector<LPWSTR>);
			cs.lpData = static_cast<LPVOID>(&Contents);

			::SendMessage(m_obj->m_nxhwnd, WM_COPYDATA, reinterpret_cast<WPARAM>(hwnd), reinterpret_cast<LPARAM>(&cs));

			return 0L;

		}

		case 5:
			PostQuitMessage(0);

			delete rc;
			delete hdc;
			delete ps;

			break;

		}

		default:
			return ::DefWindowProc(hwnd, msg, wp, lp);
	}

	}

	return 0L;
}