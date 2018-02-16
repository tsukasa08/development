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

	//メンバ関数

	//コンストラクタ
	XML();


	//デストラクタ
	~XML();

	//xmlファイル読み込み
	bool ReadXMLFile();

	//エレメント値取得
	bool GetXmlValue(const CComBSTR& TagName);

	//メンバ変数

	//xmlファイルの絶対パス
	LPCTSTR m_filename;

	//XMLドキュメントオブジェクト
	IXMLDOMDocumentPtr m_pXMLDOMDocument;

	//XMLファイル<MovieTitle>エレメント値
	std::vector <CComBSTR> m_TitleValue;

	// XMLファイル<Review>エレメント値
	std::vector <CComBSTR> m_ReviewValue;

	// XMLファイル<Memo>エレメント値
	std::vector <CComBSTR> m_MemoValue;

	//データ量
	int m_XmlDataNum;


};

