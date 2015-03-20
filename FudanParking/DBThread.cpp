#include "stdafx.h"
#include "DBThread.h"
#include "ShareTypes.h"



CDBThread::CDBThread()
{
	
}

CDBThread::~CDBThread()
{
	
}


void CDBThread::DBThreadInitialize(TQueue<struct CarStatus> *carstate)
{
	char *itemName = "Section1";
	m_carstate = carstate;

	GetPrivateProfileStringA(itemName, "DataBaseIP", "192.168.1.1", m_IP, sizeof(m_IP), CONFIG_FILE_NAME);
	m_port = GetPrivateProfileIntA(itemName, "DataBasePort", 3306, CONFIG_FILE_NAME);
	GetPrivateProfileStringA(itemName, "DataUser", "root", m_user, sizeof(m_user), CONFIG_FILE_NAME);
	GetPrivateProfileStringA(itemName, "DataPassWord", "password", m_password, sizeof(m_password), CONFIG_FILE_NAME);
}

DWORD CDBThread::ThreadMemberFunc()
{
	DataConn = new CDataBaseProc;
	DataConn->ConnectDataBase(m_IP, m_port, m_user, m_password);

	char update[256];
	
	CarStatus carstatus;
	while(m_carstate != NULL)
	{
		m_carstate->Pop(carstatus);
		for(int i = 0; i < (int)carstatus.num.size(); i++)
		{
			printf("i: %d  status: %d  time: %s\n", carstatus.num[i], carstatus.status[i], carstatus.readtime);
			sprintf(update, "UPDATE sp_parkingstatus SET `status` = %d,  `modify_time` = '%s' WHERE parking_space_id = %d", carstatus.status[i], carstatus.readtime, carstatus.num[i]);
			DataConn->updateDatabase(update);
		}
		
	}

	DataConn->CloseConnect();

	return 0;
}