#include "NextWindow.h"
#include <vector>

//static�ϐ���`
HINSTANCE NextWindow::m_nxhInstance;
int NextWindow::m_nxnCmdShow;

NextWindow::NextWindow()
{
}

//�R���X�g���N�^�i��������j
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


//StartWindow���C������
bool NextWindow::CreateWindowMain(){

	//�E�B���h�E�쐬
	//if (!Create()){
	//	return false;
	//}

	//�E�B���h�E�\��
	Show(m_nxhwnd, m_nxnCmdShow);


	return true;
}

//�E�B���h�E�쐬
bool NextWindow::Create(){

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);			// �\���̂̃T�C�Y
	wcex.style = CS_HREDRAW | CS_VREDRAW;		// �N���X�̃X�^�C��
	wcex.lpfnWndProc = Wndproc;				// �v���V�[�W����
	wcex.cbClsExtra = 0;						// �⏕������
	wcex.cbWndExtra = 0;						// �⏕������
	wcex.hInstance = m_nxhInstance;					// �C���X�^���X
	wcex.hIcon = (HICON)LoadImage(			// �A�C�R��
		NULL, MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
	wcex.hCursor = (HCURSOR)LoadImage(		// �J�[�\��
		NULL, MAKEINTRESOURCE(IDC_ARROW),
		IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
	wcex.hbrBackground =						// �w�i�u���V
		(HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wcex.lpszMenuName = NULL;					// ���j���[��
	wcex.lpszClassName = TEXT("NextWindow");	// �N���X��
	wcex.hIconSm = (HICON)LoadImage(			// �������A�C�R��
		NULL, MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);


	if (RegisterClassEx(&wcex) == 0){
		return false;
	}

	HWND NextWindowhWnd = CreateWindow(
		TEXT("NextWindow"), // �E�C���h�E�N���X��
		TEXT("NextWindow"), // �L���v�V����������
		WS_OVERLAPPEDWINDOW,	// �E�C���h�E�̃X�^�C��
		CW_USEDEFAULT,	// �����ʒu
		CW_USEDEFAULT,	// �����ʒu
		500,	// ��
		500,	// ����
		NULL,	// �e�E�C���h�E
		NULL,	// �E�C���h�E���j���[
		m_nxhInstance,	// �C���X�^���X�n���h��
		NULL);	// WM_CREATE���

	if (NextWindowhWnd == NULL){
		return false;
	}

	m_nxhwnd = NextWindowhWnd;

	return true;

}

//�E�B���h�E�\��
void NextWindow::Show(HWND hwnd, int ncmd){

	ShowWindow(hwnd, ncmd);
	UpdateWindow(hwnd);
}



//�E�B���h�E�v���V�[�W��
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
			::MessageBox(hwnd, TEXT("�E�B���h�E�`�ʃG���[\n"), TEXT("ErrorInfo"), MB_OK);
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
		::DrawText(*hdc, TEXT("�f��^�C�g���F"), -1, rc, DT_LEFT | DT_WORDBREAK);

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
		::DrawText(*hdc, TEXT("���r���[�F"), -1, rc, DT_LEFT | DT_WORDBREAK);

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
		::DrawText(*hdc, TEXT("�����F"), -1, rc, DT_LEFT | DT_WORDBREAK);
		
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
		::DrawText(*hdc, TEXT("�ȏ�̓��e�œo�^���܂����H"), -1, rc, DT_LEFT | DT_WORDBREAK);

		::EndPaint(hwnd, ps);

		HWND BT_YES = CreateWindow(
			TEXT("BUTTON"),
			TEXT("�͂�"),
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
			TEXT("������"),
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

			//XML�t�@�C���ɏ�������

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
