#include <stdlib.h>
#include "Application.h"
#include "Globals.h"
#include "SDL/include/SDL.h"
#include <malloc.h>

#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )

enum main_states
{
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};

Application* App = nullptr;

int main(int argc, char ** argv)
{
	int main_return = EXIT_FAILURE;
	main_states state = MAIN_CREATION;

	while (state != MAIN_EXIT)
	{
		switch (state)
		{
		case MAIN_CREATION:

			LOG("Application Creation --------------");
			App = new Application();
			state = MAIN_START;
			break;
		case MAIN_START:

			LOG("Application Init --------------");
			if (App->Init() == false)
			{
				LOG("Application Init exits with error -----");
				state = MAIN_EXIT;
			}
			else
			{
				state = MAIN_UPDATE;
				LOG("Application Update --------------");
			}
			if (_heapchk() != _HEAPOK)
			break;

		case MAIN_UPDATE:
		{
			int update_return = App->Update();

			//keep it just in debug mode
			//int  heapstatus;
			//char *buffer;

			//// Allocate and deallocate some memory  
			//if ((buffer = (char *)malloc(100)) != NULL)
			//	free(buffer);

			//// Check heap status  
			//heapstatus = _heapchk();
			//switch (heapstatus)
			//{
			//case _HEAPOK:
			//	printf(" OK - heap is fine\n");
			//	break;
			//case _HEAPEMPTY:
			//	printf(" OK - heap is empty\n");
			//	break;
			//case _HEAPBADBEGIN:
			//	printf("ERROR - bad start of heap\n");
			//	break;
			//case _HEAPBADNODE:
			//	printf("ERROR - bad node in heap\n");
			//	break;
			//}

			if (update_return == UPDATE_ERROR)
			{
				LOG("Application Update exits with error -----");
				state = MAIN_EXIT;
			}

			if (update_return == UPDATE_STOP)
				state = MAIN_FINISH;
		}
			break;

		case MAIN_FINISH:

			LOG("Application CleanUp --------------");
			if (App->CleanUp() == false)
			{
				LOG("Application CleanUp exits with error -----");
			}
			else
				main_return = EXIT_SUCCESS;

			state = MAIN_EXIT;

			break;

		}
	}

	RELEASE( App);
	LOG("Bye :)\n");
	return main_return;
}