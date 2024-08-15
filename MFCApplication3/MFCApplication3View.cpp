
// MFCApplication3View.cpp: CMFCApplication3View 類別的實作
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以定義在實作預覽、縮圖和搜尋篩選條件處理常式的
// ATL 專案中，並允許與該專案共用文件程式碼。
#ifndef SHARED_HANDLERS
#include "MFCApplication3.h"
#endif

#include "MFCApplication3Doc.h"
#include "MFCApplication3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <fstream>

#include <nlohmann/json.hpp>
using nlohmann::json;

#include "UserInterface.h"
UserInterface myInterface;

// CMFCApplication3View

IMPLEMENT_DYNCREATE(CMFCApplication3View, CFormView)

BEGIN_MESSAGE_MAP(CMFCApplication3View, CFormView)
	// 標準列印命令
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFormView::OnFilePrintPreview)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication3View::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &CMFCApplication3View::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CMFCApplication3View::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CMFCApplication3View::OnEnChangeEdit3)
END_MESSAGE_MAP()

// CMFCApplication3View 建構/解構

CMFCApplication3View::CMFCApplication3View() noexcept
	: CFormView(IDD_MFCAPPLICATION3_FORM)
{
	// TODO: 在此加入建構程式碼

}

CMFCApplication3View::~CMFCApplication3View()
{
}

void CMFCApplication3View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);



}

BOOL CMFCApplication3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此經由修改 CREATESTRUCT cs 
	// 達到修改視窗類別或樣式的目的

	return CFormView::PreCreateWindow(cs);
}

void CMFCApplication3View::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	//Read from data.json, and write it to 3 edit box
	std::ifstream f("data.json");
	if (!f.is_open()) {
		//basicFileLogger->basicFileLogger->warn("data.json doesn't exist, may cause by first run.");
		return;
	}
	json jsonObj;
	f >> jsonObj;
	f.close();
	jsonObj.dump();
	// If use get<std::string>(), "dataFile": "1" -> 1, which is we want.
	// If use dump(), "dataFile": "1" -> "1", which is not correct. 
	CString dataFile(jsonObj["dataFile"].get<std::string>().c_str());
    CString imgDir(jsonObj["imgDir"].get<std::string>().c_str());
	CString searchDir(jsonObj["searchDir"].get<std::string>().c_str());
	GetDlgItem(IDC_EDIT1)->SetWindowText(dataFile);
	GetDlgItem(IDC_EDIT2)->SetWindowText(imgDir);
	GetDlgItem(IDC_EDIT3)->SetWindowText(searchDir);

}


// CMFCApplication3View 列印

BOOL CMFCApplication3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 預設的準備列印程式碼
	return DoPreparePrinting(pInfo);
}

void CMFCApplication3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 加入列印前額外的初始設定
}

void CMFCApplication3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 加入列印後的清除程式碼
}

void CMFCApplication3View::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: 在此加入自訂的列印程式碼
}


// CMFCApplication3View 診斷

#ifdef _DEBUG
void CMFCApplication3View::AssertValid() const
{
	CFormView::AssertValid();
}

void CMFCApplication3View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMFCApplication3Doc* CMFCApplication3View::GetDocument() const // 內嵌非偵錯版本
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication3Doc)));
	return (CMFCApplication3Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication3View 訊息處理常式


void CMFCApplication3View::OnBnClickedButton1()
{
	myInterface.StartProcess();
}


void CMFCApplication3View::OnEnChangeEdit1()
{
	CString strText;
	GetDlgItem(IDC_EDIT1)->GetWindowText(strText);
	myInterface.m_dataFile = strText;
}


void CMFCApplication3View::OnEnChangeEdit2()
{
	CString strText;
	GetDlgItem(IDC_EDIT2)->GetWindowText(strText);
	myInterface.m_imgDir = strText;
}


void CMFCApplication3View::OnEnChangeEdit3()
{
	CString strText;
	GetDlgItem(IDC_EDIT3)->GetWindowText(strText);
	myInterface.m_searchDir = strText;
}
