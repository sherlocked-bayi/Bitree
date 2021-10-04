
// work2Dlg.cpp: 实现文件
//

#include "stdafx.h"
#include "work2.h"
#include "work2Dlg.h"
#include "afxdialogex.h"
#include "math.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include <atlimage.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define OK 1
#define OVERFLOWW -2
#define ERROR 0
typedef char TElemType;
     
int dep0;                  //二叉树深度
int h1, h2;				  //记录结点与结点之间的距离以及层与层之间的距离
int lr = 0;                 //判断当前画的是左子树还是右子树的变量
int x = 500 / 2, xo = 500 / 2;	  
int y = 500 / 5, yo = 500 / 5;
int e = 0;					 //记录坐标出栈时的数据
int xl, yl;                  //记录坐标出栈时的数据
int h = 1;                    //记录所画的是第几层的二叉树
HDC hdc;          
RECT rect0 = { 0,0,500,500 };//定义一个矩形区域用于画图
LPCRECT rect = &rect0;
BOOL istrue; //记录Check2的结果
HWND hwnd;


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cwork2Dlg 对话框



Cwork2Dlg::Cwork2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WORK2_DIALOG, pParent)
	, m_dep()
	, m_pre(_T(""))
	, m_in(_T(""))
	, m_post(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cwork2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT7, m_pre);
	DDX_Text(pDX, IDC_EDIT8, m_in);
	DDX_Text(pDX, IDC_EDIT9, m_post);
}

BEGIN_MESSAGE_MAP(Cwork2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &Cwork2Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &Cwork2Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// Cwork2Dlg 消息处理程序

BOOL Cwork2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	ULONG_PTR m_pGdiToken;
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&m_pGdiToken, &gdiplusStartupInput, NULL);
	hwnd=GetSafeHwnd();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cwork2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cwork2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Cwork2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

typedef struct BiTNode {     //二叉树结构定义
	char data;
	struct BiTNode  *lchild, *rchild;
}BitNode, *BiTree;

typedef struct XY {  //二叉树结点坐标栈结构定义,用来画图
	int* base;
	int* top;
	int stacksize;
}XYStack;

XYStack X, Y;

int InitStack(XYStack &X)   //构造栈
{
	X.base = (int*)malloc(100 * sizeof(int));
	if (!X.base)
		exit(-2);
	X.top = X.base;
	X.stacksize = 100;
	return(1);
}

int GetTop(XYStack X, int &e)   //得到栈顶元素
{
	if (X.top == X.base)
		return(0);
	e = *(X.top - 1);
	return(1);
}

int Push(XYStack &X, int e)   //入栈
{
	if (X.top - X.base >= X.stacksize) {
		X.base = (int*)realloc(X.base, (X.stacksize + 10) * sizeof(int));
		if (!X.base)
			exit(-2);
		X.top = X.base + X.stacksize;
		X.stacksize += 10;
	}
	*X.top = e;
	X.top++;
	return(1);
}

int Pop(XYStack &X, int &e)    //出栈
{
	if (X.top == X.base)return(0);
	e = *--X.top;
	return(1);
}

int Find(CString str , int c) {//函数用来找字符串中某个特定元素的下标
	for (int i = 0; i < str.GetLength(); i++) {
		if (str[i] == c) {
			return i;
		}
	}
	return -1;
}

