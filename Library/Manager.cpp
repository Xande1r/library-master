#include "Manager.h"


Manager::Manager()
{
}


Manager::~Manager()
{
}
VOID HideConsoleCursor1(VOID)
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
VOID ShowConsoleCursor1(VOID)
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 1 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void Manager::ShowMenu()
{
	HideConsoleCursor1();
	system("cls");
	system("color 74");
	printf("\n");
	printf("\n");
	printf("\t\t                   ╭ ⺌ % ╮                             ╭ ```╮  \n");
	printf("\t\t                   (@^o^@) 欢迎使用图书信息后台管理系统   (⌒:⌒)\n");
	printf("\t\t                   (~):(~)                            (~)v(~) \n");
	printf("\t\t                   *****************************************\n");
	printf("\t\t  *           *    *                                       *  *           *    \n");
	printf("\t\t  * *       * *    *                                       *  * *       * *    \n");
	printf("\t\t  *   *   *   *    *                菜   单                *  *   *   *   *    \n");
	printf("\t\t  *     *     *    *                                       *  *     *     *    \n");
	printf("\t\t  *     *     *    *           [1]：新书录入               *  *     *     *    \n");
	printf("\t\t  *     *     *    *                                       *     *     *    \n");
	printf("\t\t  *     *     *    *           [2]：图书查询               *  *     *     *    \n");
	printf("\t\t  *     *     *    *	                                   *  *     *     *    \n");
	printf("\t\t  *     *     *    *	       [3]：删除图书               *  *     *     *    \n");
	printf("\t\t  *     *     *    *	                                   *  *     *     *    \n");
	printf("\t\t  *     *     *    *	       [4]：图书列表               *  *     *     *    \n");
	printf("\t\t  *     *     *    *	                                   *  *     *     *    \n");
	printf("\t\t  *     *     *    *	       [5]：借阅记录               *  *     *     *    \n");
	printf("\t\t  *     *     *    *	                                   *  *     *     *    \n");
	printf("\t\t  *     *     *    *	       [6]：新增用户               *  *     *     *    \n");
	printf("\t\t  *     *     *    *	                                   *  *     *     *    \n");
	printf("\t\t   *    *    *     *           [7]：用户列表               *  *     *     *     \n");
	printf("\t\t  *     *     *    *	                                   *  *     *     *    \n");
	printf("\t\t  *     *     *    *	       [8]：删除用户               *  *     *     *    \n");
	printf("\t\t  *     *     *    *	                                   *  *     *     *    \n");
	printf("\t\t  *     *     *    *	       [9]：查询用户               *  *     *     *    \n");
	printf("\t\t  *     *     *    *	                                   *  *     *     *    \n");
	printf("\t\t  *     *     *    *	       [0]:退出登录                *  *     *     *    \n");
	printf("\t\t    *   *   *      *                                       *    *   *   *      \n");
	printf("\t\t      * * *        *****************************************      * * *        \n");
	printf("\n\t\t                                请输入您的操作！");
}

bool Manager::AddBook()
{
	string bookName;
	string author;
	string classify;
	string isbn;
	string pub;
	int total;
	char szTime[32] = { 0 };
	time_t lt;
	lt = time(NULL);
	m_timeUtil.TimeToString(lt, szTime);

	cout << "你选择的是新增图书功能，请依次输入图书信息" << endl;
	cout << "图书名称 类别 作者 ISBN 出版社 总册数" << endl;
	cin >> bookName;
	cin >> classify;
	cin >> author;
	cin >> isbn;
	cin >> pub;
	cin >> total;

	Book book;
	book.SetBookName(bookName);
	book.SetClassify(classify);
	book.SetAuthor(author);
	book.SetISBN(isbn);
	book.SetPub(pub);
	book.SetTotalNum(total);
	book.SetLeftNum(0);
	book.SetInDate(szTime);

	if (!m_dbUtil.isOpen)
	{
		m_dbUtil.OpenDB();
	}
	m_dbUtil.AddBook(book);
	cout << "新增图书成功" << endl;
	getchar();
	return true;
}

