#ifndef DBThread_H
#define DBThread_H



#include "DataBaseProc.h"
#include "ThreadBase.h"
#include "TQueue.h"



/*****************************************************************/
/* �̳�ʵ��CThreadBase�࣬���ڽ����������ʵʱд�����ݿ���     */
/*****************************************************************/

class CDBThread : public CThreadBase
{
public:
	CDBThread();
	~CDBThread();

	void DBThreadInitialize(TQueue<struct CarStatus> *carstate);


private:
	DWORD ThreadMemberFunc();

	CDataBaseProc *DataConn;

	char           m_IP[256];
	int            m_port;
	char           m_user[256];
	char           m_password[256];
	TQueue<struct CarStatus>    *m_carstate;
};



#endif