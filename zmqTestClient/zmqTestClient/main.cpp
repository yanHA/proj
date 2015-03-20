/** Hello World client
 ** Connect REQ socket to tcp://localhost:5555
 ** Sends "Hello" to server, expects "World" back
 **/

#include <zmq.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

int main(void)
{
	void *context = zmq_init(1);     //创建上下文，初始化一个io_thread

	//Socket to talk to server
	printf("Connecting to hello world server...\n");

	void *requester = zmq_socket(context, ZMQ_REQ);
	zmq_connect(requester, "tcp://localhost:5555");       //连接到端点

	int request_nbr;
	for(request_nbr = 0; request_nbr != 10; request_nbr++)
	{
		zmq_msg_t request;         //建立request的消息结构
		zmq_msg_init_size(&request, 10);     //初始化request消息体结构
		memcpy(&request, "Hello", 10);
		printf("Sending Hello World! ...\n", request_nbr);
		zmq_send(requester, &request, 10, 0);
		//zmq_msg_close(&request);

		zmq_msg_t reply;
		zmq_msg_init_size(&reply, 10);
		zmq_recv(requester, &reply, 10, 0);
		printf("Receive World %d...\n", request_nbr);
		//zmq_msg_close(&reply);

		system("pause");
	}

	zmq_close(&requester);
	zmq_ctx_term(context);

	return 0;
}