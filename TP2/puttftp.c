#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>


//#define EXIT_FAILURE -1
#define EXIT_SUCCESS 0

int main(int argc, char *argv[]){
	char *fileName;
	char *server;
	int s,sfd;
	
	
	struct addrinfo hints = {0};
    struct addrinfo *res, *tmp;
    
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;
    
	if(argc!=3){
		printf("Incorrect number of argument : expected 2");
		return(EXIT_FAILURE);
	}
	
	server = argv[2];
	fileName = argv[1];
	
	s = getaddrinfo(server, "1069", &hints, &res);
	if(s!=0){
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}
	
	for (tmp = res; tmp !=NULL; tmp = tmp->ai_next){
		sfd=socket(tmp->ai_family, tmp->ai_socktype, tmp->ai_protocol);
		if(sfd==-1) continue;
		if(connect(sfd, tmp->ai_addr, tmp->ai_addrlen)!=-1)break;
		close(sfd);
		
	}
	
	printf("Welcome to %s, to upload: %s \n",server, fileName);
	//printf("adress : %d\nfamily: %d, socktype: %d,  protocol: %d\n", res->ai_addr, res->ai_family, res->ai_socktype, res->ai_protocol);


	freeaddrinfo(res);
	close(sfd);              //problème principale du programme, si j'ajoute cette line j'otient une erreur parceque je free 2x une variable, sinon j'obtient un segmentation fault
	
	
}

