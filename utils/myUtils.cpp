#include "myUtils.h"

void myUtils::setNonBlock(int fd){
	int flag = fcntl(fd, F_GETFL);
	flag |= O_NONBLOCK;
	fcntl(fd, F_SETFL, flag);
}

void myUtils::fdAdd(int ep, int fd, bool oneShot) {
	epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLIN | EPOLLET | EPOLLRDHUP;
	if(oneShot) event.events |= EPOLLONESHOT;
	epoll_ctl(ep, EPOLL_CTL_ADD, fd, &event);
	setNonBlock(fd);
}

void myUtils::fdRemove(int ep, int fd) {
	epoll_ctl(ep, EPOLL_CTL_DEL, fd, nullptr);
	close(fd);
}

void myUtils::fdMode(int ep, int fd, int ev) {
	epoll_event event;
	event.data.fd = fd;
	event.events = ev | EPOLLET | EPOLLONESHOT | EPOLLRDHUP;
	epoll_ctl(ep, EPOLL_CTL_MOD, fd, &event);
}

void myUtils::printMsg() {
	std::cout << "////////////////////////////////////////////////////////////////////\n"
	             "//                        五子棋游戏服务器启动                          //\n"
	             "////////////////////////////////////////////////////////////////////\n";
}
