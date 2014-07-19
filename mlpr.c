
#include "mlpr.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <string.h>
#include <stdio.h>


int 
mlpr_open (mlpr_ctx * ctx, char * portname, speed_t baud)
{
	ctx->fd = open (portname, O_RDWR | O_NOCTTY);
	if (ctx->fd < 0) {
	
		return -1;
	}


	ctx->ret = tcgetattr (ctx->fd, &ctx->old);
	if (ctx->ret < 0 ) {
		return -1;
	}

	cfsetospeed (&ctx->opt, baud);
	cfsetispeed (&ctx->opt, baud);

	
	ctx->opt.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
	ctx->opt.c_iflag &= ~(ICRNL | INLCR | IXON | IXOFF);
	ctx->opt.c_oflag &= ~(OCRNL | ONLCR);
	ctx->opt.c_cflag &= ~(PARENB | CSTOPB | CSIZE);
	ctx->opt.c_cflag |= CS8;

	ctx->ret = tcsetattr (ctx->fd, TCSANOW, &ctx->opt);

	if (ctx->ret < 0) {

		return -1;
	}

	return 0;
}


int 
mlpr_getstatus (mlpr_ctx * ctx)
{
	char cmd[] = {16, 4, 2};
	struct timeval tv;
	fd_set rset;
	unsigned char ans = 0;
	
	ctx->ret = write (ctx->fd, write, sizeof (cmd));
	if (ctx->ret < 0) {
	
		return -1;
	}
	
	FD_ZERO (&rset);
	FD_SET ( ctx->fd, &rset);
	tv = (struct timeval) {0, 500000};
	ctx->ret = select (ctx->fd + 1, &rset, NULL, NULL, &tv);

	if (!ctx->ret || FD_ISSET (ctx->fd, &rset))	{
		// ofline 
		return -1;
	}
	
	ctx->ret = read (ctx->fd, &ans, sizeof (unsigned char));
	if (ctx->ret < 0) {
		return -1;
	}
	
	switch (ans)	{
	
	case 0x12: 
		break;
	case 0x32: 
		break;
	case 0x36: 
		break;
	default : 
		break;
	
	};
	
	return (int ) ans;
}


int 
mlpr_chfont (mlpr_ctx * ctx, int fontsize)
{
	unsigned char cmd[4];
	snprintf (cmd, sizeof(cmd), "%c%c%c", 27, 33, fontsize);
	return ctx->ret = write (ctx->fd, cmd, 3);
}


int 
mlpr_rstfont (mlpr_ctx * ctx)
{
	unsigned char cmd[4];
	snprintf (cmd, sizeof(cmd), "%c%c%c", 27, 64, 0);
	return ctx->ret = write (ctx->fd, cmd, 3);
}


int 
mlpr_cutpaper (mlpr_ctx * ctx)
{
	char cmd[5];
	snprintf (cmd, sizeof(cmd), "%c%c%c%c", 29, 86, 1, 10);
	return ctx->ret = write (ctx->fd, cmd, 4);
}


int 
mlpr_close (mlpr_ctx * ctx)
{
	tcsetattr (ctx->fd, TCSANOW, &ctx->old);
	close (ctx->fd);
}

int 
mlpr_newline (mlpr_ctx * ctx)
{
	unsigned char cmd = 0x0a;
	return ctx->ret = write (ctx->fd, &cmd, sizeof (unsigned char));	
}

int 
mlpr_println (mlpr_ctx * ctx, char * str)
{
	return 0;
}

int 
mlpr_printpic (mlpr_ctx * ctx, char * imagename)
{
	
	return 0;
}

