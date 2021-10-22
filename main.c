//  Group C Driver File
#include "MessagePassing.h"
#include "clientHelper.h"
#include "HunterHolstead.h"
#include "ProcessB_ThreadManagement.c"
#include "clientDriver.c"
#include "serverDriver.c"

/**
 * Arguments:
 *      void
 * Description:
 *      main driver file aka client that runs the program
 * Return type:
 *      void
*/
int main() { 
	// run clientDriver and serverDriver files
	clientDriver();
	serverDriver();
	// initialize client
    int socket_client = clientStarter();

	close(socket_client);
    return 0;
}
