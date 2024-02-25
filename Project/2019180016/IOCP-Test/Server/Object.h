#pragma once

// Ŭ���̾�Ʈ���� ��ȭ�� �ʿ��� ��ü���� ������ �ֻ��� Ŭ����
class Object
{
public:
	Object() :
		x(0.f), y(0.f), z(0.f),
		Pitch(0.f), Yaw(0.f), Roll(0.f)
	{}
	Object(float x, float y, float z, float rx, float ry, float rz);
	~Object() {}

public:
	void SetLocation(float x, float y, float z) { this->x = x; this->y = y; this->z = z; };
	void SetRotation(float x, float y, float z) { Pitch = x; Yaw = y; Roll = z; };

	void GetLocation(float &x, float &y, float &z) {
		x = this->x;
		y = this->y;
		z = this->z;
	}
	void GetRotation(float &x, float &y, float &z) {
		x = Pitch;
		y = Yaw;
		x = Roll;
	}

public:
	void MoveLocation(float x, float y, float z);

protected:
	float x;
	float y;
	float z;

	float Pitch;
	float Yaw;
	float Roll;
};