BiTree Createtree(CString pre, CString in, CString post) {//建树
		if (pre == "") {
			if (post.GetLength() <= 0) {
				return NULL;
			}
			char rootval = post[post.GetLength() - 1];
			BiTree root;
			root = (BiTNode*)malloc(sizeof(BitNode));
			root->data = rootval;
			int leftSize = in.Find(rootval);
			//切出左子树的中序和后序
			CString leftin = in.Left(leftSize);
			CString leftpost = post.Left(leftSize);
			root->lchild = Createtree("", leftin, leftpost);//递归求左子树
			//切出右子树的中序和后序
			CString rightin = in.Right(in.GetLength() - leftSize - 1);
			CString rightpost = post.Mid(leftSize, post.GetLength() - leftSize - 1);
			root->rchild = Createtree("", rightin, rightpost);//递归求右子树
			return root;
		}
		else if (post == "") {
			if (pre.GetLength() <= 0) {
				return NULL;
			}
			char rootval = pre[0];
			BiTree root;
			root = (BiTNode*)malloc(sizeof(BitNode));
			root->data = rootval;
			int leftSize = in.Find(rootval);
			//切出左子树的中序和先序
			CString leftin = in.Left(leftSize);
			CString leftpre = pre.Mid(1, leftSize);
			root->lchild = Createtree(leftpre, leftin, "");//递归求左子树
			//切出右子树的中序和先序
			CString rightin = in.Right(in.GetLength() - leftSize - 1);
			CString rightpre = pre.Right(pre.GetLength() - leftSize - 1);
			root->rchild = Createtree(rightpre, rightin, "");//递归求右子树
			return root;
		}
		else {
			if (post.GetLength() <= 0) {
				return NULL;
			}
			char rootval = post[post.GetLength() - 1];
			BiTree root;
			root = (BiTNode*)malloc(sizeof(BitNode));
			root->data = rootval;
			int leftSize = in.Find(rootval);
			//切出左子树的中序和后序
			CString leftin = in.Left(leftSize);
			CString leftpost = post.Left(leftSize);
			root->lchild = Createtree("", leftin, leftpost);//递归求左子树
			//切出右子树的中序和后序
			CString rightin = in.Right(in.GetLength() - leftSize - 1);
			CString rightpost = post.Mid(leftSize, post.GetLength() - leftSize - 1);
			root->rchild = Createtree("", rightin, rightpost);//递归求右子树
			return root;
		}

}


int Mydepth(BiTree T) {   //求树的深度
	int dep1, dep2;
	if (T == NULL) return 0;
	else {
		dep1 = Mydepth(T->lchild);//递归求左子树
		dep2 = Mydepth(T->rchild);//递归求右子树
		return (dep1 > dep2 ? dep1 + 1 : dep2 + 1);
	}
}

BOOL Check1(CString A, CString B) {//通过这个函数实现简单地比较输入的字符串的元素是否相等
	char* char1;
	LPCTSTR p = A.GetBuffer(0);
	A.ReleaseBuffer();
	char1 = new char[A.GetLength() + 1];
	strcpy_s(char1, A.GetLength() + 1, CT2CA(p));
	for (int i = 0; i < A.GetLength() - 1; i++)//将字符串A中的元素排序
		for (int j = 0; j < A.GetLength() - 1 - i; j++)
			if (char1[j] > char1[j + 1])
			{
				char c;
				c = char1[j];
				char1[j] = char1[j + 1];
				char1[j + 1] = c;
			}
	char* char2;
	p = B.GetBuffer(0);
	B.ReleaseBuffer();
	char2 = new char[B.GetLength() + 1];
	strcpy_s(char2, B.GetLength() + 1, CT2CA(p));
	for (int i = 0; i < B.GetLength() - 1; i++)//将字符串B中的元素排序
		for (int j = 0; j < B.GetLength() - 1 - i; j++)
			if (char2[j] > char2[j + 1])
			{
				char c;
				c = char2[j];
				char2[j] = char2[j + 1];
				char2[j + 1] = c;
			}
	if (!strcmp(char1,char2)) {//比较排序后的字符串是否相等
		return TRUE;
	}
	else return FALSE;
}

