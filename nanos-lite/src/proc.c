#include <proc.h>

#define MAX_NR_PROC 4

static PCB pcb[MAX_NR_PROC] __attribute__((used)) = {};
static PCB pcb_boot = {};
PCB *current = NULL;

void naive_uload(PCB *pcb, const char *filename);
void context_uload(PCB* p, const char *filename, char *const argv[], char *const envp[]);
void context_kload(PCB* p, void (*entry)(void *), void* arg);

void switch_boot_pcb() {
  current = &pcb_boot;
}

void hello_fun(void *arg) {
  int j = 1;int _fun_count = 1;
  while (1) {
    if(j==100000){
			Log("Hello World from Nanos-lite with arg '%s' for the %dth time!", (char *)arg, _fun_count);
			_fun_count++; j = 0;
			yield();
		}
//		yield();
		j ++;
  }
}

void init_proc() {
	//memset(pcb, 0, sizeof(pcb));
//	context_kload(&pcb[0], hello_fun, "AAAAAA");
	//context_kload(&pcb[1], hello_fun, "ZZZZZZ");
	char *arg1[] = {"/bin/exec-test","1", NULL};
	//char *arg2[] = {"/bin/cat", "/share/games/bird/atlas.txt", NULL};
	char *empty[] = {NULL};
 // context_uload(&pcb[0], "/bin/hello", arg1, empty);
	context_uload(&pcb[0], "/bin/nterm", empty, empty);
//	printf("arg1: %s, arg2: %s\n", arg1[0], arg2[0]);
	context_uload(&pcb[1], "/bin/hello", arg1, empty);
	pcb[0].prio = 64;
	switch_boot_pcb();

  Log("Initializing processes...");

  // load program here
	// naive_uload(NULL, "/bin/menu");
}

Context* schedule(Context *prev) {
	static int curr_pcb_id = 0;
	static int count = 1;
	current->cp = prev;

	if(count < current->prio){
		count++;
		return current->cp;
	}
	count = 1;
	do{
		curr_pcb_id++;
		curr_pcb_id %= MAX_NR_PROC;
		//printf("check %d prio: %d\n", curr_pcb_id, pcb[curr_pcb_id].prio);
	} while(pcb[curr_pcb_id].prio==0);
	//printf("schedule to %d\n", curr_pcb_id);
	current = &pcb[curr_pcb_id];

	//current = (current == &pcb[0] ? &pcb[1]:&pcb[0]);
  return current->cp;
}
