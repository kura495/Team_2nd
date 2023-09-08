#include"Input.h"

#define XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  7849
#define XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE 8689
#define XINPUT_GAMEPAD_TRIGGER_THRESHOLD    30

Input* Input::GetInstance()
{
	static Input instance;
	return &instance;
}

void Input::Initialize(WinApp*winApp_){
	//DirectInputのオブジェクトを作成
	hr = DirectInput8Create(winApp_->GetHINSTANCE(),DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)&directInput,nullptr);
	assert(SUCCEEDED(hr));
	//キーボードデバイスを生成
	hr = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	assert(SUCCEEDED(hr));
	//入力データ形式のセット
	hr = keyboard->SetDataFormat(&c_dfDIKeyboard);
	assert(SUCCEEDED(hr));
	//排他制御レベルのセット
	hr = keyboard->SetCooperativeLevel(winApp_->GetHWND(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	key = {};
	preKey = {};

	//コントローラー

}

void Input::Update()
{
	preKey = key;
	//キーボード情報の取得開始
	keyboard->Acquire();
	key = {};
	//全キーの入力状態を取得する
	keyboard->GetDeviceState(sizeof(key), key.data());
}

bool Input::pushKey(uint8_t keyNumber)
{
	if (key[keyNumber]!=0&&preKey[keyNumber]==0) {
		return true;
	}
	return false;
}
bool Input::IspushKey(uint8_t keyNumber)
{
	if (key[keyNumber] != 0) {
			return true;
	}
return false;
}

bool Input::TreggerKey(uint8_t keyNumber)
{
	if (preKey[keyNumber] == 0) {
		return true;
	}
	return false;
}

bool Input::IsTreggerKey(uint8_t keyNumber)
{
	if (key[keyNumber] == 0 && preKey[keyNumber] != 0) {
		return true;
	}
	return false;
}

bool Input::GetJoystickState(int32_t stickNo, XINPUT_STATE& out)
{
	DWORD dwResult = XInputGetState(stickNo, &out);
	if (out.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) {
		if (-XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE < out.Gamepad.sThumbLX) {
			out.Gamepad.sThumbLX = 0;
		}
		
	}
	if (out.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) {
		if (-XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE < out.Gamepad.sThumbLY) {
			out.Gamepad.sThumbLY = 0;
		}
	}
	if (out.Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) {
		if (-XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE < out.Gamepad.sThumbRX) {
			out.Gamepad.sThumbRX = 0;
		}
		
	}
	if (out.Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) {
		if (-XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE < out.Gamepad.sThumbRY) {
			out.Gamepad.sThumbRY = 0;
		}
	}
	return dwResult == ERROR_SUCCESS;

}

bool Input::PushLTrigger(XINPUT_STATE& out)
{
	if (out.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) {
		return true;
	}
	return false;
}

bool Input::PushRTrigger(XINPUT_STATE& out)
{
	if (out.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) {
		return true;
	}
	return false;
}

bool Input::PushLSHOULDER(XINPUT_STATE& out)
{
	if (out.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) {
		return true;
	}
	return false;
}

bool Input::PushRSHOULDER(XINPUT_STATE& out)
{
	if (out.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
		return true;
	}
	return false;
}

bool Input::PushAButton(XINPUT_STATE& out)
{
	if (out.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
		return true;
	}
	return false;
}

bool Input::PushBButton(XINPUT_STATE& out)
{
	if (out.Gamepad.wButtons & XINPUT_GAMEPAD_B) {
		return true;
	}
	return false;
}

bool Input::PushXButton(XINPUT_STATE& out)
{
	if (out.Gamepad.wButtons & XINPUT_GAMEPAD_X) {
		return true;
	}
	return false;
}

bool Input::PushYButton(XINPUT_STATE& out)
{
	if (out.Gamepad.wButtons & XINPUT_GAMEPAD_Y) {
		return true;
	}
	return false;
}
