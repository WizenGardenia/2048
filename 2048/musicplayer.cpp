#include "stdafx.h"
#include <MMSystem.h>
#include <Digitalv.h>
#include "musicplayer.h"

#pragma comment(lib, "Winmm.lib")

//定义三个全局变量
HWND m_hWnd;
DWORD DeviceId;
MCI_OPEN_PARMS mciopenparms;

//加载
void Load(HWND hWnd, CString strFilepath)
{
	m_hWnd = hWnd;
	mciSendCommand(DeviceId, MCI_CLOSE, 0, 0); //在加载文件前先清空上一次播放的设备
	mciopenparms.lpstrElementName = strFilepath; //将音乐文件路径传给设备
	DWORD dwReturn;
	if (dwReturn = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_WAIT, (DWORD)(LPVOID)&mciopenparms))
	{
		//如果打开文件失败,将出错信息储存在buffer,并显示出错警告
		char buffer[256];
		mciGetErrorString(dwReturn, buffer, 256); //获取错误码对应的错误信息
		MessageBox(hWnd, buffer, "出错警告！", MB_ICONHAND | MB_ICONERROR | MB_ICONSTOP); //弹出错误信息提示对话框
	}
	DeviceId = mciopenparms.wDeviceID;
	//打开文件成功就关联文件到设备
}

//播放
void play()
{
	MCI_PLAY_PARMS mciplayparms;
	mciplayparms.dwCallback = (DWORD)m_hWnd;
	mciplayparms.dwFrom = 0; //每次播放都是从0开始播放
	mciSendCommand(DeviceId, MCI_PLAY, MCI_FROM | MCI_NOTIFY, (DWORD)(LPVOID)&mciplayparms);
}

//暂停
void pause()
{
	mciSendCommand(DeviceId, MCI_PAUSE, 0, 0);
}

//恢复
void resume()
{
	mciSendCommand(DeviceId, MCI_RESUME, 0, 0);
}

//停止
void stop()
{
	mciSendCommand(DeviceId, MCI_STOP, 0, 0);
	mciSendCommand(DeviceId, MCI_CLOSE, 0, 0);
	//当点击停止按钮时,将所有的信息都清除掉
}

//设置音量
DWORD setVolume(DWORD vol)
{
	MCI_DGV_SETAUDIO_PARMS setvolume; //设置音量的参数结构体
	setvolume.dwCallback = NULL; //
	setvolume.dwItem = MCI_DGV_SETAUDIO_VOLUME; //动作是设置音量
	setvolume.dwValue = vol; //音量值是vol
	mciSendCommand(DeviceId, MCI_SETAUDIO, MCI_DGV_SETAUDIO_ITEM | MCI_DGV_SETAUDIO_VALUE, (DWORD)(LPVOID)&setvolume);
	return 0;
}