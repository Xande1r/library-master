#include "Student.h"

Student::Student()
{
}


Student::~Student()
{
}
VOID HideConsoleCursor2(VOID)
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
VOID ShowConsoleCursor2(VOID)
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 1 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void Student::ShowMenu()
{
	HideConsoleCursor2();
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
	printf("\t\t  *     *     *    *           [1]：查询图书               *  *     *     *    \n");
	printf("\t\t  *     *     *    *                                       *     *     *    \n");
	printf("\t\t  *     *     *    *           [2]：借阅图书               *  *     *     *    \n");
	printf("\t\t  *     *     *    *	                                   *  *     *     *    \n");
	printf("\t\t  *     *     *    *	       [3]：归还图书               *  *     *     *    \n");
	printf("\t\t  *     *     *    *	                                   *  *     *     *    \n");
	printf("\t\t  *     *     *    *	       [4]：借阅记录               *  *     *     *    \n");
	printf("\t\t  *     *     *    *	                                   *  *     *     *    \n");
	printf("\t\t  *     *     *    *	       [5]：续借图书               *  *     *     *    \n");
	printf("\t\t  *     *     *    *	                                   *  *     *     *    \n");
	printf("\t\t  *     *     *    *	       [6]：借阅排行               *  *     *     *    \n");
	printf("\t\t  *     *     *    *	                                   *  *     *     *    \n");
	printf("\t\t  *     *     *    *	       [0]:退出登录                *  *     *     *    \n");
	printf("\t\t    *   *   *      *                                       *    *   *   *      \n");
	printf("\t\t      * * *        *****************************************      * * *        \n");
	printf("\n\t\t                                请输入您的操作！");
}

bool Student::BorrowTop()
{
	vector<Book> books;
	if (!m_dbUtil.isOpen)
	{
		m_dbUtil.OpenDB();
	}
	m_dbUtil.BorrowTop(books);
	cout << "书名     借阅数量" << endl;
	vector<Book>::iterator vecIter;
	for (vecIter = books.begin(); vecIter != books.end(); vecIter++)
	{

		cout << setiosflags(ios::left) << setw(4) << vecIter->GetBookName() << "  " << setw(14) << vecIter->GetTotalNum()<< endl;
	}
	cin.get();
	cin.get();
	return true;
}
//根据书名查询书籍
bool Student::QueryBook(string strBookName)
{
	vector<Book> books;
	if (!m_dbUtil.isOpen)
	{
		m_dbUtil.OpenDB();
	}

	m_dbUtil.SelectBookByName(strBookName, books);
	vector<Book>::iterator vecIter;
	cout << "ID     书名            作者           出版社       入库日期     馆藏数量   余量" << endl;
	for (vecIter = books.begin(); vecIter != books.end(); vecIter++)
	{

		cout << setiosflags(ios::left) << setw(4) << vecIter->GetBookID() << "  " << setw(14) << vecIter->GetBookName() << "  " << setw(10) << vecIter->GetAuthor() << "  " << setw(14) << vecIter->GetPub() << "  " << setw(14) << vecIter->GetInDate() << "  " << setw(8) << vecIter->GetTotalNum() << "  " << setw(3) << vecIter->GetLeftNum() << endl;
	}
	cin.get();
	cin.get();
	return true;
}

