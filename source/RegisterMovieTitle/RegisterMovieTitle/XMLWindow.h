#pragma once

#include <Windows.h>
#include "XML.h"

class XMLWindow
{
public:
	XMLWindow();
	~XMLWindow();

	//�R���X�g���N�^�i��������j
	XMLWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);


	//CreateWindow���C������
	bool CreateWindowMain();

	//�E�B���h�E�쐬
	bool Create();

	//�E�B���h�E�\��
	void Show(HWND hwnd, int ncmd);

	//XML�t�@�C���f�[�^�\��
	static bool ShowXMLData(XML* obj);

	//�E�B���h�E�v���V�[�W��
	static LRESULT CALLBACK Wndproc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

	//�e�E�B���h�E�n���h��
	HWND m_xmlhwnd;

	static HINSTANCE m_xmlhInstance;

	HINSTANCE m_hprevInstance;

	LPSTR m_lpCmdLine;

	int m_nCmdShow;
};

