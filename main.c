#include <stdio.h>
#include <unistd.h>
#include "altimu.h"

int main(void)
{
    I2C_init();
	LSM303DLHC_A_init();
	LSM303DLHC_M_init();
    L3GD20_init();
    LPS331AP_init();
    LSM303DLHC_A_read();
    int xcal = acc.x, ycal = acc.y, zcal = acc.z;
	
	for (;;)
	{
        LSM303DLHC_A_read();
        LSM303DLHC_M_read();
        L3GD20_read();
        //printf("%f\t%f\n", LPS331AP_readTempC(), LPS331AP_readPerssureMbar());
        printf("%d\t%d\t%d\n", acc.x-xcal, acc.y-ycal, acc.z-zcal);
		usleep(100000);
	}
	return 0;
}
