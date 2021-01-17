#pragma once

//-----------------------------------------------------------------------------
// Mouse.
//-----------------------------------------------------------------------------

class Mouse
{
public:
	enum MouseButton
	{
		BUTTON_LEFT = 0,
		BUTTON_RIGHT = 1,
		BUTTON_MIDDLE = 2
	};

	static Mouse& Get();

	bool ButtonDown(MouseButton button) const
	{
		return m_pCurrButtonStates[button];
	}

	bool ButtonPressed(MouseButton button) const
	{
		return m_pCurrButtonStates[button] && !m_pPrevButtonStates[button];
	}

	bool ButtonUp(MouseButton button) const
	{
		return !m_pCurrButtonStates[button];
	}

	bool CursorIsVisible() const
	{
		return m_cursorVisible;
	}

	bool IsMouseSmoothing() const
	{
		return m_enableFiltering;
	}

	int xPosAbsolute() const
	{
		return m_xPosAbsolute;
	}

	int yPosAbsolute() const
	{
		return m_yPosAbsolute;
	}

	float xPosRelative() const
	{
		return m_xPosRelative;
	}

	float yPosRelative() const
	{
		return m_yPosRelative;
	}

	float WeightModifier() const
	{
		return m_weightModifier;
	}

	float WheelPos() const
	{
		return m_mouseWheel;
	}

	bool Attach(HWND hWnd);
	void Detach();
	void HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void HideCursor(bool hideCursor);
	void SetPosition(UINT x, UINT y);
	void SetWeightModifier(float weightModifier);
	void SmoothMouse(bool smooth);
	void Update();

private:
	Mouse();
	Mouse(const Mouse&);
	Mouse& operator=(const Mouse&);
	~Mouse();

	void performMouseFiltering(float x, float y);
	void performMouseSmoothing(float x, float y);

	static const float WEIGHT_MODIFIER;
	static const int HISTORY_BUFFER_SIZE = 10;
	static const int TEMP_BUFFER_SIZE = 40;

	static BYTE m_tempBuffer[TEMP_BUFFER_SIZE];

	HWND m_hWnd;
	int m_xPosAbsolute;
	int m_yPosAbsolute;
	int m_historyBufferSize;
	int m_mouseIndex;
	int m_wheelDelta;
	int m_prevWheelDelta;
	float m_mouseWheel;
	float m_xPosRelative;
	float m_yPosRelative;
	float m_weightModifier;
	float m_filtered[2];
	float m_history[HISTORY_BUFFER_SIZE * 2];
	float m_mouseMovementX[2];
	float m_mouseMovementY[2];
	bool m_cursorVisible;
	bool m_enableFiltering;
	bool m_buttonStates[2][3];
	bool* m_pCurrButtonStates;
	bool* m_pPrevButtonStates;
};