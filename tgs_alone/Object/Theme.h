#pragma once

#define THEME_MAX 15

class Theme
{
private:
	int theme_img[4]; // ����摜
	int theme[THEME_MAX];  // ���� 
	bool theme_flg;   // ������o�����o���Ȃ����t���O
	int theme_num;    // ����̐�

public:
	Theme();
	~Theme();

	void Initialize();  // ����������
	void Update();      // �X�V����
	void Draw();        // �`�揈��
	void Finalize();    // �I��������
};