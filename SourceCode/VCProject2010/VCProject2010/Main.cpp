//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
#include "stdafx.h"

#include "CommonClass.h"
#include "ModelTest.h"
#include <cstdio>
#include "Cursor.h"
#include "Device.h"
#include "Optional.h"
#include "ObjectSet.h"
#include "DemoRotatingCube.h"
#include "MainBackground.h"
#include "Cursor.h"
#include <Windows.h>
#include "ObjModel.h"

static Engine::ObjectSet<Engine::GameObject> root;

///////////////////////////////////////////////////////////////////////////////////////////
//
// ���������
//
//////////////////////////////////////////////////////////////////////////////////////////

static Engine::Cursor& GetMouseCursor()
{
	static Engine::Cursor cur;
	return cur;
}

namespace Engine
{
	void ShowCursor(bool b)
	{
		b ?
			GetMouseCursor().Show() :
			GetMouseCursor().Hide();
	}
}

int PASCAL WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR     lpCmdLine,
                   int       nCmdShow)
{
	// ��ʼ����Ϸ����
	if( !CSystem::InitGameEngine( hInstance, lpCmdLine ) )
		return 0;

	// To do : �ڴ�ʹ��API���Ĵ��ڱ���
	const std::string WindowTitle{ "Rotating Cube" };

	CSystem::SetWindowTitle(WindowTitle.c_str());

	const HWND hWnd = FindWindow("Darkstar Window Class", WindowTitle.c_str());

	Engine::InitDevice(hWnd);
	auto& device = Engine::GetDevice();

	
	root.NewObject<Game::EngineTests::ModelTest>("box");

	// ������ѭ����������Ļͼ��ˢ�µȹ���
	while(device.EngineMainLoop())
	{
		// ��ȡ���ε���֮���ʱ�����ݸ���Ϸ�߼�����
		const float	fTimeDelta	=	CSystem::GetTimeDelta();

		root.Update(fTimeDelta);
		root.Draw();

		GetMouseCursor().Update(fTimeDelta);
		GetMouseCursor().Draw();
	};

	// �ر���Ϸ����
	CSystem::ShutdownGameEngine();

	return 0;
}


#pragma region Misc
#pragma warning(disable:4996)
extern "C"
{
	int _sprintf(char* buffer, const char* format, ...)
	{
		va_list args;
		va_start(args, format);
		int r = sprintf(buffer, format, args);
		va_end(args);
		return r;
	}
};

//==========================================================================
//
// ���沶׽����ƶ���Ϣ�󣬽����õ�������
// ���� fMouseX, fMouseY��Ϊ��굱ǰ����
//
void CSystem::OnMouseMove(const float fMouseX, const float fMouseY)
{
	

}
//==========================================================================
//
// ���沶׽�������Ϣ�󣬽����õ�������
// ���� iMouseType����갴��ֵ���� enum MouseTypes ����
// ���� fMouseX, fMouseY��Ϊ��굱ǰ����
//
void CSystem::OnMouseClick(const int iMouseType, const float fMouseX, const float fMouseY)
{
}
//==========================================================================
//
// ���沶׽��굯����Ϣ�󣬽����õ�������
// ���� iMouseType����갴��ֵ���� enum MouseTypes ����
// ���� fMouseX, fMouseY��Ϊ��굱ǰ����
//
void CSystem::OnMouseUp(const int iMouseType, const float fMouseX, const float fMouseY)
{
}
//==========================================================================
//
// ���沶׽���̰�����Ϣ�󣬽����õ�������
// ���� iKey�������µļ���ֵ�� enum KeyCodes �궨��
// ���� iAltPress, iShiftPress��iCtrlPress�������ϵĹ��ܼ�Alt��Ctrl��Shift��ǰ�Ƿ�Ҳ���ڰ���״̬(0δ���£�1����)
//
void CSystem::OnKeyDown(const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress)
{
	// �����ڴ������Ϸ��Ҫ����Ӧ����
}
//==========================================================================
//
// ���沶׽���̵�����Ϣ�󣬽����õ�������
// ���� iKey������ļ���ֵ�� enum KeyCodes �궨��
//
void CSystem::OnKeyUp(const int iKey)
{
	// �����ڴ������Ϸ��Ҫ����Ӧ����
}

//===========================================================================
//
// ���沶׽�������뾫����ײ֮�󣬵��ô˺���
// ����֮��Ҫ������ײ�������ڱ༭�����ߴ��������þ��鷢�ͼ�������ײ
// ���� szSrcName��������ײ�ľ�������
// ���� szTarName������ײ�ľ�������
//
void CSystem::OnSpriteColSprite(const char *szSrcName, const char *szTarName)
{
	// �����ڴ������Ϸ��Ҫ����Ӧ����
}

//===========================================================================
//
// ���沶׽������������߽���ײ֮�󣬵��ô˺���.
// ����֮��Ҫ������ײ�������ڱ༭�����ߴ��������þ��������߽�����
// ���� szName����ײ���߽�ľ�������
// ���� iColSide����ײ���ı߽� 0 ��ߣ�1 �ұߣ�2 �ϱߣ�3 �±�
//
void CSystem::OnSpriteColWorldLimit(const char *szName, const int iColSide)
{
	// �����ڴ������Ϸ��Ҫ����Ӧ����
}


#pragma endregion
