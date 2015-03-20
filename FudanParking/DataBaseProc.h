#ifndef DataBaseProc_H
#define DataBaseProc_H

#include <mysql.h>


class CDataBaseProc
{
public:
	CDataBaseProc();
	~CDataBaseProc();

	BOOL ConnectDataBase(char *ip, int port, char *user, char *password);
	BOOL updateDatabase(char *query);
	BOOL CloseConnect();

private:

	MYSQL m_mysql;
	char *m_ip;
	char *m_user;
	char *m_password;
	int   m_port;
	char  m_update[256];
	//int   m_update_result;
};


#endif