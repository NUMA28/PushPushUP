#include "DxLib.h"

const char TITLE[] = "Push Push UP";

const int WIN_WIDTH = 768; //�E�B���h�E����
const int WIN_HEIGHT = 448;//�E�B���h�E�c��


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	ChangeWindowMode(TRUE);	//�E�B���h�E���[�h�ɐݒ�
	//�E�B���h�E�T�C�Y���蓮�ł͕ύX�ł����A���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetMainWindowText(TITLE);// �^�C�g����ύX
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);//��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�i���j�^�[�̉𑜓x�ɍ��킹��j
	SetWindowSizeExtendRate(1.0);//��ʃT�C�Y��ݒ�i�𑜓x�Ƃ̔䗦�Őݒ�j
	SetBackgroundColor(0, 0, 0);// ��ʂ̔w�i�F��ݒ肷��

	//Dx���C�u�����̏�����
	if (DxLib_Init() == -1) { return -1; }

	//�i�_�u���o�b�t�@�j�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	//�摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���
	int playerX = 168;
	int playerY = 416;
	int gage = 0;

	int X = 0;//�ړ����鋗��

	int PushSpace = 0;

	//��ʐ؂�ւ��p�t���O
	int LScreenFlag = 0;
	int RScreenFlag = 1;

	int Title = LoadGraph("Image\\Title.png");

	int BackSky = LoadGraph("Image\\BackSky.png");

	int Wall = LoadGraph("Image\\Wall.png");

	int HUDTimer = LoadGraph("Image\\TimeHUD.png");

	int Tsuta = LoadGraph("Image\\Tsuta.png");

	int timeHUD = LoadGraph("Image\\TimeHUD.png");

	int block = LoadGraph("Image\\block.png");

	int Gameover = LoadGraph("Image\\Gameover.png");

	int Timeover = LoadGraph("Image\\Timeover.png");

	int HowToJapanese = LoadGraph("Image\\HowTo Japanese.ver.png");

	int HowToHindi = LoadGraph("Image\\HowTo Hindi.ver.png");

	int KeypadTime = 0;

	int scene = 0;

	int Gage[31];
	LoadDivGraph("Image\\Gage.png", 31, 31, 1, 148, 208, Gage);

	int Distance[17];
	LoadDivGraph("Image\\distance.png", 17, 17, 1, 96, 248, Distance);

	int Keypad[2];
	LoadDivGraph("Image\\Space Key HUD.png", 2, 2, 1, 60, 22, Keypad);

	char strNum[10];

	int TimeGraph[10];
	LoadDivGraph("Image\\TimeNumber.png", 10, 10, 1, 28, 42, TimeGraph);

	//��������
	int Time = 100;
	int Time2 = 0;

	int BscrollY = -8512;

	int blockX[10]{ 250,50,250,50,250,50,250,50,250,50 };//�u���b�N�̍��W
	int blockY[10]{ 0,0,0,0,0,0,0,0,0,0 };

	int R_flag[10]{ 0,0,0,0,0,0,0,0,0,0 };//�ړ��̃t���O
	int L_flag[10]{ 1,1,1,1,1,1,1,1,1,1 };

	int LIFE = 1;//�v���C���[�̃��C�t

	int BGMFlag1 = 1;

	//�ȁASE
	int Opening = LoadSoundMem("Sound\\Opening.mp3");
	ChangeVolumeSoundMem(255 * 35 / 100, Opening);

	int MainTheme = LoadSoundMem("Sound\\Main theme.wav");
	ChangeVolumeSoundMem(255 * 35 / 100, MainTheme);

	int MainThemeSpeed = LoadSoundMem("Sound\\Main theme Speed 2.wav");
	ChangeVolumeSoundMem(255 * 35 / 100, MainThemeSpeed);

	int GameOver = LoadSoundMem("Sound\\Game Over.mp3");
	ChangeVolumeSoundMem(255 * 35 / 100, GameOver);

	int MaxGage = LoadSoundMem("Sound\\Gage Max.mp3");
	ChangeVolumeSoundMem(255 * 35 / 100, MaxGage);

	int HighGage = LoadSoundMem("Sound\\Gage high.mp3");
	ChangeVolumeSoundMem(255 * 35 / 100, HighGage);

	int MiddleGage = LoadSoundMem("Sound\\Gage Middle.mp3");
	ChangeVolumeSoundMem(255 * 35 / 100, MiddleGage);

	int LowGage = LoadSoundMem("Sound\\Gage Low.mp3");
	ChangeVolumeSoundMem(255 * 35 / 100, LowGage);

	//�Q�[�����[�v�Ŏg���ϐ��̐錾
	char keys[256] = { 0 }; //�ŐV�̃L�[�{�[�h���p
	char oldkeys[256] = { 0 };//1���[�v�i�t���[���j�O�̃L�[�{�[�h���

	// �Q�[�����[�v
	while (1)
	{
		//�ŐV�̃L�[�{�[�h��񂾂������̂͂P�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�

		//�ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		//��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		//�X�V����

		//����1�i�X�y�[�X�L�[�ŃQ�[�W�����߂�j
		switch (scene)
		{
		case 0:

			StopSoundMem(GameOver);

			if (CheckSoundMem(Opening) == 0)
			{
				PlaySoundMem(Opening, DX_PLAYTYPE_BACK);
			}

			if (keys[KEY_INPUT_1] == 1)
			{
				scene = 6;
			}

			if (keys[KEY_INPUT_2] == 1)
			{
				scene = 7;
			}

			if (keys[KEY_INPUT_Z] == 1)
			{
				LIFE = 1;

				playerX = 168;
				playerY = 416;
				gage = 0;

				X = 0;//�ړ����鋗��

				PushSpace = 0;

				//��ʐ؂�ւ��p�t���O
				LScreenFlag = 0;
				RScreenFlag = 1;

				//��������
				Time = 100;
				Time2 = 0;

				BscrollY = -8512;

				for (int i = 0; i < 10; i += 2)
				{
					blockX[i] = 250;
				}

				for (int i = 1; i < 10; i += 2)
				{
					blockX[i] = 0;
				}

				scene = 1;
			}

			/*DrawFormatString(0, 200, GetColor(255, 255, 255), "Z�L�[�ŊJ�n", TRUE);
			DrawFormatString(0, 220, GetColor(255, 255, 255), "1�L�[�ŗV�ѕ�", TRUE);
			DrawFormatString(0, 240, GetColor(255, 255, 255), "2�L�[�ŗV�ѕ�", TRUE);*/
			DrawGraph(0, 0, Title, TRUE);

			break;


		case 1:

			StopSoundMem(Opening);
			StopSoundMem(GameOver);

			if (Time > 30)
			{
				if (CheckSoundMem(MainTheme) == 0)
				{
					PlaySoundMem(MainTheme, DX_PLAYTYPE_BACK);
				}
			}

			if (Time <= 30)
			{
				StopSoundMem(MainTheme);

				if (CheckSoundMem(MainThemeSpeed) == 0)
				{
					PlaySoundMem(MainThemeSpeed, DX_PLAYTYPE_BACK);
				}
			}

			if (RScreenFlag == 1)
			{
				gage += 1;

				if (gage > 30)
				{
					gage = 0;
				}

				//�Q�[�W���狗�����Z�o
				if (gage >= 1 && gage <= 10)//�Q�[�W�l��1<=gage<=10�̎�
				{
					X = gage * 10;
				}

				if (gage >= 11 && gage <= 20)//�Q�[�W�l��11<=gage<=20�̎�
				{
					X = gage * 20;
				}

				if (gage >= 21 && gage <= 30)//�Q�[�W�l��21<=gage<=30�̎�
				{
					X = gage * 30;
				}
			}

			if (keys[KEY_INPUT_SPACE] == 1 && RScreenFlag == 1)
			{
				StopSoundMem(HighGage);
				StopSoundMem(MiddleGage);
				StopSoundMem(LowGage);
				PushSpace = 1;

				if (gage >= 1 && gage <= 10)//�Q�[�W�l��1<=gage<=10�̎�
				{
					if (CheckSoundMem(LowGage) == 0)
					{
						PlaySoundMem(LowGage, DX_PLAYTYPE_BACK);
					}
				}

				if (gage >= 11 && gage <= 20)//�Q�[�W�l��11<=gage<=20�̎�
				{
					if (CheckSoundMem(MiddleGage) == 0)
					{
						PlaySoundMem(MiddleGage, DX_PLAYTYPE_BACK);
					}
				}

				if (gage >= 21 && gage <= 30)//�Q�[�W�l��21<=gage<=30�̎�
				{
					if (CheckSoundMem(HighGage) == 0)
					{
						PlaySoundMem(HighGage, DX_PLAYTYPE_BACK);
					}
				}

				if (gage == 0)//�Q�[�W�l��0�̎��i�B���p���[�Q�[�W�j
				{
					if (CheckSoundMem(MaxGage) == 0)
					{
						PlaySoundMem(MaxGage, DX_PLAYTYPE_BACK);
					}
				}

				RScreenFlag = 0;
				LScreenFlag = 1;
			}

			else
				if (keys[KEY_INPUT_SPACE] == 0)
				{
					PushSpace = 0;
				}

			//����2�i�ӂ��ړ�����j
			if (LScreenFlag == 1)
			{
				//�Q�[�W��5�������Ă���
				X -= 5;

				//�Q�[�W��0�ȏ�̎��ɂ����������s��Ȃ�
				if (X > 0)
				{
					//��������
					//�v���C���[Y���W���������Ƃ�
					if (0 < X && X < 28)
					{
						playerY -= 1;
					}

					if (28 <= X && X < 56)
					{
						playerY -= 2;
					}

					if (56 <= X && X < 112)
					{
						playerY -= 4;
					}

					if (112 <= X && X < 225)
					{
						playerY -= 6;
					}

					if (225 <= X && X < 450)
					{
						playerY -= 8;
					}

					if (450 <= X)
					{
						playerY -= 10;
					}

					//�v���C���[Y���W���~�߂Ĕw�iY���W�𓮂����Ƃ�
					if (playerY < 224 && BscrollY < 0)
					{
						playerY = 224;

						if (0 <= X && X < 28)
						{
							BscrollY += 1;
						}

						if (28 <= X && X < 56)
						{
							BscrollY += 2;
						}

						if (56 <= X && X < 112)
						{
							BscrollY += 3;
						}

						if (112 <= X && X < 225)
						{
							BscrollY += 4;
						}

						if (225 <= X && X < 450)
						{
							BscrollY += 5;
						}

						if (450 <= X)
						{
							BscrollY += 10;
						}
					}

					//�w�i��Y���W = 0�Ŏ~�߂�
					if (BscrollY >= 0)
					{
						BscrollY = 0;
					}

					//�v���C���[��Y���W = 160�Ŏ~�߂āA�N���A��ʁi�V�[��2�j��
					if (playerY <= 192)
					{
						playerY = 192;
						scene = 2;
					}
				}

				//�S�[���ɂ��ǂ蒅���܂ł͉E�������ɌJ��Ԃ�
				if (X == 0 && playerY > 160)
				{
					gage = 0;
					RScreenFlag = 1;
					LScreenFlag = 0;
				}
			}

			//�E���֌W�Ȃ��i��ɓ����Ă���j�����̏���
			//�^�C�}�[����
			Time2 += 1;

			if (Time2 == 52)
			{
				Time2 = 0;
				Time -= 1;

				if (Time < 0)
				{
					Time = 0;
				}
			}

			if (Time == 0 && Time2 == 51)
			{
				scene = 4;
			}

			for (int i = 0; i < 10; i++)//�����蔻��
			{
				if (playerX < blockX[i] + 96 && playerY < blockY[i] + 48 && blockX[i] < playerX + 48 && blockY[i] < playerY + 48)
				{
					LIFE = 0;
				}
			}

			for (int i = 0; i < 10; i++)//�����]��
			{

				if (blockX[i] <= 30)
				{
					L_flag[i] = 0;
					R_flag[i] = 1;
				}

				if (blockX[i] >= 260)//�u���b�N�̕������炷����
				{
					L_flag[i] = 1;
					R_flag[i] = 0;
				}

			}

			for (int i = 0; i < 10; i++)
			{
				if (L_flag[i] == 1)//���ɐi��
				{
					blockX[i] -= 1;
				}
				if (R_flag[i] == 1)//�E�ɐi��
				{
					blockX[i] += 1;
				}
			}

			blockY[0] = BscrollY + 7000;
			blockY[1] = BscrollY + 6000;
			blockY[2] = BscrollY + 5000;
			blockY[3] = BscrollY + 4000;
			blockY[4] = BscrollY + 3500;
			blockY[5] = BscrollY + 3000;
			blockY[6] = BscrollY + 2500;
			blockY[7] = BscrollY + 2000;
			blockY[8] = BscrollY + 1500;
			blockY[9] = BscrollY + 1000;

			//�`�揈��
			//�w�i
			DrawGraph(0, BscrollY, BackSky, TRUE);

			//�v���C���[
			DrawGraph(playerX, playerY, Tsuta, TRUE);

			//��Q��
			DrawGraph(blockX[0], blockY[0], block, TRUE);
			DrawGraph(blockX[1], blockY[1], block, TRUE);
			DrawGraph(blockX[2], blockY[2], block, TRUE);
			DrawGraph(blockX[3], blockY[3], block, TRUE);
			DrawGraph(blockX[4], blockY[4], block, TRUE);
			DrawGraph(blockX[5], blockY[5], block, TRUE);
			DrawGraph(blockX[6], blockY[6], block, TRUE);
			DrawGraph(blockX[7], blockY[7], block, TRUE);
			DrawGraph(blockX[8], blockY[8], block, TRUE);
			DrawGraph(blockX[9], blockY[9], block, TRUE);

			if (LIFE == 0)
			{
				scene = 3;
			}

			//��
			DrawGraph(0, BscrollY, Wall, TRUE);

			//�E����HUD�̍�������
			DrawBox(WIN_WIDTH / 2, 0, WIN_WIDTH, WIN_HEIGHT, GetColor(0, 0, 0), TRUE);

			//���vHUD�̕`��
			DrawGraph(490, 16, timeHUD, TRUE);

			//�����w�蕶����ɏ]���āA�z��Ɋi�[
			sprintf_s(strNum, sizeof(strNum), "%d", Time);

			//�^�C�}�[�̐����\��
			for (int i = 0; i < 10; i++)
			{
				int num = strNum[i] - '0'; //�I�t�Z�b�g����

				//X���W�͈�ԍ��̐��������������ʒu +i���� *�摜�ꌅ����x��
				if (Time == 100)
				{
					DrawGraph(534 + i * 28, 76, TimeGraph[num], TRUE);
				}

				if (9 < Time && Time < 100)
				{
					DrawGraph(548 + i * 28, 76, TimeGraph[num], TRUE);
				}

				if (0 <= Time && Time < 10)
				{
					DrawGraph(562 + i * 28, 76, TimeGraph[num], TRUE);
				}
			}

			//�Q�[�WHUD�̕\��
			for (int i = 0; i < 31; ++i)
			{
				DrawGraph(424, 206, Gage[gage], TRUE);
			}

			//�����Q�[�WHUD�̕\��
			for (int i = 0; i < 17; ++i)
			{
				if (-8928 <= BscrollY && BscrollY < -8382)
				{
					DrawGraph(612, 158, Distance[0], TRUE);
				}

				if (-8382 <= BscrollY && BscrollY < -7836)
				{
					DrawGraph(612, 158, Distance[1], TRUE);
				}

				if (-7836 <= BscrollY && BscrollY < -7290)
				{
					DrawGraph(612, 158, Distance[2], TRUE);
				}

				if (-7290 <= BscrollY && BscrollY < -6744)
				{
					DrawGraph(612, 158, Distance[3], TRUE);
				}

				if (-6744 <= BscrollY && BscrollY < -6198)
				{
					DrawGraph(612, 158, Distance[4], TRUE);
				}

				if (-6198 <= BscrollY && BscrollY < -5652)
				{
					DrawGraph(612, 158, Distance[5], TRUE);
				}

				if (-5652 <= BscrollY && BscrollY < -5106)
				{
					DrawGraph(612, 158, Distance[6], TRUE);
				}

				if (-5106 <= BscrollY && BscrollY < -4560)
				{
					DrawGraph(612, 158, Distance[7], TRUE);
				}

				if (-4560 <= BscrollY && BscrollY < -4014)
				{
					DrawGraph(612, 158, Distance[8], TRUE);
				}

				if (-4014 <= BscrollY && BscrollY < -3468)
				{
					DrawGraph(612, 158, Distance[9], TRUE);
				}

				if (-3468 <= BscrollY && BscrollY < -2922)
				{
					DrawGraph(612, 158, Distance[10], TRUE);
				}

				if (-2922 <= BscrollY && BscrollY < -2376)
				{
					DrawGraph(612, 158, Distance[11], TRUE);
				}

				if (-2376 <= BscrollY && BscrollY < -1830)
				{
					DrawGraph(612, 158, Distance[12], TRUE);
				}

				if (-1830 <= BscrollY && BscrollY < -1284)
				{
					DrawGraph(612, 158, Distance[13], TRUE);
				}

				if (-1284 <= BscrollY && BscrollY < -738)
				{
					DrawGraph(612, 158, Distance[14], TRUE);
				}

				if (-738 <= BscrollY && BscrollY < -192)
				{
					DrawGraph(612, 158, Distance[15], TRUE);
				}

				if (-192 <= BscrollY)
				{
					DrawGraph(612, 158, Distance[16], TRUE);
				}
			}

			//�`���[�g���A���p�L�[�p�b�hHUD�\��
			if (RScreenFlag == 1)
			{
				KeypadTime += 1;

				if (KeypadTime == 20)
				{
					KeypadTime = 0;
				}
			}

			for (int i = 0; i < 2; ++i)
			{
				if (0 < KeypadTime && KeypadTime < 10)
				{
					DrawGraph(443, 414, Keypad[0], TRUE);
				}

				else
				{
					DrawGraph(443, 414, Keypad[1], TRUE);
				}
			}

			////�f�o�b�O�R�[�h
			//DrawFormatString(400, 200, GetColor(255, 255, 255), "�v���C���[X���W(playerX) = %d", playerX);
			//DrawFormatString(400, 220, GetColor(255, 255, 255), "�v���C���[Y���W(playerY) = %d", playerY);
			//DrawFormatString(400, 260, GetColor(255, 255, 255), "�p���[�Q�[�W(gage) = %d", gage);
			//DrawFormatString(200, 100, GetColor(255, 255, 255), "���݂̔w�i��Y���W(BscrollY) = %d", BscrollY);
			//DrawFormatString(400, 300, GetColor(255, 255, 255), "�E��������(RScreenFlag) = %d", RScreenFlag);
			//DrawFormatString(400, 320, GetColor(255, 255, 255), "����������(LScreenFlag) = %d", LScreenFlag);
			//DrawFormatString(400, 340, GetColor(255, 255, 255), "�X�y�[�X�L�[�������Ă��邩(PushSpace) = %d", PushSpace);
			//DrawFormatString(400, 360, GetColor(255, 255, 255), "�i�ދ��� = %d(X)", X);

			break;

		case 2://�N���A�\���

			StopSoundMem(MainTheme);
			StopSoundMem(MainThemeSpeed);
			StopSoundMem(MaxGage);
			StopSoundMem(HighGage);
			StopSoundMem(MiddleGage);
			StopSoundMem(LowGage);

			PlayMovie("Movies\\Ending.mp4", 1, DX_MOVIEPLAYTYPE_NORMAL);
			scene = 5;

			break;

		case 3://�Q�[���I�[�o�[���

			StopSoundMem(MainTheme);
			StopSoundMem(MainThemeSpeed);
			StopSoundMem(MaxGage);
			StopSoundMem(HighGage);
			StopSoundMem(MiddleGage);
			StopSoundMem(LowGage);

			if (CheckSoundMem(GameOver) == 0)
			{
				PlaySoundMem(GameOver, DX_PLAYTYPE_LOOP);
			}

			if (keys[KEY_INPUT_T] == 1)
			{
				scene = 0;
			}

			if (keys[KEY_INPUT_R] == 1)
			{
				playerX = 168;
				playerY = 416;
				gage = 0;

				LIFE = 1;

				X = 0;//�ړ����鋗��

				PushSpace = 0;

				//��ʐ؂�ւ��p�t���O
				LScreenFlag = 0;
				RScreenFlag = 1;

				//��������
				Time = 100;
				Time2 = 0;

				BscrollY = -8512;

				scene = 1;
			}

			//�w�i
			DrawGraph(0, BscrollY, BackSky, TRUE);

			//�v���C���[
			DrawGraph(playerX, playerY, Tsuta, TRUE);

			//��Q��
			DrawGraph(blockX[0], blockY[0], block, TRUE);
			DrawGraph(blockX[1], blockY[1], block, TRUE);
			DrawGraph(blockX[2], blockY[2], block, TRUE);
			DrawGraph(blockX[3], blockY[3], block, TRUE);
			DrawGraph(blockX[4], blockY[4], block, TRUE);
			DrawGraph(blockX[5], blockY[5], block, TRUE);
			DrawGraph(blockX[6], blockY[6], block, TRUE);
			DrawGraph(blockX[7], blockY[7], block, TRUE);
			DrawGraph(blockX[8], blockY[8], block, TRUE);
			DrawGraph(blockX[9], blockY[9], block, TRUE);

			//��
			DrawGraph(0, BscrollY, Wall, TRUE);

			//�E����HUD�̍�������
			DrawGraph(0, 0, Gameover, TRUE);

			break;

		case 4://�^�C���A�b�v���

			StopSoundMem(MainThemeSpeed);
			StopSoundMem(MaxGage);
			StopSoundMem(HighGage);
			StopSoundMem(MiddleGage);
			StopSoundMem(LowGage);

			if (CheckSoundMem(GameOver) == 0)
			{
				PlaySoundMem(GameOver, DX_PLAYTYPE_LOOP);
			}

			if (keys[KEY_INPUT_T] == 1)
			{
				scene = 0;
			}

			if (keys[KEY_INPUT_R] == 1)
			{
				playerX = 168;
				playerY = 416;
				gage = 0;

				LIFE = 1;

				X = 0;//�ړ����鋗��

				PushSpace = 0;

				//��ʐ؂�ւ��p�t���O
				LScreenFlag = 0;
				RScreenFlag = 1;

				//��������
				Time = 100;
				Time2 = 0;

				BscrollY = -8512;

				scene = 1;

				break;

		case 5://�N���A�\���

			PlayMovie("Movies\\Credit.mp4", 1, DX_MOVIEPLAYTYPE_BCANCEL);
			scene = 0;

			break;

		case 6://�V�ѕ��i���{��j

			if (CheckSoundMem(Opening) == 0)
			{
				PlaySoundMem(Opening, DX_PLAYTYPE_BACK);
			}

			if (keys[KEY_INPUT_T] == 1)
			{
				scene = 0;
			}

			DrawGraph(0, 0, HowToJapanese, TRUE);

			break;

		case 7://�V�ѕ��i�q���f�B�[��j

			if (CheckSoundMem(Opening) == 0)
			{
				PlaySoundMem(Opening, DX_PLAYTYPE_BACK);
			}

			if (keys[KEY_INPUT_T] == 1)
			{
				scene = 0;
			}
			DrawGraph(0, 0, HowToHindi, TRUE);

			break;

			}

			//�w�i
			DrawGraph(0, BscrollY, BackSky, TRUE);

			//�v���C���[
			DrawGraph(playerX, playerY, Tsuta, TRUE);

			//��Q��
			DrawGraph(blockX[0], blockY[0], block, TRUE);
			DrawGraph(blockX[1], blockY[1], block, TRUE);
			DrawGraph(blockX[2], blockY[2], block, TRUE);
			DrawGraph(blockX[3], blockY[3], block, TRUE);
			DrawGraph(blockX[4], blockY[4], block, TRUE);
			DrawGraph(blockX[5], blockY[5], block, TRUE);
			DrawGraph(blockX[6], blockY[6], block, TRUE);
			DrawGraph(blockX[7], blockY[7], block, TRUE);
			DrawGraph(blockX[8], blockY[8], block, TRUE);
			DrawGraph(blockX[9], blockY[9], block, TRUE);

			//��
			DrawGraph(0, BscrollY, Wall, TRUE);

			//�E����HUD�̍�������
			DrawGraph(0, 0, Timeover, TRUE);

			break;
		}

		//---------  �����܂łɃv���O�������L�q  ---------//
		ScreenFlip();//�i�_�u���o�b�t�@�j����
		// 20�~���b�ҋ@�i�^��60FPS�j
		WaitTimer(20);
		// Windows �V�X�e�����炭�������������
		if (ProcessMessage() == -1)
		{
			break;
		}
		// �d�r�b�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	//Dx���C�u�����I������
	DxLib_End();

	return 0;
}