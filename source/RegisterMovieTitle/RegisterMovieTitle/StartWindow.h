#pragma once

#include <Windows.h>
#include <map>

#include "NextWindow.h"
#include "XMLWindow.h"

//StartWindow�N���X
//StartWindow��\��

class StartWindow
{
public:

	//�����o�֐�

	//�R���X�g���N�^
	StartWindow();

	//�R���X�g���N�^�i��������j
	StartWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

	//�f�X�g���N�^
	~StartWindow();

	//CreateWindow���C������
	bool CreateWindowMain();

	//�E�B���h�E�쐬
	bool Create();

	//�E�B���h�E�\��
	void Show(HWND hwnd, int ncmd);

	//�E�B���h�E���C�A�E�g�i�e�L�X�g�{�b�N�X��{�^���̍쐬�j
	static bool WindowLayout(HWND hwnd);

	//�E�B���h�E�v���V�[�W��
	static LRESULT CALLBACK Wndproc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);





	//�����o�ϐ�

	static HINSTANCE m_hInstance;

	HINSTANCE m_hprevInstance;

	LPSTR m_lpCmdLine;

	int m_nCmdShow;

	//�e�E�B���h�E�n���h��
	HWND m_hwnd;

	//�m�F��ʃN���X�̃I�u�W�F�N�g
	static NextWindow *m_obj;

	//XML�E�B���h�E�̃I�u�W�F�N�g
	static XMLWindow *m_xmlobj;

	//�e�E�B���h�E�ɑ�����e�L�X�g�{�b�N�X��{�^���̃E�B���h�E�n���h���̃��X�g
	static std::map<std::string, HWND> m_HandleList;
};

