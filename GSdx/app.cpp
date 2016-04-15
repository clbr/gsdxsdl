#include <stdio.h>

extern "C" {

int GSinit();
void GSconfigure();
const char *PS2EgetLibName();
int GSopen(void** dsp, const char* title, int mt);

}

int main() {

	void *dsp = NULL;

	printf("gsinit: %d, lib %s\n", GSinit(), PS2EgetLibName());
	printf("gsopen: %d\n", GSopen(&dsp, "Hello Title", 1));

	return 0;
}