BOOL Check2(CString pre, CString in, CString post){//这个函数用来判断输入的序列是否能够构成一颗二叉树
	if (pre == "") {//输入了中序序列和后序序列
		if (post.GetLength() <= 0) {//简单的来说, 先由后序遍历可得到某一子树的树根, 则在中序遍历中查找此子树根便可知该子树的左子树组成与右子树的组成, 若在上一步得到的左子树, 右子树的序列不符合后序遍历序中的序列, 则可判定不可构成一颗二叉树		
			return TRUE;
		}
		char rootval = post[post.GetLength() - 1];
		int leftSize = in.Find(rootval);
		//切出左子树的中序和后序
		CString leftin = in.Left(leftSize);
		CString leftpost = post.Left(leftSize);
		if (Check1(leftin, leftpost)) {//判断后序序列的左子树与中序序列的是否相等,首先判断结点元素是否相等
			if (leftin.GetLength() == 1) {//然后判断是否递归到了只剩一个结点
				if (leftin == leftpost) {
					return TRUE;
				}
				else {
					istrue = FALSE;
					return FALSE;
				}
			}
			else Check2("", leftin, leftpost);//如果不是只剩一个结点，递归求左子树	
		}
		else
		{
			istrue = FALSE;
			return FALSE;
		}
		//切出右子树的中序和后序
		CString rightin = in.Right(in.GetLength() - leftSize - 1);
		CString rightpost = post.Mid(leftSize, post.GetLength() - leftSize - 1);	
		if (Check1(rightin, rightpost)) {//判断先序序列的左子树与中序序列的是否相等,首先判断结点元素是否相等
			if (rightin.GetLength() == 1) {//然后判断是否递归到了只剩一个结点
				if (rightin == rightpost) {
					return TRUE;
				}
				else {
					istrue = FALSE;
					return FALSE;
				}			
			}
			else Check2("", rightin, rightpost);//如果不是只剩一个结点，递归求左子树	
		}
		else
		{
			istrue = FALSE;
			return FALSE;
		}
	}
	else if (post == "") {//输入了先序序列和中序序列
		if (pre.GetLength() <= 0) {//先由先序遍历可得到某一子树的树根,则在中序遍历中查找此子树根便可知该子树的左子树组成与右子树的组成,若在上一步得到的左子树,右子树的序列不符合先序遍历序中的序列,则可判定不可构成一颗二叉树
			return TRUE;
		}
		char rootval = pre[0];
		int leftSize = in.Find(rootval);
		//切出左子树的中序和先序
		CString leftin = in.Left(leftSize);
		CString leftpre = pre.Mid(1, leftSize);
		if (Check1(leftin, leftpre)) {//判断先序序列的左子树与中序序列的是否相等,首先判断结点元素是否相等
			if (leftin.GetLength() == 1) {//然后判断是否递归到了只剩一个结点
				if (leftin == leftpre) {
					return TRUE;
				}
				else {
					istrue = FALSE;
					return FALSE;
				} 
			}
			else Check2(leftpre, leftin, "");//如果不是只剩一个结点，递归求左子树	
		}
		else {
			istrue = FALSE;
			return FALSE;
		} 
		//切出右子树的中序和先序
		CString rightin = in.Right(in.GetLength() - leftSize - 1);
		CString rightpre = pre.Right(pre.GetLength() - leftSize - 1);
		if (Check1(rightin, rightpre)) {//判断先序序列的左子树与中序序列的是否相等,首先判断结点元素是否相等
			if (rightin.GetLength() == 1) {//然后判断是否递归到了只剩一个结点
				if (rightin == rightpre) {
					return TRUE;
				}
				else {
					istrue = FALSE;
					return FALSE;
				} 
			}
			else Check2(rightpre, rightin, "");//如果不是只剩一个结点，递归求左子树	
		}
		else {
			istrue = FALSE;
			return FALSE;
		} 
	}
	else {
		if (pre.GetLength() <= 0) {//先由先序遍历可得到某一子树的树根,则在中序遍历中查找此子树根便可知该子树的左子树组成与右子树的组成,若在上一步得到的左子树,右子树的序列不符合先序遍历序中的序列,则可判定不可构成一颗二叉树
			return TRUE;
		}
		char rootval = pre[0];
		int leftSize = in.Find(rootval);
		//切出左子树的中序和先序
		CString leftin = in.Left(leftSize);
		CString leftpre = pre.Mid(1, leftSize);
		if (Check1(leftin, leftpre)) {//判断先序序列的左子树与中序序列的是否相等,首先判断结点元素是否相等
			if (leftin.GetLength() == 1) {//然后判断是否递归到了只剩一个结点
				if (leftin == leftpre) {
					return TRUE;
				}
				else {
					istrue = FALSE;
					return FALSE;
				}
			}
			else Check2(leftpre, leftin, "");//如果不是只剩一个结点，递归求左子树	
		}
		else {
			istrue = FALSE;
			return FALSE;
		}
		//切出右子树的中序和先序
		CString rightin = in.Right(in.GetLength() - leftSize - 1);
		CString rightpre = pre.Right(pre.GetLength() - leftSize - 1);
		if (Check1(rightin, rightpre)) {//判断先序序列的左子树与中序序列的是否相等,首先判断结点元素是否相等
			if (rightin.GetLength() == 1) {//然后判断是否递归到了只剩一个结点
				if (rightin == rightpre) {
					return TRUE;
				}
				else {
					istrue = FALSE;
					return FALSE;
				}
			}
			else Check2(rightpre, rightin, "");////如果不是只剩一个结点，递归求左子树	
		}
		else {
			istrue = FALSE;
			return FALSE;
		}
	}
}


