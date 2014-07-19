#ifndef __MLPR_H__
#define __MLPR_H__

#include <termios.h>

typedef struct _mlpr
{
	struct termios old, opt;
	int fd;
	int ret;
	char portname[10];
}
mlpr_ctx;


int mlpr_open (mlpr_ctx * ctx, char * portname, speed_t baud);
int mlpr_close (mlpr_ctx * ctx);
int mlpr_cutpaper (mlpr_ctx * ctx);
int mlpr_println (mlpr_ctx * ctx, char * msg);
int mlpr_getstatus (mlpr_ctx * ctx);
int mlpr_rolpaper (mlpr_ctx * ctx, int n);
int mlpr_chfont (mlpr_ctx * ctx, int fontsize);
int mlpr_rstfont (mlpr_ctx * ctx);
int mlpr_printpic (mlpr_ctx * ctx, char * imagename);
int mlpr_newline (mlpr_ctx * ctx);





#endif 
