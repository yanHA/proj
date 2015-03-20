/** Hello World server
 ** binds REP socket to tcp://*5555
 ** Expects "Hello" from client, replies with "World"
 **/

#include <zmq.h>

#include <stdio.h>
#include <string.h>
#include <assert.h>

int main(void)
{
	void *context = zmq_init(1);       //��ʼ��������context

	void *responder = zmq_socket(context, ZMQ_REP);  //REP����socket
	int rc = zmq_bind(responder, "tcp://127.0.0.1:5555");
	assert(rc == 0);
	//rc = zmq_setsockopt(responder, ZMQ_SUBSCRIBE, "proc_", 5);

	while(1)
	{
		//char buffer[10];
		//�ȴ���һ���ͻ��˵�request
		zmq_msg_t request;           //������Ϣ�ṹ
		zmq_msg_init_size(&request, 10);      //��ʼ���յ���Ϣ
		zmq_recv(responder,&request, 10, 0);
		printf("Received Hello\n");
		zmq_msg_close(&request);

		Sleep(1);

		//��ͻ��˷�����Ϣ
		zmq_msg_t reply;
		zmq_msg_init_size(&reply, 5);        //��ʼ��5���ֽڵ���϶����������"World"
		memcpy(zmq_msg_data(&reply), "World", 5);  //��������Ϣ��ṹ��
		zmq_send(responder, &reply, 5, 0);    //����Ϣ���ܵ����ȴ�io_thread�ӹܵ��ж�ȡ����
		zmq_msg_close(&reply);

	}

	zmq_close(responder);
	zmq_term(context);

	return 0;
}