#pragma once
#include "Math_Structs.h"
#include <cstdint>

class Collider {
public:
	//半径を取得
	float GetRadius() const { return radius_; }
	//半径を設定
	void SetRadius(float& Radius) { radius_ = Radius; }
	//衝突時に呼ばれる関数
	virtual void OnCollision(const uint32_t&Attribute) = 0;
	virtual Vector3 GetWorldPosition()=0;
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
	void SetcollisionMask(uint32_t collisionMask){

		collisionMask_ = collisionMask;
	}

private:
	/// <summary>
	/// 半径
	/// 初期値は1.0f
	/// </summary>
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
