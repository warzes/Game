#include "stdafx.h"
#include "Keyboard.h"

//-----------------------------------------------------------------------------
// Keyboard.
//-----------------------------------------------------------------------------

Keyboard& Keyboard::Get()
{
	static Keyboard theInstance;
	return theInstance;
}

Keyboard::Keyboard()
{
	m_lastChar = 0;
	m_pCurrKeyStates = m_keyStates[0];
	m_pPrevKeyStates = m_keyStates[1];

	memset(m_pCurrKeyStates, 0, 256);
	memset(m_pPrevKeyStates, 0, 256);
}

void Keyboard::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CHAR:
		m_lastChar = static_cast<int>(wParam);
		break;

	default:
		break;
	}
}

void Keyboard::Update()
{
	BYTE* pTempKeyStates = m_pPrevKeyStates;

	m_pPrevKeyStates = m_pCurrKeyStates;
	m_pCurrKeyStates = pTempKeyStates;

	GetKeyboardState(reinterpret_cast<BYTE*>(m_pCurrKeyStates));
}