//展示所有书籍
bool Manager::DisplayAllBook()
{
	vector<Book> books;
	if (!m_dbUtil.isOpen)
	{
		m_dbUtil.OpenDB();
	}

	m_dbUtil.SelectAllBook(books);
	vector<Book>::iterator vecIter;
	cout << "ID     书名            类别            作者           出版社       入库日期     馆藏数量   余量" << endl;
	for (vecIter = books.begin(); vecIter != books.end(); vecIter++)
	{

		cout << setiosflags(ios::left) << setw(4) << vecIter->GetBookID() << "  " << setw(14) << vecIter->GetBookName() << "  " << setw(10) << vecIter->GetClassify() << "  " << setw(10) << vecIter->GetAuthor() << "  " << setw(14) << vecIter->GetPub() << "  " << setw(14) << vecIter->GetInDate() << "  " << setw(8) << vecIter->GetTotalNum() << "  " << setw(3) << vecIter->GetLeftNum() << endl;
	}
	cin.get();
	cin.get();
	return true;
}

//根据书名查询书籍
bool Manager::QueryBook(string strBookName)
{
	vector<Book> books;
	if (!m_dbUtil.isOpen)
	{
		m_dbUtil.OpenDB();
	}

	m_dbUtil.SelectBookByName(strBookName, books);
	vector<Book>::iterator vecIter;
	cout << "ID     书名            类别            作者           出版社       入库日期     馆藏数量   余量" << endl;
	for (vecIter = books.begin(); vecIter != books.end(); vecIter++)
	{

		cout << setiosflags(ios::left) << setw(4) << vecIter->GetBookID() << "  " << setw(14) << vecIter->GetBookName() << "  " << setw(10) << vecIter->GetClassify() << "  " << setw(10) << vecIter->GetAuthor() << "  " << setw(14) << vecIter->GetPub() << "  " << setw(14) << vecIter->GetInDate() << "  " << setw(8) << vecIter->GetTotalNum() << "  " << setw(3) << vecIter->GetLeftNum() << endl;
	}
	cin.get();
	cin.get();
	return true;
}

//根据图书ID删除图书
bool Manager::DeleteBook(int nBookId)
{
	Book book;
	book.SetBookID(-1);
	if (!m_dbUtil.isOpen)
	{
		m_dbUtil.OpenDB();
	}
	m_dbUtil.SelectBookById(nBookId, book);
	if (book.GetBookID() != -1)
	{
		cout << "ID     书名            类别            作者           出版社       入库日期     馆藏数量   余量" << endl;
		cout << setiosflags(ios::left) << setw(4) << book.GetBookID() << "  " << setw(14) << book.GetBookName() << "  " << setw(10) << book.GetClassify() << "  " << setw(10) << book.GetAuthor() << "  " << setw(14) << book.GetPub() << "  " << setw(14) << book.GetInDate() << "  " << setw(8) << book.GetTotalNum() << "  " << setw(3) << book.GetLeftNum() << endl;

		//询问是否删除
		char chIsDelete = 'a';
		cout << "删除这本书吗?n/y" << endl;
		cin.get();
		cin >> chIsDelete;
		while (true)
		{
			if (chIsDelete == 'y' || chIsDelete == 'Y')
			{
				m_dbUtil.DeleteBookById(nBookId);
				break;
			}
			else if (chIsDelete == 'n' || chIsDelete == 'N')
			{
				cout << "已取消删除！";
				break;
			}
			else
			{
				cout << "输入有误,请重新输入:";
				cin.get();
				cin >> chIsDelete;
			}
		}
	}
	else
	{
		cout << "没有找到ID为" << nBookId << "的书籍" << endl;
	}
	cin.get();
	cin.get();
	return true;
}

