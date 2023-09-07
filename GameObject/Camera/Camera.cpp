#include"Camera.h"

void Camera::Initialize(int32_t kClientWidth, int32_t kClientHeight)
{
	kClientWidth_= kClientWidth;
	kClientHeight_= kClientHeight;
	matRot_ = MakeIdentity4x4();
	worldMatrix = MakeAffineMatrix({1,1,1},{0,0,0}, {0,0,0});
	/*Matrix4x4 cameraMatrix = MakeAffineMatrix({1,1,1},{0,0,0}, translation_);*/
	Matrix4x4 cameraMatrix = MakeIdentity4x4();
	cameraMatrix = Multiply(cameraMatrix, matRot_);
	Matrix4x4 Move = MakeTranslateMatrix(translation_);
	cameraMatrix = Multiply(cameraMatrix, Move);
	ViewMatrix = Inverse(cameraMatrix);
	ViewMatrix = Multiply(ViewMatrix, matRot_);
	ProjectionMatrix = MakePerspectiveFovMatrix(FOV, float(kClientWidth_) / float(kClientHeight_), 0.1f, 100.0f);
	Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix,Multiply(ViewMatrix, ProjectionMatrix));
	transformationMatrixData = worldViewProjectionMatrix;
	input = Input::GetInstance();
	
}
void Camera::Update()
{
#ifdef _DEBUG
	if (DebucCameraFlag) {
		DebugCameraMove();
	}
#endif // _DEBUG
	worldMatrix = MakeAffineMatrix({ 1,1,1 }, { 0,0,0 }, { 0,0,0 });
	/*Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1,1,1 }, {0,0,0}, translation_);*/
	Matrix4x4 cameraMatrix = MakeIdentity4x4();
	cameraMatrix = Multiply(cameraMatrix,matRot_);
	//rotate後で消す！！
	Matrix4x4 rotate = MakeRotateMatrix(rotation_);
	cameraMatrix = Multiply(cameraMatrix, rotate);
	//rotate後で消す！！
	Matrix4x4 Move = MakeTranslateMatrix(translation_);
	cameraMatrix = Multiply(cameraMatrix, Move);
	ViewMatrix = Inverse(cameraMatrix);
	
	ProjectionMatrix = MakePerspectiveFovMatrix(/*0.45f*/FOV, float(kClientWidth_) / float(kClientHeight_), 0.1f, 100.0f);
	Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(ViewMatrix, ProjectionMatrix));
	transformationMatrixData = worldViewProjectionMatrix;
}
void Camera::ImGui(const char* Title)
{
	ImGui::Begin(Title);
	//回転
	ImGui::SliderFloat3("Rotate", &rotation_.x, 0, 5, "%.3f");
	//移動
	ImGui::SliderFloat3("Translate", &translation_.x, -25, 10, "%.3f");
	ImGui::SliderFloat(/*"FOV"*/"???", &FOV, 45.0f, 104.0f);
#ifdef _DEBUG
	ImGui::Text("DebugCameraOn : 1\n");
	ImGui::Text("DebugCameraOff : 2\n");
	ImGui::Text("Rotate : W A S D\n");
	ImGui::Text("Translate : ARROWKEY\n");
#endif // DEBUG
	ImGui::End();
}
Vector3 Camera::GetmatRot()
{
	Vector3 result;
	result.x = matRot_.m[0][0] * matRot_.m[0][1]* matRot_.m[0][2];
	result.y = matRot_.m[0][0] * matRot_.m[0][2] * matRot_.m[2][0] * matRot_.m[2][2];
	result.z = matRot_.m[0][0] * matRot_.m[0][1] * matRot_.m[1][0] * matRot_.m[1][1];

	return result;
}
#ifdef _DEBUG
void Camera::DebugCameraMove()
{
#pragma region rotation
		Matrix4x4 matRotDelta = MakeIdentity4x4();
		if (input->IspushKey(DIK_UP)) {
			const float speed = -0.05f;
			matRotDelta = Multiply(matRotDelta, MakeRotateXMatrix(speed));
		}
		else if (input->IspushKey(DIK_DOWN)) {
			const float speed = 0.05f;
			matRotDelta = Multiply(matRotDelta, MakeRotateXMatrix(speed));
		}
		if (input->IspushKey(DIK_LEFT)) {
			const float speed = -0.05f;
			matRotDelta = Multiply(matRotDelta, MakeRotateYMatrix(speed));
		}
		else if (input->IspushKey(DIK_RIGHT)) {
			const float speed = 0.05f;
			matRotDelta = Multiply(matRotDelta, MakeRotateYMatrix(speed));
		}
		matRot_ = Multiply(matRotDelta,matRot_);
#pragma endregion 回転
#pragma region translation_
		if (input->IspushKey(DIK_A)) {
			const float speed = -0.5f;
			Vector3 translate{ speed,0,0 };
			translation_ = Add(translation_, translate);
		}
		else if (input->IspushKey(DIK_D)) {
			const float speed = 0.5f;
			Vector3 translate{ speed,0,0 };
			translation_ = Add(translation_, translate);
		}
		if (input->IspushKey(DIK_W)) {
			const float speed = 0.5f;
			Vector3 translate{ 0,speed,0 };
			translation_ = Add(translation_, translate);
		}
		else if (input->IspushKey(DIK_S)) {
			const float speed = -0.5f;
			Vector3 translate{ 0,speed,0 };
			translation_ = Add(translation_, translate);
		}
		if (input->IspushKey(DIK_E)) {
			const float speed = 0.5f;
			Vector3 translate{ 0,0,speed };
			translation_ = Add(translation_, translate);
		}
		else if (input->IspushKey(DIK_Q)) {
			const float speed = -0.5f;
			Vector3 translate{ 0,0,speed };
			translation_ = Add(translation_, translate);
		}
#pragma endregion 移動
}
#endif // DEBUG