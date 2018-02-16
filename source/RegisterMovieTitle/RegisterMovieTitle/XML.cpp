#include "XML.h"



//#pragma comment (lib, "msxml6.lib")

//コンストラクタ
XML::XML()
{
	m_filename = new wchar_t[200];
	m_filename = L"C:\\Users\\Tsukasa\\Desktop\\開発ソース\\development\\source\\RegisterMovieTitle\\xml\\MovieList.xml";
	//m_filename = L"MovieList.xml";
}

//デストラクタ
XML::~XML()
{
}

bool XML::ReadXMLFile(){

	HRESULT hResult;

	// DOMドキュメントの作成
	
	hResult = m_pXMLDOMDocument.CreateInstance(CLSID_DOMDocument);
	if (hResult != S_OK)
	{
		return false;
	}

	// XMLファイル読み込み
	m_pXMLDOMDocument->put_async(VARIANT_FALSE); // load関数がロードを完了するまで待つようにする。

	HRESULT readresult;
	VARIANT_BOOL varbResult;

	readresult = m_pXMLDOMDocument->load(CComVariant(m_filename), &varbResult);

	if (!varbResult || readresult != S_OK)
	{
		return false;
	}

	if (!GetXmlValue(TEXT("title"))) {
		return false;
	}

	if (!GetXmlValue(TEXT("review"))) {
		return false;
	}

	if (!GetXmlValue(TEXT("memo"))) {
		return false;
	}

	return true;
}

//エレメント値取得
bool XML::GetXmlValue(const CComBSTR& TagName) {

	HRESULT TagNamehresult;
	IXMLDOMNodeListPtr pXMLDOMNodeList = nullptr;

	TagNamehresult = m_pXMLDOMDocument->getElementsByTagName(TagName, &pXMLDOMNodeList);


	if (TagNamehresult != S_OK || pXMLDOMNodeList == nullptr) {
		return false;
	}

	long nodenum = 0;
	HRESULT nodenumresult;

	nodenumresult = pXMLDOMNodeList->get_length(&nodenum);

	if (nodenumresult != S_OK) {
		return false;
	}

	m_XmlDataNum = nodenum;

	long l;
	for (l = 0; l < nodenum; l++) {
		HRESULT NodeListResult;
		IXMLDOMNodePtr pXMLDOMNode = NULL;

		NodeListResult = pXMLDOMNodeList->get_item(l, &pXMLDOMNode);

		if (NodeListResult != S_OK) {
			return false;
		}

		HRESULT TypeResult;
		DOMNodeType eNodeType;
		TypeResult = pXMLDOMNode->get_nodeType(&eNodeType);

		if (TypeResult != S_OK) {
			return false;
		}
		else if (eNodeType != NODE_ELEMENT) {
			return false;
		}


		IXMLDOMElementPtr pXMLDOMElement = NULL;

		pXMLDOMNode->QueryInterface(IID_IXMLDOMElement, (void**)&pXMLDOMElement);

		HRESULT TextResult;
		static std::vector<CComBSTR> tmp;
		tmp.push_back("");

		TextResult = pXMLDOMElement->get_text(&tmp.at(l));

		if (TextResult != S_OK) {
			return false;
		}

		if (TagName == TEXT("title")) {
			if (l == 0) {
				m_TitleValue.clear();
			}
			m_TitleValue.push_back(tmp.at(l));
		}
		else if (TagName == TEXT("review")) {
			if (l == 0) {
				m_ReviewValue.clear();
			}
			m_ReviewValue.push_back(tmp.at(l));
		}
		else if (TagName == TEXT("memo")) {
			if (l == 0) {
				m_MemoValue.clear();
			}
			m_MemoValue.push_back(tmp.at(l));
		}

	}

	return true;
}