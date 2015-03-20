#include "stdafx.h"
#include "DataBaseProc.h"

CDataBaseProc::CDataBaseProc()
{

}

CDataBaseProc::~CDataBaseProc()
{

}

//�������ݿ�
BOOL CDataBaseProc::ConnectDataBase(char *ip, int port, char *user, char *password)
{
	m_ip = ip;
	m_port = port;
	m_user = user;
	m_password = password;

	mysql_init(&m_mysql);

	if(!mysql_real_connect(&m_mysql, m_ip, m_user, m_password, "icvmp_smartpark", m_port, NULL, 0))
	{
		printf("Connect DataBase failed with %s\n", mysql_error(&m_mysql));
		return 0;
	}
	else
	{
		printf("Connect DataBase Success...\n");
		return 1;
	}
}

//�������ݿ��г�λ״̬
BOOL CDataBaseProc::updateDatabase(char *query)
{
	int update_result; 
	update_result = mysql_real_query(&m_mysql, query, (unsigned int) strlen(query));

	if(update_result)
	{
		printf("error making query: %s\n", mysql_error(&m_mysql));
		return 0;
	}
	else
	{
		return 1;
	}
}

//�ر����ݿ�����

BOOL CDataBaseProc::CloseConnect()
{
	mysql_close(&m_mysql);
	return 1;
}