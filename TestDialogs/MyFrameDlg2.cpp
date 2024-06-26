// MyFrameDlg2.cpp : implementation file
// DEMO Dialog for StyleFramework
//
#include "stdafx.h"
#include "MyFrame.h"
#include "MyFrameDlg2.h"
#include "StyleMessageBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMyFrameDlg dialog

MyFrameDlg2::MyFrameDlg2(CWnd* pParent /*=NULL*/)
	          :StyleDialog(IDD, pParent,true,true)
            ,m_error(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

MyFrameDlg2::~MyFrameDlg2()
{
}

void MyFrameDlg2::DoDataExchange(CDataExchange* pDX)
{
	StyleDialog::DoDataExchange(pDX);
  DDX_Control(pDX,IDC_EDIT1,    m_editString1, m_string1);
  DDX_Control(pDX,IDC_EDIT2,    m_editString2, m_string2);
  DDX_Control(pDX,IDC_COMBO_1,  m_combo_1);
  DDX_Control(pDX,IDC_COMBO_2,  m_combo_2);
  DDX_Control(pDX,IDC_COMBO_3,  m_combo_3);
  DDX_Control(pDX,IDC_CHECK1,   m_check1);
  DDX_Control(pDX,IDC_CHECK2,   m_check2);
  DDX_Control(pDX,IDC_CHECK3,   m_check3);
  DDX_Control(pDX,IDC_SPIN1,    m_spin1,&m_editString1);
  DDX_Control(pDX,IDC_SPIN2,    m_spin2,&m_editString2);
  DDX_Control(pDX,IDC_ERROR,    m_buttonError);
  DDX_Control(pDX,IDC_HYPERLINK,m_visitEdwig);

  DDX_Control(pDX,IDC_ST_COLOR, m_staticColor);
  DDX_Control(pDX,IDC_ST_MULTI, m_staticMulti);
  DDX_Control(pDX,IDC_ST_ENAB,  m_staticEnabled);
  DDX_Control(pDX,IDC_ST_NUM10, m_staticNumber10);
  DDX_Control(pDX,IDC_ST_NUM20, m_staticNumber20);
  DDX_Control(pDX,IDC_ST_TEST,  m_staticTest);

  DDX_Control(pDX,IDOK,         m_buttonOK);
  DDX_Control(pDX,IDCANCEL,     m_buttonCancel);

  DDV_StyleMinMaxInt(pDX,IDC_EDIT1,m_string1,0,10);
  DDV_StyleMinMaxInt(pDX,IDC_EDIT2,m_string2,0,20);
}

BEGIN_MESSAGE_MAP(MyFrameDlg2, StyleDialog)
  ON_WM_PAINT()
  ON_WM_QUERYDRAGICON()
  ON_CBN_SELENDOK(IDC_COMBO_1, OnCbnCloseupCombo1)
  ON_CBN_SELENDOK(IDC_COMBO_2, OnCbnCloseupCombo2)
  ON_CBN_SELENDOK(IDC_COMBO_3, OnCbnCloseupCombo3)
  ON_BN_CLICKED  (IDC_CHECK1,  OnBnClickedCheck1)
  ON_BN_CLICKED  (IDC_CHECK2,  OnBnClickedCheck2)
  ON_BN_CLICKED  (IDC_CHECK3,  OnBnClickedCheck3)
  ON_EN_KILLFOCUS(IDC_EDIT1,   OnEnChangeEdit1)
  ON_EN_KILLFOCUS(IDC_EDIT2,   OnEnChangeEdit2)
  ON_BN_CLICKED  (IDC_ERROR,   OnBnClickedError)
  ON_NOTIFY(UDN_DELTAPOS,IDC_SPIN2,OnDeltaposSpin2)
END_MESSAGE_MAP()

// CMyFrameDlg message handlers

BOOL MyFrameDlg2::OnInitDialog()
{
  StyleDialog::OnInitDialog();
  SetWindowText(_T("Style dialog"));
  ShowMinMaxButton();
  SetAboutBoxAndIcon(IDM_ABOUTBOX,IDS_ABOUTBOX);

  RegisterTooltips();

  // Set the default button
  m_buttonOK.SetDefaultButton(true);
  m_buttonOK.SetStyle(_T("ok"));
  m_buttonCancel.SetStyle(_T("can"));
  m_check1.SetCheck(true);
  m_check2.SetCheck(true);
  m_check3.SetCheck(true);

  FillCombo1();
  FillCombo2();
  FillCombo3();
  SetSpinButtons();

  m_visitEdwig.SetURL(_T("https://github.com/edwig"));

  // Trigger SetupDynamicLayout
  SetCanResize();

  UpdateData(FALSE);
  
  return InitFirstFocus();
}

// Triggered by SetCanResize
void
MyFrameDlg2::SetupDynamicLayout()
{
  // See to it that we get a manager;
  StyleDialog::SetupDynamicLayout();

  auto manager = GetDynamicLayout();
  if(manager != nullptr)
  {
    HWND spin1 = m_spin1.GetSafeHwnd();
    HWND spin2 = m_spin2.GetSafeHwnd();
    manager->AddItem(IDC_COMBO_1,  CMFCDynamicLayout::MoveNone(),                         CMFCDynamicLayout::SizeHorizontal(100));
    manager->AddItem(IDC_COMBO_2,  CMFCDynamicLayout::MoveNone(),                         CMFCDynamicLayout::SizeHorizontal(100));
    manager->AddItem(IDC_COMBO_3,  CMFCDynamicLayout::MoveNone(),                         CMFCDynamicLayout::SizeHorizontal(100));
    manager->AddItem(IDC_EDIT1,    CMFCDynamicLayout::MoveNone(),                         CMFCDynamicLayout::SizeHorizontal(50));
    manager->AddItem(spin1,        CMFCDynamicLayout::MoveHorizontal(50),                 CMFCDynamicLayout::SizeNone());
    manager->AddItem(IDC_EDIT2,    CMFCDynamicLayout::MoveNone(),                         CMFCDynamicLayout::SizeHorizontal(50));
    manager->AddItem(spin2,        CMFCDynamicLayout::MoveHorizontal(50),                 CMFCDynamicLayout::SizeNone());
    manager->AddItem(IDC_ERROR,    CMFCDynamicLayout::MoveHorizontal(100),                CMFCDynamicLayout::SizeNone());
    manager->AddItem(IDOK,         CMFCDynamicLayout::MoveHorizontalAndVertical(100,100), CMFCDynamicLayout::SizeNone());
    manager->AddItem(IDCANCEL,     CMFCDynamicLayout::MoveHorizontalAndVertical(100,100), CMFCDynamicLayout::SizeNone());
  }
}

void 
MyFrameDlg2::FillCombo1()
{
  m_combo_1.AddString(_T("Lime"));
  m_combo_1.AddString(_T("Skyblue"));
  m_combo_1.AddString(_T("Purple"));
  m_combo_1.AddString(_T("Mustard"));
  m_combo_1.AddString(_T("Moderate gray"));
  m_combo_1.AddString(_T("Pure gray"));
  m_combo_1.AddString(_T("Black & White"));
  m_combo_1.AddString(_T("Dark Theme"));
}

void 
MyFrameDlg2::FillCombo2()
{
  for (int i = 0; i < 5; ++i)
  {
    for(int j = 0; j < 5; ++j)
    {
      CString text;
      for(int num = 0;num <= i;++num)
      {
        text += (char)('A' + j);
      }
      m_combo_2.AddString(text);
    }
  }
}

void
MyFrameDlg2::FillCombo3()
{
  for(int i = 0; i < 5; ++i)
  {
    for(int j = 0; j < 5; ++j)
    {
      CString text;
      for(int num = 5;num > i;--num)
      {
        text += (char)('A' + j);
      }
      m_combo_3.AddString(text);
    }
  }
}

void 
MyFrameDlg2::SetSpinButtons()
{
  m_spin1.SetBase(10);
  m_spin1.SetRange(0,10);

  m_spin2.SetBase(10);
  m_spin2.SetRange(0, 20);
}

void
MyFrameDlg2::RegisterTooltips()
{
  EnableToolTips();

  RegisterTooltip(IDC_SPIN1,    _T("Change the number"));
  RegisterTooltip(m_editString1,_T("This is a tooltip for the first edit field"));
  RegisterTooltip(m_combo_1,    _T("Choose your color style here"));
}

// If you add a minimize button to your dialog, you will need the code below
// to draw the icon.  For MFC applications using the document/view model,
// this is automatically done for you by the framework.

void 
MyFrameDlg2::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		StyleDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR 
MyFrameDlg2::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void
MyFrameDlg2::OnCbnCloseupCombo1()
{
  int sel = m_combo_1.GetCurSel();
  if(sel >= 0)
  {
    CString text;
    m_combo_1.GetLBText(sel,text);
    CString message(_T("Your choice was: "));
    message += text;

    StyleMessageBox(this,message,_T("Info"),MB_OK | MB_ICONINFORMATION);
    SetTheme((ThemeColor::Themes)sel);
    Invalidate();

    ReDrawFrame();
  }
}

void
MyFrameDlg2::OnCbnCloseupCombo2()
{
  CString selection;
  m_combo_2.GetWindowText(selection);
  StyleMessageBox(this,selection,_T("Your choice"),MB_OK);

  selection = _T("All numbers: ");
  for(int index = 0; index < m_combo_2.GetCount(); ++index)
  {
    if(m_combo_2.GetMultiSelection(index))
    {
      CString sel;
      sel.Format(_T("%d "), index);
      selection += sel;
    }
  }
  StyleMessageBox(this,selection,_T("Numbers"),MB_OK);
}

void
MyFrameDlg2::OnBnClickedCheck1()
{
  // Flip window-enabled
  BOOL enab = m_combo_3.IsWindowEnabled();
  m_combo_3.EnableWindow(!enab);
}

void
MyFrameDlg2::OnCbnCloseupCombo3()
{

}

void
MyFrameDlg2::OnBnClickedCheck2()
{
  // Flip window-enabled
  BOOL enab = m_editString1.IsWindowEnabled();
  m_editString1.EnableWindow(!enab);
  m_spin1.EnableWindow(!enab);
}

void
MyFrameDlg2::OnEnChangeEdit1()
{
  UpdateData();
}

void
MyFrameDlg2::OnBnClickedCheck3()
{
  // Flip window-enabled
  BOOL enab = m_editString2.IsWindowEnabled();
  m_editString2.EnableWindow(!enab);
  m_spin2.EnableWindow(!enab);
}

void
MyFrameDlg2::OnEnChangeEdit2()
{
  UpdateData();
}

// No auto-buddy. We must do it ourselves!
void 
MyFrameDlg2::OnDeltaposSpin2(NMHDR* pNMHDR,LRESULT* pResult)
{
  LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
  int number = m_editString2.GetWindowNumber();
  if (pNMUpDown->iDelta < 0)
  {
    if(number > 0) --number;
  }
  else
  {
    if(number < 20) ++number;
  }
  m_editString2.SetWindowNumber(number);
  *pResult = 0;
}

void
MyFrameDlg2::OnBnClickedError()
{
  bool message(false);

  if(++m_error == 6)
  {
    m_error = 0;
  }

  m_combo_1    .SetErrorState(false);
  m_combo_2    .SetErrorState(false);
  m_combo_3    .SetErrorState(false);
  m_editString1.SetErrorState(false);
  m_editString2.SetErrorState(false);

  switch(m_error)
  {
    case 0:   message = true; break; // No control in error state
    case 1:   m_combo_1    .SetErrorState(true); break;
    case 2:   m_combo_2    .SetErrorState(true); break;
    case 3:   m_combo_3    .SetErrorState(true); break;
    case 4:   m_editString1.SetErrorState(true); break;
    case 5:   m_editString2.SetErrorState(true); break;
    default:  break;
  }

  if(message)
  {
    StyleMessageBox(this,_T("Testing the message box in error mode"),_T("ERROR"),MB_OK|MB_ICONERROR);
  }
}
