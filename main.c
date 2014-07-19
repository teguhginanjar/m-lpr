#include "mlpr.h"


int 
main ()
{
	mlpr_ctx ctx;
	//struct _mlpr ctx;
	mlpr_open (&ctx, "/dev/ttyUSB0", B19200);
	
	return 0;
}