//根据图书ID借阅书籍
bool Student::BorrowBook(int nBookId)
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
		cout << "ID     书名            作者           出版社       入库日期     馆藏数量   余量" << endl;
		cout << setiosflags(ios::left) << setw(4) << book.GetBookID() << "  " << setw(14) << book.GetBookName() << "  " << setw(10) << book.GetAuthor() << "  " << setw(14) << book.GetPub() << "  " << setw(14) << book.GetInDate() << "  " << setw(8) << book.GetTotalNum() << "  " << setw(3) << book.GetLeftNum() << endl;
		if (book.GetLeftNum() == 0)
		{
			cout << "该书籍已全部借出，暂时无法借阅!" << endl;
			cin.get();
			cin.get();
			return false;
		}
		//询问是否借阅
		char chIsBorrow = 'a';
		cout << "借阅这本书吗?n/y" << endl;
		cin.get();
		cin >> chIsBorrow;
		while (true)
		{
			if (chIsBorrow == 'y' || chIsBorrow == 'Y')
			{
				//借阅
				BorrowRecord borrowRecord;
				borrowRecord.m_nBookId = book.GetBookID();
				borrowRecord.m_nUserId = m_nID;
				time_t tTemp = time(NULL);
				char szTime[16] = { 0 };
				m_timeUtil.TimeToString(tTemp, szTime);
				borrowRecord.m_tBorrowDate = szTime;
				borrowRecord.m_tShouldReturnDate = m_timeUtil.AddMonth(tTemp);
				borrowRecord.m_tReturnDate = "";
				borrowRecord.m_nContinue = 0;
				m_dbUtil.AddBorrowRecord(borrowRecord);
				break;
			}
			else if (chIsBorrow == 'n' || chIsBorrow == 'N')
			{
				cout << "已取消借阅！";
				break;
			}
			else
			{
				cout << "输入有误,请重新输入:";
				cin.get();
				cin >> chIsBorrow;
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

//根据图书ID借阅书籍
bool Student::ReturnBook()
{
	Book book;
	User user;
	book.SetBookID(-1);
	vector<BorrowRecord> borrowRecords;
	if (!m_dbUtil.isOpen)
	{
		m_dbUtil.OpenDB();
	}
	//展示还未归还的图书记录
	m_dbUtil.SelectBorrowRecordByUserId(borrowRecords, m_nID, 1);
	cout << "已下是没有归还的图书" << endl;
	vector<BorrowRecord>::iterator vecIter;
	cout << "ID       书名        借阅人    借阅日期       应还日期     还书日期   续借次数" << endl;
	for (vecIter = borrowRecords.begin(); vecIter != borrowRecords.end(); vecIter++)
	{
		user = m_dbUtil.SelectUserById(vecIter->m_nUserId);
		m_dbUtil.SelectBookById(vecIter->m_nBookId, book);
		cout << setiosflags(ios::left) << setw(4) << vecIter->m_nBorrowId << "  " << setw(14) << book.GetBookName() << "  " << setw(6) << user.m_strName << "  " << setw(13) << vecIter->m_tBorrowDate << "  " << setw(13) << vecIter->m_tShouldReturnDate << "  " << setw(13) << vecIter->m_tReturnDate << "  " << setw(3) << vecIter->m_nContinue << endl;
	}
	cout << "请选择要归还图书的记录ID" << endl;
	//选择要还哪本书
	int nRecordId;
	cin >> nRecordId;



	bool bIsFind = true;
	while (bIsFind)
	{
		for (vecIter = borrowRecords.begin(); vecIter != borrowRecords.end(); vecIter++)
		{
			if (nRecordId == vecIter->m_nBorrowId)
			{
				bIsFind = false;
				break;
			}
		}
		if (vecIter == borrowRecords.end())
		{
			cout << "您所输入的ID不在记录中，请重新输入:";
			cin >> nRecordId;
		}
	}
	//还书
	m_dbUtil.FinishBorrowRecord(vecIter->m_nBorrowId, vecIter->m_nBookId);
	cout << "还书成功!" << endl;

	bIsFind = true;
	while (bIsFind)
	{
		for (vecIter = borrowRecords.begin(); vecIter != borrowRecords.end(); vecIter++)
		{
			if (nRecordId == vecIter->m_nBorrowId)
			{
				bIsFind = false;
				//计算逾期天数
				string shouldreturnyear, shouldreturnmonth, shouldreturnday;
				shouldreturnyear = vecIter->m_tShouldReturnDate.substr(0, 4);
				shouldreturnmonth = vecIter->m_tShouldReturnDate.substr(5, 2);
				shouldreturnday = vecIter->m_tShouldReturnDate.substr(8, 2);

				string returnyear, returnmonth, returnday;
				//returnyear是当前日期的year
				time_t tTemp = time(NULL);
				char szTime[16] = { 0 };
				m_timeUtil.TimeToString(tTemp, szTime);
				returnyear = szTime;
				returnyear = returnyear.substr(0, 4);
				returnmonth = szTime;
				returnmonth = returnmonth.substr(5, 2);
				returnday = szTime;
				returnday = returnday.substr(8, 2);


				int nShouldReturnYear, nShouldReturnMonth, nShouldReturnDay;
				nShouldReturnYear = atoi(shouldreturnyear.c_str());
				nShouldReturnMonth = atoi(shouldreturnmonth.c_str());
				nShouldReturnDay = atoi(shouldreturnday.c_str());

				int nReturnYear, nReturnMonth, nReturnDay;
				nReturnYear = atoi(returnyear.c_str());
				nReturnMonth = atoi(returnmonth.c_str());
				nReturnDay = atoi(returnday.c_str());

				int nOutDate = 0;
				if (nReturnYear > nShouldReturnYear)
				{
					nOutDate = (nReturnYear - nShouldReturnYear) * 365 + (nReturnMonth - nShouldReturnMonth) * 30 + (nReturnDay - nShouldReturnDay);
				}
				else if (nReturnYear == nShouldReturnYear)
				{
					if (nReturnMonth > nShouldReturnMonth)
					{
						nOutDate = (nReturnMonth - nShouldReturnMonth) * 30 + (nReturnDay - nShouldReturnDay);
					}
					else if (nReturnMonth == nShouldReturnMonth)
					{
						if (nReturnDay > nShouldReturnDay)
						{
							nOutDate = nReturnDay - nShouldReturnDay;
						}
					}
				}
				cout << "逾期天数为:" << nOutDate << endl;
				//根据逾期天数计算罚款
				double nFine = 0;
				if (nOutDate >= 0 && nOutDate <= 30)
				{
					nFine = nOutDate * 0.01;
				}
				else if (nOutDate <= 60) {
					nFine = 30 * 0.01 + (nOutDate - 30) * 0.05;
				}
				else {
					nFine = 30 * 0.01 + 30 * 0.05 + (nOutDate - 60) * 0.2;
				}
				cout << "罚款金额为:" << nFine << endl;
				break;
			}
		}
	}



	cin.get();
	cin.get();
	return true;
}

//展示个人借阅记录
bool Student::ShowMyBorrowRecord()
{
	vector<BorrowRecord> borrowRecords;
	if (!m_dbUtil.isOpen)
	{
		m_dbUtil.OpenDB();
	}

	m_dbUtil.SelectBorrowRecordByUserId(borrowRecords, m_nID, 2);
	User user;
	Book book;
	cout << "以下是您的所有借阅记录:" << endl;
	vector<BorrowRecord>::iterator vecIter;
	cout << "ID       书名        类别        借阅人    借阅日期       应还日期     还书日期   续借次数" << endl;
	for (vecIter = borrowRecords.begin(); vecIter != borrowRecords.end(); vecIter++)
	{
		user = m_dbUtil.SelectUserById(vecIter->m_nUserId);
		m_dbUtil.SelectBookById(vecIter->m_nBookId, book);
		cout << setiosflags(ios::left) << setw(4) << vecIter->m_nBorrowId << "  " << setw(14) << book.GetBookName() << "  " << setw(6) << book.GetClassify() << "  " << setw(6) << user.m_strName << "  " << setw(13) << vecIter->m_tBorrowDate << "  " << setw(13) << vecIter->m_tShouldReturnDate << "  " << setw(13) << vecIter->m_tReturnDate << "  " << setw(3) << vecIter->m_nContinue << endl;
	}
	cin.get();
	cin.get();
	return true;
}

//续借图书
bool Student::RenewBook()
{
	Book book;
	User user;
	book.SetBookID(-1);
	vector<BorrowRecord> borrowRecords;
	if (!m_dbUtil.isOpen)
	{
		m_dbUtil.OpenDB();
	}
	//展示还未归还的图书记录
	m_dbUtil.SelectBorrowRecordByUserId(borrowRecords, m_nID, 1);
	cout << "以下是没有归还的图书" << endl;
	vector<BorrowRecord>::iterator vecIter;
	cout << "ID       书名        类别        借阅人    借阅日期       应还日期     还书日期   续借次数" << endl;
	for (vecIter = borrowRecords.begin(); vecIter != borrowRecords.end(); vecIter++)
	{
		user = m_dbUtil.SelectUserById(vecIter->m_nUserId);
		m_dbUtil.SelectBookById(vecIter->m_nBookId, book);
		cout << setiosflags(ios::left) << setw(4) << vecIter->m_nBorrowId << "  " << setw(14) << book.GetBookName() << "  " << setw(6) << book.GetClassify() << "  " << setw(6) << user.m_strName << "  " << setw(13) << vecIter->m_tBorrowDate << "  " << setw(13) << vecIter->m_tShouldReturnDate << "  " << setw(13) << vecIter->m_tReturnDate << "  " << setw(3) << vecIter->m_nContinue << endl;
	}
	cout << "请选择要续借图书的记录ID" << endl;

	//选择要续借哪本书
	int nRecordId;
	cin >> nRecordId;
	bool bIsNotFind = true;
	bool bCanContinue = false;
	while (bIsNotFind)
	{
		for (vecIter = borrowRecords.begin(); vecIter != borrowRecords.end(); vecIter++)
		{
			if (nRecordId == vecIter->m_nBorrowId)
			{
				bIsNotFind = false;
				if (vecIter->m_nContinue > 0)
				{
					bCanContinue = false;
				}
				else
				{
					bCanContinue = true;
				}

				break;
			}
		}
		if (vecIter == borrowRecords.end())
		{
			cout << "您所输入的ID不在记录中，请重新输入:";
			cin >> nRecordId;
		}
	}

	if (true == bCanContinue)
	{
		m_dbUtil.ExtendBorrowRecord(nRecordId);
		cout << "续借成功!" << endl;
	}
	else
	{
		cout << "此书籍已经续借过一次，无法再次续借" << endl;
	}

	cin.get();
	cin.get();
	return true;

}