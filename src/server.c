/*************************************************************************
	 File Name: server.c
	 Author: Jacky.Tao 
	 Mail: migrant.tao@gmail.com 
	 Created Time: 2014年10月15日 星期三 18时43分04秒
 ************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>


int main(int argc, char *argv[])
{
            int sockfd,new_fd;
            struct sockaddr_in server_addr;
            struct sockaddr_in client_addr;
            int sin_size,portnumber;
            char hello[]="Hello! Are You Fine?\n";

            if(argc!=2)
    {
                        fprintf(stderr,"Usage:%s portnumber\a\n",argv[0]);
                        exit(1);
                
    }

            if((portnumber=atoi(argv[1]))<0)
    {
                        fprintf(stderr,"Usage:%s portnumber\a\n",argv[0]);
                        exit(1);
                
    }

            /* 鏈嶅姟鍣ㄧ寮�濮嬪缓绔媠ocket鎻忚堪绗� */
            if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)  
    {
                        fprintf(stderr,"Socket error:%s\n\a",strerror(errno));
                        exit(1);
                
    }

            /* 鏈嶅姟鍣ㄧ濉厖 sockaddr缁撴瀯  */ 
            bzero(&server_addr,sizeof(struct sockaddr_in));
            server_addr.sin_family=AF_INET;
            server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
            server_addr.sin_port=htons(portnumber);

            /* 鎹嗙粦sockfd鎻忚堪绗�  */ 
            if(bind(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))==-1)
    {
                        fprintf(stderr,"Bind error:%s\n\a",strerror(errno));
                        exit(1);
                
    }

            /* 鐩戝惉sockfd鎻忚堪绗�  */
                    if(listen(sockfd,5)==-1)
    {
                        fprintf(stderr,"Listen error:%s\n\a",strerror(errno));
                        exit(1);
                
    }

            while(1)
            {
                                /* 鏈嶅姟鍣ㄩ樆濉�,鐩村埌瀹㈡埛绋嬪簭寤虹珛杩炴帴  */
                                sin_size=sizeof(struct sockaddr_in);
                                if((new_fd=accept(sockfd,(struct sockaddr *)(&client_addr),&sin_size))==-1)
                {
                                            fprintf(stderr,"Accept error:%s\n\a",strerror(errno));
                                            exit(1);
                                    
                }

                                fprintf(stderr,"Server get connection from %s\n",
                                                       inet_ntoa(client_addr.sin_addr));
                                if(write(new_fd,hello,strlen(hello))==-1)
                {
                                            fprintf(stderr,"Write Error:%s\n",strerror(errno));
                                            exit(1);
                                    
                }
                                /* 杩欎釜閫氳宸茬粡缁撴潫     */
                                close(new_fd);
                                /* 寰幆涓嬩竴涓�     */  
                                        
            }
                    close(sockfd);
                            exit(0);

}

