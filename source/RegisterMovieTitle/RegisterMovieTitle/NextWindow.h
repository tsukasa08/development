#pragma once

#include <Windows.h>

class NextWindow
{
public:

	//�����o�֐�

	NextWindow();

	~NextWindow();

	//�R���X�g���N�^�i��������j
	NextWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

	//CreateWindow���C������
	bool CreateWindowMain();

	//�E�B���h�E�쐬
	bool Create();

	//�E�B���h�E�\��
	static void Show(HWND hwnd, int ncmd);

	//�E�B���h�E�v���V�[�W��
	static LRESULT CALLBACK Wndproc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);





	//�����o�ϐ�

	static HINSTANCE m_nxhInstance;

	HINSTANCE m_nxhprevInstance;

	LPSTR m_nxlpCmdLine;

	static int m_nxnCmdShow;

	//�e�E�B���h�E�n���h��
	HWND m_nxhwnd;
};

