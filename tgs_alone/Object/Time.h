#pragma once

class Time
{
private:
	float time;       // ��������
	int time_cnt;     // 1�b���炷�^�C�~���O���J�E���g

public:
	Time();
	~Time();

	void Initialize();  // ����������
	void Update();      // �X�V����
	void Draw();        // �`�揈��
	void Finalize();    // �I��������
};