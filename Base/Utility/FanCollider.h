#pragma once
#include "Math_Structs.h"
#include <cstdint>
#include "Collider.h"

class FanCollider
{
public:
	FanCollider();
	~FanCollider();

	//半径を取得
	float GetRadius() const { return radius_; }
	//半径を設定
	void SetRadius(float& Radius) { radius_ = Radius; }
	//角度を設定
	void SetAngle(float& Angle) { angle_ = Angle; }
	//衝突時に呼ばれる関数
	virtual void OnCollision(const uint32_t& Attribute) = 0;
	virtual void CheckCollision(const Collider& collider);
	virtual Vector3 GetWorldPosition() = 0;
	uint32_t GetcollitionAttribute() const { return collisionAttribute_; }
	/// <summary>
	/// 衝突属性
	/// </summary>
	/// <param name="collisionAttribute"></param>
	void SetcollisionAttribute(uint32_t collisionAttribute) {
		collisionAttribute_ = collisionAttribute;
	}
	uint32_t GetcollisionMask() const { return collisionMask_; }
	/// <summary>
	/// 衝突マスク
	/// </summary>
	/// <param name="collisionMask">基本はSetcollitionAttributeに入れたものに~を付けてビット反転</param>
	void SetcollisionMask(uint32_t collisionMask) {

		collisionMask_ = collisionMask;
	}

private:
	float angle_ = 0.0f;
	float radius_ = 1.0f;
	/// <summary>
	/// 衝突属性(自分)
	/// </summary>
	uint32_t collisionAttribute_ = 0xffffffff;
	/// <summary>
	/// 衝突マスク(相手)
	/// </summary>
	uint32_t collisionMask_ = 0xffffffff;
};

FanCollider::FanCollider()
{
}

FanCollider::~FanCollider()
{
}