#pragma once
#define DIRECTINPUT_VERSION 0x0800//DirectInputのバージョン指定
#include <dinput.h>
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

#include <wrl.h>
#include "WinApp.h"
#include <array>

#include <XInput.h>

class Input
{
public:
	static Input* GetInstance();
	void Initialize(WinApp* winApp_);
	void Update();
	/// <summary>
	/// 押した瞬間
	/// </summary>
	/// <param name="keyNumber"></param>
	/// <returns></returns>
	bool pushKey(uint8_t keyNumber);
	/// <summary>
	/// 押している間
	/// </summary>
	/// <param name="keyNumber"></param>
	/// <returns></returns>
	bool IspushKey(uint8_t keyNumber);
	/// <summary>
	/// 離している間
	/// </summary>
	/// <param name="keyNumber"></param>
	/// <returns></returns>
	bool TreggerKey(uint8_t keyNumber);
	/// <summary>
	/// 離した瞬間
	/// </summary>
	/// <param name="keyNumber"></param>
	/// <returns></returns>
	bool IsTreggerKey(uint8_t keyNumber);
	/// <summary>
	/// ゲームパッドの状態を取得
	/// </summary>
	/// <param name="stickNo"></param>
	/// <param name="out"></param>
	/// <returns></returns>
	bool GetJoystickState(int32_t stickNo, XINPUT_STATE& out);
	/// <summary>
	/// LTriggerを押している間
	/// </summary>
	/// <param name="out"></param>
	/// <returns></returns>
	bool PushLTrigger(XINPUT_STATE& out);
	/// <summary>
	/// RTriggerを押している間
	/// </summary>
	/// <param name="out"></param>
	/// <returns></returns>
	bool PushRTrigger(XINPUT_STATE& out);
	/// <summary>
	/// LSHOLDER(LB)を押している間
	/// </summary>
	/// <param name="out"></param>
	/// <returns></returns>
	bool PushLSHOULDER(XINPUT_STATE& out);
	/// <summary>
	/// RSHOLDER(RB)を押している間
	/// </summary>
	/// <param name="out"></param>
	/// <returns></returns>
	bool PushRSHOULDER(XINPUT_STATE& out);
	/// <summary>
	/// AButtonを押している間
	/// </summary>
	/// <param name="out"></param>
	/// <returns></returns>
	bool PushAButton(XINPUT_STATE& out);
	/// <summary>
	/// BButtonを押している間
	/// </summary>
	/// <param name="out"></param>
	/// <returns></returns>
	bool PushBButton(XINPUT_STATE& out);
	/// <summary>
	/// XButtonを押している間
	/// </summary>
	/// <param name="out"></param>
	/// <returns></returns>
	bool PushXButton(XINPUT_STATE& out);
	/// <summary>
	/// YButtonを押している間
	/// </summary>
	/// <param name="out"></param>
	/// <returns></returns>
	bool PushYButton(XINPUT_STATE& out);

private:
	Input() = default;
	~Input() = default;
	Input(const Input& obj) = delete;
	Input& operator=(const Input& obj) = delete;

	HRESULT hr;
	Microsoft::WRL::ComPtr<IDirectInput8>directInput = nullptr;
	Microsoft::WRL::ComPtr<IDirectInputDevice8> keyboard = nullptr;
	std::array<BYTE, 256> key;
	std::array<BYTE, 256> preKey;
	
	//XINPUT_STATE joyState;
};