BOOL Draw(BiTree T, int lr, int h) {   //画图，先画左子树后画右子树
	if (T) {
		if (lr == 0) { //如果是头结点，则初始化x,y坐标
			x = xo; 
			y = yo; 
		}
		else if (h == dep0){
			x = (int)(xo + lr * h1/2); //求当前结点坐标，如果是最下面一层，则对于父节点来说则是偏移了h1/2的距离                            //比如第五层偏移量为 h/2
			y = (int)(yo + h2);                                                                                                            //第四层偏移量为h
		}                                                                                                                                  //第三层偏移量离为2h
		else {                                                                                                                             //第二层偏移量为4h
			x = (int)(xo + lr * h1*(pow(2, dep0 - h-1))); //求当前结点坐标，对于每层来说，都是相对于父节点的h1*2的dep0-h-1次方的偏移量     //第一层偏移量为0
			y = (int)(yo + h2);
		}
		if (lr == 0) {
			//MoveToEx(hdc, xo, yo, NULL);			//当前结点和父节点用直线连接
			//LineTo(hdc, x, y);
		}
		else {//动态画线
			float xm;
			float ym;
			for (xm = (float)xo,ym =(float)yo;  ym <= y; xm +=(float)(x-xo)/100, ym +=(float)h2/100) {
				if (lr > 0 && xm <= x) {
					MoveToEx(hdc, xo+lr*20, yo+15, NULL);			//当前结点和父节点用直线连接
					LineTo(hdc, xm + lr * 20, ym+15);
					Sleep(5);
				}
				if (lr < 0 && xm >= x) {
					MoveToEx(hdc, xo + lr * 20, yo+15, NULL);			//当前结点和父节点用直线连接
					LineTo(hdc, xm + lr *20, ym+15);
					Sleep(5);
				}
		}
		}		
		Ellipse(hdc, x - 23, y - 20, x + 23, y + 35); //画圈圈
		if (T->data == 'A'|| T->data == 'a') {
			CImage im0;
			im0.Load("res\\1.png");
			im0.Draw(hdc, x-15,y-10);
			Sleep(500);
			CImage im;
			im.Load("res\\2.png");
			im.Draw(hdc, x - 15, y - 10);
		}
		if (T->data == 'B' || T->data == 'b') {
			CImage im0;
			im0.Load("res\\3.png");
			im0.Draw(hdc, x - 15, y - 10);
			Sleep(500);
			CImage im;
			im.Load("res\\4.png");
			im.Draw(hdc, x - 15, y - 10);
		}
		if (T->data == 'C' || T->data == 'c') {
			CImage im0;
			im0.Load("res\\5.png");
			im0.Draw(hdc, x - 15, y - 10);
		}
		if (T->data == 'D' || T->data == 'd') {
			CImage im0;
			im0.Load("res\\6.png");
			im0.Draw(hdc, x - 15, y - 10);
			Sleep(500);
			CImage im;
			im.Load("res\\7.png");
			im.Draw(hdc, x - 15, y - 10);
		}
		if (T->data == 'E' || T->data == 'e') {
			CImage im0;
			im0.Load("res\\8.png");
			im0.Draw(hdc, x - 15, y - 10);
			Sleep(500);
			CImage im;
			im.Load("res\\9.png");
			im.Draw(hdc, x - 15, y - 10);
		}
		if (T->data == 'F' || T->data == 'f') {
			CImage im0;
			im0.Load("res\\10.png");
			im0.Draw(hdc, x - 15, y - 10);
			Sleep(500);
			CImage im;
			im.Load("res\\11.png");
			im.Draw(hdc, x - 15, y - 10);
		}
		if (T->data == 'G' || T->data == 'g') {
			CImage im0;
			im0.Load("res\\47.png");
			im0.Draw(hdc, x - 15, y - 10);
			Sleep(500);
			CImage im;
			im.Load("res\\48.png");
			im.Draw(hdc, x - 15, y - 10);
		}
		if (T->data == 'H' || T->data == 'h') {
			CImage im0;
			im0.Load("res\\12.png");
			im0.Draw(hdc, x - 15, y - 10);
			Sleep(500);
			CImage im;
			im.Load("res\\13.png");
			im.Draw(hdc, x - 15, y - 10);
		}
		if (T->data == 'I' || T->data == 'i') {
			CImage im0;
			im0.Load("res\\14.png");
			im0.Draw(hdc, x - 15, y - 10);
			Sleep(500);
			CImage im;
			im.Load("res\\15.png");
			im.Draw(hdc, x - 15, y - 10);
		}
		if (T->data == 'J' || T->data == 'j') {
			CImage im0;
			im0.Load("res\\16.png");
			im0.Draw(hdc, x - 15, y - 10);
			Sleep(500);
			CImage im;
			im.Load("res\\17.png");
			im.Draw(hdc, x - 15, y - 10);
		}
		if (T->data == 'K' || T->data == 'k') {
			CImage im0;
			im0.Load("res\\18.png");
			im0.Draw(hdc, x - 15, y - 10);
			Sleep(500);
			CImage im;
			im.Load("res\\19.png");
			im.Draw(hdc, x - 15, y - 10);
		}
		if (T->data == 'L' || T->data == 'l') {
			CImage im0;
			im0.Load("res\\20.png");
			im0.Draw(hdc, x - 15, y - 10);
			Sleep(500);
			CImage im;
			im.Load("res\\21.png");
			im.Draw(hdc, x - 15, y - 10);
		}
		if (T->data == 'M' || T->data == 'm') {
			CImage im0;
			im0.Load("res\\22.png");
			im0.Draw(hdc, x - 15, y - 10);
			Sleep(500);
			CImage im;
			im.Load("res\\23.png");
			im.Draw(hdc, x - 15, y - 10);
		}
		if (T->data == 'N' || T->data == 'n') {
			CImage im0;
			im0.Load("res\\24.png");
			im0.Draw(hdc, x - 15, y - 10);
			Sleep(500);
			CImage im;
			im.Load("res\\25.png");
			im.Draw(hdc, x - 15, y - 10);
		}
		if (T->data == 'O' || T->data == 'o') {
			CImage im0;
			im0.Load("res\\26.png");
			im0.Draw(hdc, x - 15, y - 10);
		}
		if (T->data == 'P' || T->data == 'p') {
			CImage im0;
			im0.Load("res\\27.png");
			im0.Draw(hdc, x - 15, y - 10);
			Sleep(500);
			CImage im;
			im.Load("res\\28.png");
			im.Draw(hdc, x - 15, y - 10);
		}
		if (T->data == 'Q' || T->data == 'q') {
			CImage im0;
			im0.Load("res\\29.png");
			im0.Draw(hdc, x - 15, y - 10);
			Sleep(500);
			CImage im;
			im.Load("res\\30.png");
			im.Draw(hdc, x - 15, y - 10);
		}
		if (T->data == 'R' || T->data == 'r') {
			CImage im0;
			im0.Load("res\\31.png");
			im0.Draw(hdc, x - 15, y - 10);
			Sleep(500);
			CImage im;
			im.Load("res\\32.png");
			im.Draw(hdc, x - 15, y - 10);
		}
		if (T->data == 'S' || T->data == 's') {
			CImage im0;
			im0.Load("res\\33.png");
			im0.Draw(hdc, x - 15, y - 10);
		}
		if (T->data == 'T' || T->data == 't') {
			CImage im0;
			im0.Load("res\\34.png");
			im0.Draw(hdc, x - 15, y - 10);
			Sleep(500);
			CImage im;
			im.Load("res\\35.png");
			im.Draw(hdc, x - 15, y - 10);
		}
		if (T->data == 'U' || T->data == 'u') {
			CImage im0;
			im0.Load("res\\36.png");
			im0.Draw(hdc, x - 15, y - 10);
		}
		if (T->data == 'V' || T->data == 'v') {
			CImage im0;
			im0.Load("res\\37.png");
			im0.Draw(hdc, x - 15, y - 10);
			Sleep(500);
			CImage im;
			im.Load("res\\38.png");
			im.Draw(hdc, x - 15, y - 10);
		}
		if (T->data == 'W' || T->data == 'w') {
			CImage im0;
			im0.Load("res\\39.png");
			im0.Draw(hdc, x - 15, y - 10);
			Sleep(500);
			CImage im;
			im.Load("res\\40.png");
			im.Draw(hdc, x - 15, y - 10);
		}
		if (T->data == 'X' || T->data == 'x') {
			CImage im0;
			im0.Load("res\\41.png");
			im0.Draw(hdc, x - 15, y - 10);
			Sleep(500);
			CImage im;
			im.Load("res\\42.png");
			im.Draw(hdc, x - 15, y - 10);
		}
		if (T->data == 'Y' || T->data == 'y') {
			CImage im0;
			im0.Load("res\\43.png");
			im0.Draw(hdc, x - 15, y - 10);
			Sleep(500);
			CImage im;
			im.Load("res\\44.png");
			im.Draw(hdc, x - 15, y - 10);
		}
		if (T->data == 'Z' || T->data == 'z') {
			CImage im0;
			im0.Load("res\\45.png");
			im0.Draw(hdc, x - 15, y - 10);
			Sleep(500);
			CImage im;
			im.Load("res\\46.png");
			im.Draw(hdc, x - 15, y - 10);
		}
		Sleep(500);//实现动态显示过程
		xo = x;		//将当前结点设为源节点
		yo = y;
		Push(X, x); //保存当前节点坐标                                                                                                                                                         
		Push(Y, y);
		h++;       //深度加一
		Draw(T->lchild, lr = -1, h);   //递归遍历输出各结点，如果是左子树则lr=-1，向左画
		Draw(T->rchild, lr = 1, h);	//如果是右子树则lr=1，向右画
	}
	else
		return TRUE;
	if (lr == 1) {      //当右子树遍历完后，执行：
		h--;		//当前深度-1，开始画上一层的右子树
		Pop(X, e);  //坐标出栈
		Pop(Y, e);
		GetTop(X, xl); //将上一个结点的坐标赋给xo,yo
		GetTop(Y, yl);
		xo = xl;
		yo = yl;
	}
}

