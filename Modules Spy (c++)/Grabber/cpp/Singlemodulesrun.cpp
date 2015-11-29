#include "Singlemodulesrun.h"

pthread_t HI, SC, SI, NI, ES, SP;

void *HI_proc(void *param);
void *SC_proc(void *param);
void *SI_proc(void *param);
void *NI_proc(void *param);
void *ES_proc(void *param);
void *SP_proc(void *param);

void KillModules(void)
{
	pthread_cancel(HI);
	pthread_cancel(SC);
	pthread_cancel(SI);
	pthread_cancel(NI);
	pthread_cancel(ES);
	pthread_cancel(SP);
}

void SingleModulesRun(control *C)
{
	//pthread_t HI, SC, SI, NI, ES, SP;

	pthread_create(&HI, NULL, HI_proc, (void*)C);
	pthread_create(&SC, NULL, SC_proc, (void*)C);
	pthread_create(&SI, NULL, SI_proc, (void*)C);
	pthread_create(&NI, NULL, NI_proc, (void*)C);
	pthread_create(&ES, NULL, ES_proc, (void*)C);
	pthread_create(&SP, NULL, SP_proc, (void*)C);

}
void *HI_proc(void *param)
{
	control *CS = (control*)param;
	HardWareInfo(CS->run[0], "HardwareLog.txt", CS->period[0]);
	return NULL;
}
void *SC_proc(void *param)
{
	control *CS = (control*)param;
	GetSampleServiceConfig(CS->run[1], "SampleSrviceConfigLog.txt", CS->period[1]);
	return NULL;
}
void *SI_proc(void *param)
{
	control *CS = (control*)param;
	SystemInfo(CS->run[2], "SystemInfoLog.txt", CS->period[2]);
	return NULL;
}
void *NI_proc(void *param)
{
	control *CS = (control*)param;
	GetCompIP(CS->run[3], "NetworkInformationLog.txt", CS->period[3]);
	return NULL;
}
void *ES_proc(void *param)
{
	control *CS = (control*)param;
	EnumerateSerialPorts(CS->run[4], "SerialLog.txt", CS->period[4]);
	return NULL;
}
void *SP_proc(void *param)
{
	control *CS = (control*)param;
	ScanProcess(CS->run[5], "ScanProcessLog.txt", CS->period[5]);
	return NULL;
}