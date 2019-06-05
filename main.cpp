#include <stdio.h>
#include <QtGui>
#include <QApplication>
#include "soccerview.h"
#include "timer.h"
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <thread>
#define PORT 8881
#define ssl_port 10006
#define IP "127.0.0.1"

GLSoccerView *view;

bool runApp = true;

void geometry(){
	static const double minDuration = 0.01; // 100FPS
	RoboCupSSLClient client(ssl_port);
	client.open(false);
	SSL_WrapperPacket packet;
	while(true){
		while(client.receive(packet)){
			if(packet.has_geometry()){
				view->updateFieldGeometry(packet.geometry().field());
			}
		}
		Sleep(minDuration);
	}
}

void ball_players(){
    pacote info_packet;

	// criacao do socket
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){ 
        cout << "Erro durante a criacao do socket" << endl; 
        exit(-1);
    }
    // zerando o address e setando logo em seguida
	memset(&serv_addr, '0', sizeof(serv_addr)); 
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
    
	// verificando endereco do socket
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0){ 
        cout << "Endereco invalido" << endl;
        exit(-1);
    }
	
	// esperando recepção das mensagens
    while(true){
    	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) >= 0){ 
    		valread = read(sock, &info_packet, sizeof(pacote)); 
    		while(valread){
        		view->updateNewDetection(info_packet); // atualizando o frame do cliente gráfico com as informações
        		valread = read(sock, &info_packet, sizeof(pacote));
        	}
    	}
    }
}

int main(int argc, char **argv){
	// inicializando o cliente gráfico
	QApplication app(argc, argv);
	QStringList arguments = QCoreApplication::arguments();
	view = new GLSoccerView();
	view->show();

	// inicializando as threads
    thread first(ball_players);
    first.detach();
	thread second(geometry);
	second.detach();
	
	int retVal = app.exec();
	runApp = false;
	return retVal;
}