void Cwork2Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	hdc = ::GetDC(m_hWnd); 
	FillRect(hdc, rect, NULL);//清空图
	UpdateData(TRUE); //更新数据
	if (m_pre == "") {//只输入了中序和后序
		if (Check1(m_in, m_post)) {//首先判断输入的中序序列和后序序列元素是否相等
			istrue = TRUE;//初始化istrue
			Check2("", m_in, m_post);//然后判断输入的中序序列和后序序列是否能构成一颗二叉树
			if (istrue) {
			BiTree T = Createtree(m_pre, m_in, m_post);//建立二叉树
			int dep = Mydepth(T);  //得到二叉树深度
			dep0 = dep;  //赋给全局变量
			h1 = (int)(500 / (pow(2, dep - 1) + 1));  //根据树深确定结点与结点之间的距离，因为二叉树在满二叉树的情况下，最下层有2的n-1次方的结点，m为二叉树的深度，因此用宽度500除以结点数加一，则可以得到适当的结点与结点之间的距离
			h2 = (int)(500 / (dep + 1));			//根据树深确定层与层之间的距离，用长度除以深度加一就可以得到适当的层与层之间的距离
			lr = 0;             
			h = 1;	//从第一层开始画				
			x = 500 / 2, xo = 500 / 2;	//初始化坐标
			y = 500 / 5, yo = 500 / 5;	
			InitStack(X);			// 初始X栈
			InitStack(Y);			//初始Y栈
			CPen pen(PS_SOLID, 2, RGB(0, 0, 0));
			SelectObject(hdc, pen);
			Draw(T, lr, h);     //画图
			::ReleaseDC(m_hWnd, hdc);  
			}
			else MessageBoxA(_T("输入表达式不合法！"));
		}
		else MessageBoxA(_T("输入表达式不合法！"));
	}
	else if(m_post == "") {//只输入了先序和中序
		if (Check1(m_in, m_pre)) {//首先判断输入的先序序列和中序序列元素是否相等
			istrue = TRUE;//初始化istrue
			Check2(m_pre, m_in, "");
			if (istrue) {//然后判断输入的先序序列和中序序列是否能构成一颗二叉树
				BiTree T = Createtree(m_pre, m_in, m_post);//建立二叉树
				int dep = Mydepth(T);
				dep0 = dep;
				h1 = (int)(500 / (pow(2, dep - 1) + 1));  //根据树深确定结点与结点之间的距离，因为二叉树在满二叉树的情况下，最下层有2的n-1次方的结点，m为二叉树的深度，因此用宽度500除以结点数加一，则可以得到适当的结点与结点之间的距离
				h2 = (int)(500 / (dep + 1));			//根据树深确定层与层之间的距离，用长度除以深度加一就可以得到适当的层与层之间的距离
				lr = 0;
				h = 1;
				InitStack(X);			// 初始X栈
				InitStack(Y);			//初始Y栈
				x = 500 / 2, xo = 500 / 2;	//初始化坐标
				y = 500 / 5, yo = 500 / 5;
				CPen pen(PS_SOLID, 2, RGB(0, 0, 0));
				SelectObject(hdc, pen);
				Draw(T, lr, h);       //画图
				::ReleaseDC(m_hWnd, hdc);
			}
			else MessageBoxA(_T("输入表达式不合法！"));
		}	
		else MessageBoxA(_T("输入表达式不合法！"));
	}
	else {//先，中，后序都输入了，按先序和中序的情况处理即可
		if (Check1(m_in, m_pre)) {
			istrue = TRUE;//初始化istrue
			Check2(m_pre, m_in, "");
			if (istrue) {
			BiTree T = Createtree(m_pre, m_in, m_post);//建立二叉树
			int dep = Mydepth(T);
			dep0 = dep;
			h1 = (int)(500 / (pow(2, dep - 1) + 1)); //根据树深确定结点与结点之间的距离，因为二叉树在满二叉树的情况下，最下层有2的n-1次方的结点，m为二叉树的深度，因此用宽度500除以结点数加一，则可以得到适当的结点与结点之间的距离
			h2 = (int)(500 / (dep + 1));			//根据树深确定层与层之间的距离，用长度除以深度加一就可以得到适当的层与层之间的距离
			lr = 0;      
			h = 1;
			InitStack(X);			// 初始X栈
			InitStack(Y);			//初始Y栈
			x = 500 / 2, xo = 500 / 2;		
			y = 500 / 5, yo = 500 / 5;		
			CPen pen(PS_SOLID, 2, RGB(0, 0, 0));
			SelectObject(hdc, pen);
			Draw(T, lr, h);       //画图
			::ReleaseDC(m_hWnd, hdc); 
			}
			else MessageBoxA(_T("输入表达式不合法！"));
		}
		else MessageBoxA(_T("输入表达式不合法！"));
	}
}


void Cwork2Dlg::OnBnClickedButton1()//测试
{
	// TODO: 在此添加控件通知处理程序代码
	hdc = ::GetDC(m_hWnd);
	FillRect(hdc, rect, NULL);//清空图
	BiTree T = Createtree("ABDECFG", "DBEAFCG", "");
	int dep = Mydepth(T);
	dep0 = dep;
	h1 = (int)(500 / (pow(2, dep - 1) + 1)); 
	h2 = (int)(500 / (dep + 1));
	lr = 0;
	h = 1;
	InitStack(X);			// 初始X栈
	InitStack(Y);			//初始Y栈
	x = 500 / 2, xo = 500 / 2;
	y = 500 / 5, yo = 500 / 5;
	CPen pen(PS_SOLID, 2, RGB(0, 0, 0));
	SelectObject(hdc, pen);
	Draw(T, lr, h);       //画图
	::ReleaseDC(m_hWnd, hdc);
}
