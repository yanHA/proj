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
	void *context = zmq_init(1);       //初始化上下文context

	void *responder = zmq_socket(context, ZMQ_REP);  //REP类型socket
	int rc = zmq_bind(responder, "tcp://127.0.0.1:5555");
	assert(rc == 0);
	//rc = zmq_setsockopt(responder, ZMQ_SUBSCRIBE, "proc_", 5);

	while(1)
	{
		//char buffer[10];
		//等待下一个客户端的request
		zmq_msg_t request;           //创建消息结构
		zmq_msg_init_size(&request, 10);      //初始化空得消息
		zmq_recv(responder,&request, 10, 0);
		printf("Received Hello\n");
		zmq_msg_close(&request);

		Sleep(1);

		//向客户端发送消息
		zmq_msg_t reply;
		zmq_msg_init_size(&reply, 5);        //初始化5个字节的罅隙内容来容纳"World"
		memcpy(zmq_msg_data(&reply), "World", 5);  //拷贝到消息体结构中
		zmq_send(responder, &reply, 5, 0);    //发消息到管道，等待io_thread从管道中读取后发送
		zmq_msg_close(&reply);

	}

	zmq_close(responder);
	zmq_term(context);

	return 0;
}