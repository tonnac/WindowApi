#include "Sample.h"

class Rotate : public Object
{
public:
	bool Init()
	{
		_Angle = 0.0f;
		LoadFile(L"PLAYER", L"../02_data/bitmap1.bmp", L"../02_data/bitmap2.bmp");
		Set(400, 400, 1, 62, 44, 74);


		_RotationDC = CreateCompatibleDC(g_hOffScreenDC);
		_ColorDC = CreateCompatibleDC(g_hOffScreenDC);
		_MaskDC = CreateCompatibleDC(g_hOffScreenDC);

		_MaxLength = sqrt((m_rtDraw.right) * (m_rtDraw.right) +
			(m_rtDraw.bottom) * (m_rtDraw.bottom));

		_ColorBitmap = CreateCompatibleBitmap(g_hScreenDC, _MaxLength, _MaxLength);
		_MaskBitmap = CreateCompatibleBitmap(g_hScreenDC, _MaxLength, _MaxLength);

		return true;
	}
	bool Frame()
	{
		_Angle += g_fPerSecFrame * 300.0f;
		Rotation(_ColorBitmap, m_ColorBitmap);
		Rotation(_MaskBitmap, m_MaskBitmap);

#pragma region dd
		if (S_Input.GetKey(VK_INSERT) == KEYSTATE::KEY_PUSH)
		{
			if (m_sRotation < 0)
			{
				m_sRotation = TB_ROTATION;
			}
			else
			{
				m_sRotation = -1;
			}
		}
		if (S_Input.GetKey('W') == KEYSTATE::KEY_PUSH ||
			S_Input.GetKey('W') == KEYSTATE::KEY_HOLD)
		{
			m_CenterPos.y += (-1 * g_fPerSecFrame * 1000.f);
		}
		if (S_Input.GetKey('S') == KEYSTATE::KEY_PUSH ||
			S_Input.GetKey('S') == KEYSTATE::KEY_HOLD)
		{
			m_CenterPos.y += (1 * g_fPerSecFrame * 1000.f);
		}
		if (S_Input.GetKey('A') == KEYSTATE::KEY_PUSH ||
			S_Input.GetKey('A') == KEYSTATE::KEY_HOLD)
		{
			m_CenterPos.x += (-1 * g_fPerSecFrame * 1000.f);
		}
		if (S_Input.GetKey('D') == KEYSTATE::KEY_PUSH ||
			S_Input.GetKey('D') == KEYSTATE::KEY_HOLD)
		{
			m_CenterPos.x += (1 * g_fPerSecFrame * 1000.f);
		}

		m_DrawPos.x = m_CenterPos.x - (m_rtDraw.right / 2);
		m_DrawPos.y = m_CenterPos.y - (m_rtDraw.bottom / 2);

		m_rtCollision.left = m_DrawPos.x;
		m_rtCollision.top = m_DrawPos.y;
		m_rtCollision.right = m_DrawPos.x + m_rtDraw.right;
		m_rtCollision.bottom = m_DrawPos.y + m_rtDraw.bottom;
#pragma endregion hh
		return true;
	}
	bool Render()
	{
		HBITMAP oldColor = (HBITMAP)SelectObject(_ColorDC, _ColorBitmap);
		HBITMAP oldMask = (HBITMAP)SelectObject(_MaskDC, _MaskBitmap);
		BitBlt(g_hOffScreenDC, m_CenterPos.x - (_MaxLength / 2), m_CenterPos.y - (_MaxLength / 2),
			_MaxLength, _MaxLength,
			_MaskDC,
			0, 0, SRCAND);
		BitBlt(g_hOffScreenDC, m_CenterPos.x - (_MaxLength / 2), m_CenterPos.y - (_MaxLength / 2),
			_MaxLength, _MaxLength,
			_ColorDC,
			0, 0, SRCINVERT);
		BitBlt(g_hOffScreenDC, m_CenterPos.x - (_MaxLength / 2), m_CenterPos.y - (_MaxLength / 2),
			_MaxLength, _MaxLength,
			_MaskDC,
			0, 0, SRCINVERT);

		SelectObject(_ColorDC, oldColor);
		SelectObject(_MaskDC, oldMask);

		return true;
	}
	bool Release()
	{
		return true;
	}
	void Rotation(HBITMAP hbit, Bitmap* bitm)
	{
		float Radian = _Angle * 3.141592f / 180.0f;
		float Cosine = cos(Radian);
		float Sine = sin(Radian);

		HBRUSH bkBrush = CreateSolidBrush(RGB(255, 255, 255));

		HBITMAP oldbitmap = (HBITMAP)SelectObject(_RotationDC, hbit);
		HBRUSH oldbrush = (HBRUSH)SelectObject(_RotationDC, bkBrush);

		PatBlt(_RotationDC, 0, 0, _MaxLength, _MaxLength, PATCOPY);
		DeleteObject(SelectObject(_RotationDC, bkBrush));


		int oldgraphic = SetGraphicsMode(_RotationDC, GM_ADVANCED);

		XFORM xform;
		xform.eM11 = Cosine;
		xform.eM12 = -Sine;
		xform.eM21 = Sine;
		xform.eM22 = Cosine;
		xform.eDx = _MaxLength / 2;
		xform.eDy = _MaxLength / 2;

		SetWorldTransform(_RotationDC, &xform);

		HDC hbitm = bitm->getMemDC();
		BitBlt(_RotationDC, -(m_rtDraw.right / 2), -(m_rtDraw.bottom / 2),
			m_rtDraw.right, m_rtDraw.bottom, hbitm,
			m_rtDraw.left, m_rtDraw.top, SRCCOPY);

		xform.eM11 = 1;
		xform.eM12 = 0;
		xform.eM21 = 0;
		xform.eM22 = 1;
		xform.eDx = 0;
		xform.eDy = 0;

		SetWorldTransform(_RotationDC, &xform);

		SetGraphicsMode(_RotationDC, GM_ADVANCED);
		SelectObject(_RotationDC, oldbrush);
		SelectObject(_RotationDC, oldbitmap);
	}
private:
	float			_MaxLength;
	HDC				_RotationDC;
	HDC				_ColorDC;
	HDC				_MaskDC;
	HBITMAP			_ColorBitmap;
	HBITMAP			_MaskBitmap;
	float			_Angle;
};

class Pl : public Core
{
public:
	bool Init()
	{
		e.Init();
		return true;
	}
	bool Frame()
	{
		e.Frame();
		return true;
	}
	bool Render()
	{
		e.Render();
		return true;
	}
	bool Release()
	{
		e.Release();
		return true;
	}
private:
	Rotate e;
};

int WINAPI wWinMain(HINSTANCE hinst, HINSTANCE previnst, LPWSTR szCmdLine, int nCmdShow)
{
	Pl wd;
	wd.SetWindow(hinst, 800, 600);
	wd.Run();

	return 0;
}