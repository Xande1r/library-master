#include <iostream>
#include "User.h"
#include "Manager.h"
#include "DBUtil.h"
#include "Student.h"
#include "Book.h"
using namespace std;
VOID HideConsoleCursor(VOID)
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
VOID ShowConsoleCursor(VOID)
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 1 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void heart()
{
	HideConsoleCursor();
	system("color 74");
	for (float y = 1.5f; y > -1.5f; y -= 0.1f)
	{
		printf("\t\t\t");
		for (float x = -1.5f; x < 1.5f; x += 0.05f)
		{
			float a = x * x + y * y - 1;
			putchar(a * a * a - x * x * y * y * y <= 0.0f ? '*' : ' ');
		}
		putchar('\n');
	}
	printf("\t\t\t       ");
	printf("欢");
	Sleep(200);
	printf(" 迎");
	Sleep(200);
	printf(" 使");
	Sleep(200);
	printf(" 用");
	Sleep(200);
	printf(" 图");
	Sleep(200);
	printf(" 书");
	Sleep(200);
	printf(" 管");
	Sleep(200);
	printf(" 理");
	Sleep(200);
	printf(" 系");
	Sleep(200);
	printf(" 统！");
	Sleep(200);
	printf(" (请按任意键进入...)");
	ShowConsoleCursor();
	getchar();
	system("cls");
}
void loginMenu()
{
	HideConsoleCursor();
	system("cls");
	system("color 74");
	printf("\t     -------------------******************图书管理系统*********************--------------------\n");
	printf("\t     -------------------******************图书管理系统*********************--------------------\n\n");
	printf(" --------------------******************账号只允许由1-18位英文与数字组成*********************------------------------\n");
	printf("\n --------------------******************密码只允许由6-18位英文与数字组成*********************------------------------\n");
	printf("\n\t\t\t\t\t欢迎使用学生管理系统，请先登录！\n");
	printf("\n");
	printf("\n");
	printf("\t\t                   ╭ ⺌ % ╮                             ╭ ```╮  \n");
	printf("\t\t                   (@^o^@) 欢迎使用图书管理系统   (⌒:⌒)\n");
	printf("\t\t                   (~):(~)                            (~)v(~) \n");
	printf("\t\t                   *****************************************\n");
	printf("\t\t  *           *    *                                       *  *           *    \n");
	printf("\t\t  * *       * *    *                                       *  * *       * *    \n");
	printf("\t\t  *   *   *   *    *                菜   单                *  *   *   *   *    \n");
	printf("\t\t  *     *     *    *                                       *  *     *     *    \n");
	printf("\t\t  *     *     *    *                1：登录                *  *     *     *    \n");
	printf("\t\t  *     *     *    *                                       *     *     *    \n");
	printf("\t\t  *     *     *    *                                       *  *     *     *    \n");
	printf("\t\t  *     *     *    *	                                      *  *     *     *    \n");
	printf("\t\t   *    *    *     *                0：退出                *   *    *    *     \n");
	printf("\t\t    *   *   *      *                                       *    *   *   *      \n");
	printf("\t\t      * * *        *****************************************      * * *        \n");
	printf("\n\t\t                                请输入您的操作！");
}
int main()
{
	heart();
	loginMenu();
	int handler;
	cin >> handler;
	if (handler == 1)
	{
		string strUserName = "";
		string strUserPWD = "";
		bool bIsLogin = false;
		User user;
		cout << "                          请输入用户名：";
		cin >> strUserName;
		cout << endl;
		cout << "                          请输入密码：";
		cin >> strUserPWD;
		cout << endl;
		DBUtil dbUtil;
		dbUtil.OpenDB();
		user = dbUtil.ReadUser(strUserName, strUserPWD);
		while (user.m_nID == -1)
		{
			cout << "用户名或者密码错误，请重新输入,按任意键继续..." << endl;
			cin.get();
			cin.get();
			system("cls");
			cout << "                          请输入用户名：";
			cin >> strUserName;
			cout << endl;
			cout << "                          请输入密码：";
			cin >> strUserPWD;
			cout << endl;
			user = dbUtil.ReadUser(strUserName, strUserPWD);
		}
		if (user.m_nRole == 1)
		{
			Manager manager;
			manager.m_nID = user.m_nRole;
			manager.m_strName = user.m_strName;
			manager.m_nRole = user.m_nRole;
			int command = -1;		//选择命令
			bIsLogin = true;
			string strBookName = "";
			int nBookId = 0;
			while (bIsLogin)
			{
				system("cls");
				manager.ShowMenu();
				cin >> command;
				switch (command)
				{
				case 1:
					//选择新增图书
					manager.AddBook();
					break;
				case 2:
					cout << "请输入书名：";
					cin >> strBookName;
					manager.QueryBook(strBookName);
					break;
				case 3:
					cout << "请输入要删除图书的ID" << endl;
					cin >> nBookId;
					manager.DeleteBook(nBookId);
					break;
				case 4:
					manager.DisplayAllBook();
					break;
				case 5:
					manager.DiaplayAllBorrowRecord();
					break;
				case 6:
					manager.AddUser();
					break;
				case 7:
					manager.DisplayAllUser();
					break;
				case 8:
					int id;
					cout << "请输入要删除用户的ID" << endl;
					cin >> id;
					manager.DeleteUser(id);
					break;
				case 9:
					manager.SelectUser();
					break;
				case 0:
					//选择退出登录
					bIsLogin = false;
					break;
				default:
					break;
				}
			}
			cout << "您已退出登录，按任意键退出..." << endl;
		}
		else
		{
			Student student;
			student.m_nID = user.m_nRole;
			student.m_strName = user.m_strName;
			student.m_nRole = user.m_nRole;
			int command = -1;		//选择命令
			bIsLogin = true;
			string strBookName = "";
			int nBookId;
			while (bIsLogin)
			{
				system("cls");
				student.ShowMenu();
				cin >> command;
				switch (command)
				{
				case 1:
					//选择查询图书
					cout << "请输入书名：";
					cin >> strBookName;
					student.QueryBook(strBookName);
					break;
				case 2:
					//选择借书
					cout << "请输入图书ID：";
					cin >> nBookId;
					student.BorrowBook(nBookId);
					break;
				case 3:
					//归还图书
					student.ReturnBook();
					break;
				case 4:
					student.ShowMyBorrowRecord();
					break;
				case 5:
					student.RenewBook();
					break;
				case 6:
					student.BorrowTop();
					break;
				case 0:
					//选择退出登录
					bIsLogin = false;
					break;
				default:
					break;
				}
			}
			cout << "您已退出登录，按任意键退出..." << endl;
		}
		cin.get();
		cin.get();
	}
	else if (handler == 0)
	{
		system("exit");
	}
	else {
		
	}
	
	
	return 0;
}