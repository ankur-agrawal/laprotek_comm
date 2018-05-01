#include "RosBridge.h"

Server server(1500);

void siginthandler(int param)
{
  server.closeConnection();
  exit(1);
}

int main(int argc, char **argv)
{
  RosBridge<Server> Bridge(&server);
  // char *param;
  // param[0]='R';
  // std::cout << argc << '\t'<< argv[1] << '\n';
  if (argc==2 && !strcmp(argv[1], "ROS"))
  {
    Bridge.init();
    std::cout << "ROS Node started and initialised" << '\n';
  }
  else
  {
    std::cout << "No ROS topic will be generated" << '\n';
  }

  while(1)
  {
    signal(SIGINT, siginthandler);
    server.initSocket();
    if (!server.ConnectToClient())
    {
      return -1;
    }
    while(1)
    {
      if (argc==2 && !strcmp(argv[1], "ROS"))
      {
        ros::spinOnce();
        Bridge.setFuncPtr3(&Server::getRosWrenches);
        Bridge.setWrenches();
      }
      server.PackData();
      if (!server.SendData())
      {
        break;
      }
      server.ReceiveData();
      server.UnpackData();

      if (argc==2 && !strcmp(argv[1], "ROS"))
      {
        Bridge.setFuncPtr(&Server::getRosPoses);
        Bridge.setPoses();
        Bridge.setFuncPtr2(&Server::getRosJoints);
        Bridge.setJoints();

        Bridge.publishPoses();
        Bridge.publishJoints();
      }
    }
    server.closeConnection();
  }
}