//根据用户名删除用户
bool Manager::DeleteUser(int id)
{
	if (!m_dbUtil.isOpen)
	{
		m_dbUtil.OpenDB();
	}
	User user = m_dbUtil.SelectUserById(id);
	if (user.m_nID != id)
	{
		cout << "很抱歉,不存在该用户！" << endl;
	}
	else {
		cout << "ID     用户名      身份" << endl;
		cout << setiosflags(ios::left) << setw(6) << user.m_nID << "  " << setw(8) << user.m_strName << "  " << (user.m_nRole == 1 ? "管理员" : "学生") << endl;
		//询问是否删除
		char chIsDelete = 'a';
		cout << "删除这个用户吗?n/y" << endl;
		cin.get();
		cin >> chIsDelete;
		while (true)
		{
			if (chIsDelete == 'y' || chIsDelete == 'Y')
			{
				m_dbUtil.DeleteByUserId(id);
				break;
			}
			else if (chIsDelete == 'n' || chIsDelete == 'N')
			{
				cout << "已取消删除！";
				break;
			}
			else
			{
				cout << "输入有误,请重新输入:";
				cin.get();
				cin >> chIsDelete;
			}
		}
	}
	cout << "输入任意值继续....";
	getchar();
	return true;
}

//展示所有借阅记录
bool Manager::DiaplayAllBorrowRecord()
{
	vector<BorrowRecord> borrowRecords;
	if (!m_dbUtil.isOpen)
	{
		m_dbUtil.OpenDB();
	}

	m_dbUtil.SelectAllBorrowRecord(borrowRecords);
	User user;
	Book book;
	vector<BorrowRecord>::iterator vecIter;
	cout << "ID       书名        借阅人    借阅日期       应还日期     还书日期   续借次数" << endl;
	for (vecIter = borrowRecords.begin(); vecIter != borrowRecords.end(); vecIter++)
	{
		user = m_dbUtil.SelectUserById(vecIter->m_nUserId);
		m_dbUtil.SelectBookById(vecIter->m_nBookId, book);
		cout << setiosflags(ios::left) << setw(4) << vecIter->m_nBorrowId << "  " << setw(14) << book.GetBookName() << "  " << setw(6) << user.m_strName << "  " << setw(13) << vecIter->m_tBorrowDate << "  " << setw(13) << vecIter->m_tShouldReturnDate << "  " << setw(13) << vecIter->m_tReturnDate << "  " << setw(3) << vecIter->m_nContinue << endl;
	}
	cin.get();
	cin.get();
	return true;
}

//增加用户
bool Manager::AddUser()
{
	cout << "请输入一下用户信息:" << endl;
	cout << "用户名   密码   用户类型" << endl;
	User user;

	cin >> user.m_strName;
	cin >> user.m_strPassword;
	cin >> user.m_nRole;

	if (!m_dbUtil.isOpen)
	{
		m_dbUtil.OpenDB();
	}

	m_dbUtil.AddUser(user);
	cout << "新增用户成功" << endl;
	cin.get();
	cin.get();
	return true;
}

//展示所有用户
bool Manager::DisplayAllUser()
{
	vector<User> users;
	if (!m_dbUtil.isOpen)
	{
		m_dbUtil.OpenDB();
	}

	m_dbUtil.SelectAllUser(users);
	User user;
	Book book;
	vector<User>::iterator vecIter;
	cout << "ID     用户名      身份" << endl;
	for (vecIter = users.begin(); vecIter != users.end(); vecIter++)
	{
		cout << setiosflags(ios::left) << setw(6) << vecIter->m_nID << "  " << setw(8) << vecIter->m_strName << "  " << (vecIter->m_nRole == 1 ? "管理员" : "学生") << endl;
	}
	cin.get();
	cin.get();
	return true;
}
bool Manager::SelectUser()
{
	vector<User> users;
	string name;
	if (!m_dbUtil.isOpen)
	{
		m_dbUtil.OpenDB();
	}
	cout << "\n请输入用户名：\t";
	cin >> name;
	m_dbUtil.SelectByName(name, users);
	vector<User>::iterator vecIter;
	cout << "ID     用户名      身份" << endl;
	for (vecIter = users.begin(); vecIter != users.end(); vecIter++)
	{
		cout << setiosflags(ios::left) << setw(6) << vecIter->m_nID << "  " << setw(8) << vecIter->m_strName << "  " << (vecIter->m_nRole == 1 ? "管理员" : "学生") << endl;
	}
	cout << "输入任意字符继续........" << endl;
	cin.get();
	cin.get();
	return true;
}
