#pragma once

class Player
{
private:
	int sound;         // ���f�[�^

public:
	Player();
	~Player();

	void Initialize();  // ����������
	void Update();      // �X�V����
	void Draw();        // �`�揈��
	void Finalize();    // �I��������
};