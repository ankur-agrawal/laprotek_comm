#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define  IP_ADDR "127.0.0.1"
#define  PORT_NUM         1500      // Port number used at the server

void SetTCPIPdata(char *data_in, char *data_out)
{
  int i=0;
  int j=0;
  int iter=0;
  int dataType; //how should the output data be? Transforms or joint angles?
  char data_substring[1];
  double Transform[2][4][4]={{{1,0,0,0.1},{0,1,0,0},{0,0,1,0},{0,0,0,1}},{{1,0,0,-0.1},{0,1,0,0},{0,0,1,0},{0,0,0,1}}};
  double Joints[2][7]={{0.1,0.2,0.3,0.4,0.5,0.6,0.7},{-0.1,-0.2,-0.3,-0.4,-0.5,-0.6,-0.7}};
  // double Joints[2][7]={{0,0,0,0,0,0,0},{0,0,0,0,0,0,0}};
  double trial=0.1;

  memcpy(data_substring,data_in, 1);
  dataType=atoi(data_substring);

  if (dataType==0)
    for (int hand=0; hand<=1; hand++)
      for (i=0; i<4; i++)
        for (j=0; j<3; j++)
        {
          snprintf(data_out+iter,9, "%08d", (int) (100000*Transform[hand][j][i]));
          iter=iter+8;
        }
  else
    for (int hand=0; hand<=1; hand++)
      for (i=0;i<7;i++)
      {
        snprintf(data_out+iter,9, "%08d", (int) (100000*Joints[hand][i]));
        iter=iter+8;
      }
}

int main(int argc, char **argv)
{
  unsigned int		client_s = 0;        			// Server socket descriptor
  struct 			sockaddr_in	server_addr;      // Server Internet address

  char				in_buf[200];     					// 500-byte input buffer for data
  char				out_buf[200];     					// 500-byte input buffer for data
  int					bytes_rec = 0;


  static int		init = 1;

  int					first = 1;
  while(1)
  {
    if(init)
    {
  	  printf("opening socket on port 1500. \n");
  	  client_s = socket(AF_INET, SOCK_STREAM, 0);

  	  server_addr.sin_family      = AF_INET;            // Address family to use
  	  server_addr.sin_port        = htons(PORT_NUM);    // Port num to use
  	  server_addr.sin_addr.s_addr = inet_addr(IP_ADDR); // IP address to use
  	  connect(client_s, (struct sockaddr *)&server_addr, sizeof(server_addr));

  	  printf("waiting on server... \n");
  	  init = 0;
    }
    while(1)
    {
  	  bytes_rec = recv(client_s, in_buf, 200, 0);
      if(bytes_rec <= 0)
      {
        printf("No Connection to server \n");
        break;
      }

      if(first)
      {
        printf("transmission started.\n");
        first = 0;
      }
      SetTCPIPdata(&in_buf[0], &out_buf[0]);
      send(client_s, out_buf, 200, 0);
    }
    sleep(5);
    init = 1;
    first = 1;
  }
}
