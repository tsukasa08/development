#include "StartWindow.h"
#include "XML.h"
#include <vector>
#include <string>


//static�ϐ���`
HINSTANCE StartWindow::m_hInstance;

NextWindow* StartWindow::m_obj;
XMLWindow* StartWindow::m_xmlobj;
std::map<std::string, HWND> StartWindow::m_HandleList;

//�R���X�g���N�^
StartWindow::StartWindow()
{
}

//�R���X�g���N�^�i��������j
StartWindow::StartWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){

	m_hInstance = hInstance;
	m_hprevInstance = hPrevInstance;
	m_lpCmdLine = lpCmdLine;
	m_nCmdShow = nCmdShow;

	m_obj = new NextWindow(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	m_xmlobj = new XMLWindow(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}

//�f�X�g���N�^
StartWindow::~StartWindow()
{
	delete m_obj;
}

//StartWindow���C������
bool StartWindow::CreateWindowMain(){

	//�E�B���h�E�쐬
	if (!Create()){
		return false;
	}

	//�E�B���h�E�\��
	Show(m_hwnd, m_nCmdShow);


	return true;
}

//�E�B���h�E�쐬
bool StartWindow::Create(){

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);			// �\���̂̃T�C�Y
	wcex.style = CS_HREDRAW | CS_VREDRAW;		// �N���X�̃X�^�C��
	wcex.lpfnWndProc = Wndproc;				// �v���V�[�W����
	wcex.cbClsExtra = 0;						// �⏕������
	wcex.cbWndExtra = 0;						// �⏕������
	wcex.hInstance = m_hInstance;					// �C���X�^���X
	wcex.hIcon = (HICON)LoadImage(			// �A�C�R��
		NULL, MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
	wcex.hCursor = (HCURSOR)LoadImage(		// �J�[�\��
		NULL, MAKEINTRESOURCE(IDC_ARROW),
		IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
	wcex.hbrBackground =						// �w�i�u���V
		(HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wcex.lpszMenuName = NULL;					// ���j���[��
	wcex.lpszClassName = TEXT("StartWindow");	// �N���X��
	wcex.hIconSm = (HICON)LoadImage(			// �������A�C�R��
		NULL, MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);


	if (RegisterClassEx(&wcex) == 0){
		return false;
	}

	HWND StartWindowhWnd = CreateWindow(
		TEXT("StartWindow"), // �E�C���h�E�N���X��
		TEXT("StartWindow"), // �L���v�V����������
		WS_OVERLAPPED | WS_SYSMENU | WS_VSCROLL,	// �E�C���h�E�̃X�^�C��
		CW_USEDEFAULT,	// �����ʒu
		CW_USEDEFAULT,	// �����ʒu
		700,	// ��
		500,	// ����
		NULL,	// �e�E�C���h�E
		NULL,	// �E�C���h�E���j���[
		m_hInstance,	// �C���X�^���X�n���h��
		NULL);	// WM_CREATE���

	if (StartWindowhWnd == NULL){
		return false;
	}

	m_hwnd = StartWindowhWnd;

	return true;

}

//�E�B���h�E�\��
void StartWindow::Show(HWND hwnd, int ncmd){

	ShowWindow(hwnd, ncmd);
	UpdateWindow(hwnd);
}

//�E�B���h�E���C�A�E�g
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
		TEXT("������"),
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
		TEXT("�m��"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		350,
		330,
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

	HWND BT_Hyozi = CreateWindow(
		TEXT("BUTTON"),
		TEXT("�\��"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		230,
		330,
		100,
		30,
		hwnd,
		(HMENU)5,
		m_hInstance,
		NULL
	);

	if (!BT_Hyozi) {
		return false;
	}

	HWND BT_close = CreateWindow(
		TEXT("BUTTON"),
		TEXT("����"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		290,
		400,
		100,
		30,
		hwnd,
		(HMENU)6,
		m_hInstance,
		NULL
		);

	if (!BT_close){
		return false;
	}

	return true;

}

//�E�B���h�E�v���V�[�W��
LRESULT CALLBACK StartWindow::Wndproc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){

	static RECT *rc = new RECT;
	static HDC *hdc = new HDC;
	static PAINTSTRUCT *ps = new PAINTSTRUCT;
	static std::vector<LPWSTR> Contents;
	static int strsize[3];
	static SCROLLINFO scinfo;


	switch (msg){

	case WM_DESTROY:
		delete rc;
		delete hdc;
		delete ps;
		::PostQuitMessage(0);
		break;

	case WM_PAINT:
		if (::GetClientRect(hwnd, rc) == 0){
			::MessageBox(hwnd, TEXT("�E�B���h�E�`�ʃG���[\n"), TEXT("ErrorInfo"), MB_OK);
			::PostQuitMessage(0);
			return 0L;
		}

		*hdc = ::BeginPaint(hwnd, ps);

		::DrawText(*hdc, TEXT("\n�o�^/�\���E�B���h�E"), -1, rc, DT_CENTER | DT_WORDBREAK);
		::DrawText(*hdc, TEXT("\n\n\n\n�f��^�C�g��"), -1, rc, DT_CENTER | DT_WORDBREAK);
		::DrawText(*hdc, TEXT("\n\n\n\n\n\n\n\n���r���["), -1, rc, DT_CENTER | DT_WORDBREAK);
		::DrawText(*hdc, TEXT("\n\n\n\n\n\n\n\n\n\n\n\n\n����"), -1, rc, DT_CENTER | DT_WORDBREAK);

		::EndPaint(hwnd, ps);

		break;

	case WM_CREATE:

		if (!WindowLayout(hwnd)){
			::MessageBox(hwnd, TEXT("WindowLayout���\�b�h�G���["), TEXT("ErrorInfo"), MB_OK);
			return 0L;
		}

		scinfo.cbSize = sizeof(SCROLLINFO);
		scinfo.fMask = SIF_POS;
		scinfo.nMin = 0;
		scinfo.nMax = 1000;
		scinfo.nPage = 100;
		scinfo.nPos = 0;

		SetScrollInfo(hwnd, SB_VERT, &scinfo, TRUE);

		break;

	case WM_COMMAND:{
		switch (LOWORD(wp)){
		case 4:{

			strsize[0] = ::GetWindowTextLength(m_HandleList["MovieTitle"]);

			strsize[1] = ::GetWindowTextLength(m_HandleList["Review"]);

			strsize[2] = ::GetWindowTextLength(m_HandleList["Memo"]);

			if (strsize[0] == 0){
				MessageBox(hwnd, TEXT("�󔒂̓��͍��ڂ�����܂��B"), TEXT("information"), MB_OK);
				return ::DefWindowProc(hwnd, msg, wp, lp);
			}
			else if (strsize[1] == 0){
				MessageBox(hwnd, TEXT("�󔒂̓��͍��ڂ�����܂��B"), TEXT("information"), MB_OK);
				return ::DefWindowProc(hwnd, msg, wp, lp);
			}
			else if (strsize[2] == 0){
				MessageBox(hwnd, TEXT("�󔒂̓��͍��ڂ�����܂��B"), TEXT("information"), MB_OK);
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

		case 5: {

			if (!m_xmlobj->CreateWindowMain()) {
				PostQuitMessage(0);
				break;
			}

			return 0L;
		}

		case 6:
			PostQuitMessage(0);

			delete rc;
			delete hdc;
			delete ps;

			break;

		}

	case WM_VSCROLL:

		switch (LOWORD(wp)) {

		case SB_LINEUP: scinfo.nPos -= 16; break;

		case SB_LINEDOWN: scinfo.nPos += 16; break;

		case SB_PAGEUP: scinfo.nPos -= scinfo.nPage / 2; break;

		case SB_PAGEDOWN: scinfo.nPos += scinfo.nPage / 2; break;

		case SB_THUMBPOSITION:
		case SB_THUMBTRACK: scinfo.nPos = HIWORD(wp); break;

		}

		scinfo.nPos = max(scinfo.nMin, min(scinfo.nMax - (signed)scinfo.nPage, scinfo.nPos));

		SetScrollInfo(hwnd, SB_VERT, &scinfo, TRUE);
		InvalidateRect(hwnd, NULL, TRUE);
		UpdateWindow(hwnd);


		break;

		default:
			return ::DefWindowProc(hwnd, msg, wp, lp);
	}

	}

	return 0L;
}