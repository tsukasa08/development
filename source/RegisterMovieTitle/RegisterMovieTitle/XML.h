#pragma once

#include <string>
#include <Windows.h>
#include <vector>
#include <atlbase.h>
#include <MsXml6.h>

#import "msxml6.dll" named_guids raw_interfaces_only

class XML
{
public:

	//�����o�֐�

	//�R���X�g���N�^
	XML();


	//�f�X�g���N�^
	~XML();

	//xml�t�@�C���ǂݍ���
	bool ReadXMLFile();

	//�G�������g�l�擾
	bool GetXmlValue(const CComBSTR& TagName);

	//�����o�ϐ�

	//xml�t�@�C���̐�΃p�X
	LPCTSTR m_filename;

	//XML�h�L�������g�I�u�W�F�N�g
	IXMLDOMDocumentPtr m_pXMLDOMDocument;

	//XML�t�@�C��<MovieTitle>�G�������g�l
	std::vector <CComBSTR> m_TitleValue;

	// XML�t�@�C��<Review>�G�������g�l
	std::vector <CComBSTR> m_ReviewValue;

	// XML�t�@�C��<Memo>�G�������g�l
	std::vector <CComBSTR> m_MemoValue;

	//�f�[�^��
	int m_XmlDataNum;


};

