#include <Windows.h>
#include "StartWindow.h"

//�e�X�g�p
#include "XML.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){

	//StartWindow�C���X�^���X��
	StartWindow *obj = new StartWindow(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	if (!obj->CreateWindowMain()){
		return -1;
	}

	//���b�Z�[�W���[�v
	int result;
	MSG msg;

	result = GetMessage(&msg, NULL, 0, 0);

	while (result){

		result = GetMessage(&msg, NULL, 0, 0);

		if (result == -1){
			break;
		}
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}

	delete obj;

	return 0;
}