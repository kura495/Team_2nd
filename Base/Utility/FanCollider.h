#pragma once
#include "Math_Structs.h"
#include <cstdint>
#include "Collider.h"

class FanCollider
{
public:
	FanCollider();
	~FanCollider();

	//���a���擾
	float GetRadius() const { return radius_; }
	//���a��ݒ�
	void SetRadius(float& Radius) { radius_ = Radius; }
	//�p�x��ݒ�
	void SetAngle(float& Angle) { angle_ = Angle; }
	//�Փˎ��ɌĂ΂��֐�
	virtual void OnCollision(const uint32_t& Attribute) = 0;
	virtual void CheckCollision(const Collider& collider);
	virtual Vector3 GetWorldPosition() = 0;
	uint32_t GetcollitionAttribute() const { return collisionAttribute_; }
	/// <summary>
	/// �Փˑ���
	/// </summary>
	/// <param name="collisionAttribute"></param>
	void SetcollisionAttribute(uint32_t collisionAttribute) {
		collisionAttribute_ = collisionAttribute;
	}
	uint32_t GetcollisionMask() const { return collisionMask_; }
	/// <summary>
	/// �Փ˃}�X�N
	/// </summary>
	/// <param name="collisionMask">��{��SetcollitionAttribute�ɓ��ꂽ���̂�~��t���ăr�b�g���]</param>
	void SetcollisionMask(uint32_t collisionMask) {

		collisionMask_ = collisionMask;
	}

private:
	float angle_ = 0.0f;
	float radius_ = 1.0f;
	/// <summary>
	/// �Փˑ���(����)
	/// </summary>
	uint32_t collisionAttribute_ = 0xffffffff;
	/// <summary>
	/// �Փ˃}�X�N(����)
	/// </summary>
	uint32_t collisionMask_ = 0xffffffff;
};

FanCollider::FanCollider()
{
}

FanCollider::~FanCollider()
{
}