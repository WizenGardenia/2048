#include "stdafx.h"
#include <MMSystem.h>
#include <Digitalv.h>
#include "musicplayer.h"

#pragma comment(lib, "Winmm.lib")

//��������ȫ�ֱ���
HWND m_hWnd;
DWORD DeviceId;
MCI_OPEN_PARMS mciopenparms;

//����
void Load(HWND hWnd, CString strFilepath)
{
	m_hWnd = hWnd;
	mciSendCommand(DeviceId, MCI_CLOSE, 0, 0); //�ڼ����ļ�ǰ�������һ�β��ŵ��豸
	mciopenparms.lpstrElementName = strFilepath; //�������ļ�·�������豸
	DWORD dwReturn;
	if (dwReturn = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_WAIT, (DWORD)(LPVOID)&mciopenparms))
	{
		//������ļ�ʧ��,��������Ϣ������buffer,����ʾ������
		char buffer[256];
		mciGetErrorString(dwReturn, buffer, 256); //��ȡ�������Ӧ�Ĵ�����Ϣ
		MessageBox(hWnd, buffer, "�����棡", MB_ICONHAND | MB_ICONERROR | MB_ICONSTOP); //����������Ϣ��ʾ�Ի���
	}
	DeviceId = mciopenparms.wDeviceID;
	//���ļ��ɹ��͹����ļ����豸
}

//����
void play()
{
	MCI_PLAY_PARMS mciplayparms;
	mciplayparms.dwCallback = (DWORD)m_hWnd;
	mciplayparms.dwFrom = 0; //ÿ�β��Ŷ��Ǵ�0��ʼ����
	mciSendCommand(DeviceId, MCI_PLAY, MCI_FROM | MCI_NOTIFY, (DWORD)(LPVOID)&mciplayparms);
}

//��ͣ
void pause()
{
	mciSendCommand(DeviceId, MCI_PAUSE, 0, 0);
}

//�ָ�
void resume()
{
	mciSendCommand(DeviceId, MCI_RESUME, 0, 0);
}

//ֹͣ
void stop()
{
	mciSendCommand(DeviceId, MCI_STOP, 0, 0);
	mciSendCommand(DeviceId, MCI_CLOSE, 0, 0);
	//�����ֹͣ��ťʱ,�����е���Ϣ�������
}

//��������
DWORD setVolume(DWORD vol)
{
	MCI_DGV_SETAUDIO_PARMS setvolume; //���������Ĳ����ṹ��
	setvolume.dwCallback = NULL; //
	setvolume.dwItem = MCI_DGV_SETAUDIO_VOLUME; //��������������
	setvolume.dwValue = vol; //����ֵ��vol
	mciSendCommand(DeviceId, MCI_SETAUDIO, MCI_DGV_SETAUDIO_ITEM | MCI_DGV_SETAUDIO_VALUE, (DWORD)(LPVOID)&setvolume);
	return 0;
}