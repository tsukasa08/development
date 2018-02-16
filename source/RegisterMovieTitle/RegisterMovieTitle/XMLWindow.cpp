#include "XMLWindow.h"

//static�ϐ���`
HINSTANCE XMLWindow::m_xmlhInstance;

XMLWindow::XMLWindow()
{
}


XMLWindow::~XMLWindow()
{
}

//�R���X�g���N�^�i��������j
XMLWindow::XMLWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	m_xmlhInstance = hInstance;
	m_hprevInstance = hPrevInstance;
	m_lpCmdLine = lpCmdLine;
	m_nCmdShow = nCmdShow;
}

//StartWindow���C������
bool XMLWindow::CreateWindowMain() {

	//�E�B���h�E�쐬
	if (!Create()) {
		return false;
	}

	//�E�B���h�E�\��
	Show(m_xmlhwnd, m_nCmdShow);


	return true;
}

//�E�B���h�E�쐬
bool XMLWindow::Create() {

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);			// �\���̂̃T�C�Y
	wcex.style = CS_HREDRAW | CS_VREDRAW;		// �N���X�̃X�^�C��
	wcex.lpfnWndProc = Wndproc;				// �v���V�[�W����
	wcex.cbClsExtra = 0;						// �⏕������
	wcex.cbWndExtra = 0;						// �⏕������
	wcex.hInstance = m_xmlhInstance;					// �C���X�^���X
	wcex.hIcon = (HICON)LoadImage(			// �A�C�R��
		NULL, MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
	wcex.hCursor = (HCURSOR)LoadImage(		// �J�[�\��
		NULL, MAKEINTRESOURCE(IDC_ARROW),
		IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED);
	wcex.hbrBackground =						// �w�i�u���V
		(HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.lpszMenuName = NULL;					// ���j���[��
	wcex.lpszClassName = TEXT("XMLWindow");	// �N���X��
	wcex.hIconSm = (HICON)LoadImage(			// �������A�C�R��
		NULL, MAKEINTRESOURCE(IDI_APPLICATION),
		IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_SHARED);


	if (RegisterClassEx(&wcex) == 0) {
		return false;
	}

	HWND XMLWindowhWnd = CreateWindow(
		TEXT("XMLWindow"), // �E�C���h�E�N���X��
		TEXT("XMLWindow"), // �L���v�V����������
		WS_OVERLAPPEDWINDOW | WS_VSCROLL,	// �E�C���h�E�̃X�^�C��
		CW_USEDEFAULT,	// �����ʒu
		CW_USEDEFAULT,	// �����ʒu
		700,	// ��
		500,	// ����
		NULL,	// �e�E�C���h�E
		NULL,	// �E�C���h�E���j���[
		m_xmlhInstance,	// �C���X�^���X�n���h��
		NULL);	// WM_CREATE���

	if (XMLWindowhWnd == NULL) {
		return false;
	}

	m_xmlhwnd = XMLWindowhWnd;

	return true;

}

//�E�B���h�E�\��
void XMLWindow::Show(HWND hwnd, int ncmd) {

	ShowWindow(hwnd, ncmd);
	UpdateWindow(hwnd);
}

//XML�f�[�^�\���֐�
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
			::MessageBox(hwnd, TEXT("�E�B���h�E�`�ʃG���[\n"), TEXT("ErrorInfo"), MB_OK);

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

		::DrawText(*hdc, TEXT("�f��^�C�g��"), -1, rc, DT_CENTER | DT_WORDBREAK);
		
		rc->top += 50;
		for (int i = 0; i < obj->m_XmlDataNum; i++) {
			::DrawText(*hdc, obj->m_TitleValue[i], -1, rc, DT_CENTER | DT_WORDBREAK);
			rc->top += 30;
		}

		rc->left = Defleft;
		rc->top = Deftop;
		::DrawText(*hdc, TEXT("���r���["), -1, rc, DT_CENTER | DT_WORDBREAK);

		rc->top += 50;
		for (int i = 0; i < obj->m_XmlDataNum; i++) {
			::DrawText(*hdc, obj->m_ReviewValue[i], -1, rc, DT_CENTER | DT_WORDBREAK);
			rc->top += 30;
		}

		rc->left = Defleft;
		rc->left += 400;
		rc->top = Deftop;
		::DrawText(*hdc, TEXT("����"), -1, rc, DT_CENTER | DT_WORDBREAK);
		rc->top += 50;
		for (int i = 0; i < obj->m_XmlDataNum; i++) {
			::DrawText(*hdc, obj->m_MemoValue[i], -1, rc, DT_CENTER | DT_WORDBREAK);
			rc->top += 30;
		}

		::EndPaint(hwnd, ps);

		

		break;

	}

	case WM_CREATE:


		//�X�N���[���o�[�����ݒ�
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