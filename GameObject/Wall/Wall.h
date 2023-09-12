#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Utility/Collider.h"
#include "Utility/CollisionConfig.h"

class Wall : public Collider
{
public:
	void Initialize(Model* model);
	void Update();
	void Draw(const ViewProjection& viewProjection);

	Vector3 GetWorldPosition() override;

	void OnCollision(const uint32_t& Attribute) override;

	/// <summary>
	/// 位置の設定
	/// </summary>
	void SetPosition(const Vector3& position);

private:
	WorldTransform worldTransform_;


	Model* model_ = nullptr;
};

