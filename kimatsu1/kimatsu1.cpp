// kimatsu1.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include"Setting.h"

int main()
{
	// �J�����g�f�B���N�g���̎擾
	char s_currentDir[_MAX_PATH];
	GetCurrentDirectory(sizeof(s_currentDir), s_currentDir);
	// �t�@�C���p�X�̍쐬(ini�t�@�C������ǂݍ���)
	char s_inifile[_MAX_PATH];
	sprintf_s(s_inifile, "%s\\BOARD.ini", s_currentDir);

	//�\���̂�ini�t�@�C���̃f�[�^���i�[
	struct Boad WIDTH, HEIGHT;
	WIDTH.Othello_WIDTH = GetPrivateProfileInt("WIDTH", "Othello_WIDTH", -1, s_inifile);
	HEIGHT.Othello_HEIGHT = GetPrivateProfileInt("HEIGHT", "Othello_HEIGHT", -1, s_inifile);

	int BOARD_WIDTH = WIDTH.Othello_WIDTH;
	int BOARD_HEIGHT = HEIGHT.Othello_HEIGHT;
	

	// ������
	for (int y = 0; y < BOARD_HEIGHT; y++)
	{
		for (int x = 0; x < BOARD_WIDTH; x++)
		{
			cells[y][x] = COLOR_NONE;
		}
	}

	cells[3][3] = COLOR_WHITE;
	cells[4][4] = COLOR_WHITE;
	cells[3][4] = COLOR_BLACK;
	cells[4][3] = COLOR_BLACK;

	bool canPut = true;

	while (1)
	{
		display();

		if (!canPut)
		{
			printf("�����ɂ͒u���܂��� \n");
		}

		printf(" %s �̃^�[���ł�", colorNames[turn]);

		canPut = true;

		switch (_getch())
		{
		case 'w':
			cursorY--;
			break;
		case 's':
			cursorY++;
			break;
		case 'a':
			cursorX--;
			break;
		case 'd':
			cursorX++;
			break;

		default:
			if (checkCanPut(turn, cursorX, cursorY, false))
			{
				// �I�������|�C���g�����s����O�ɐ΂��Ђ�����Ԃ�
				checkCanPut(turn, cursorX, cursorY, true);
				cells[cursorY][cursorX] = turn;
				turn = !turn;

				if (!checkCanPutAll(turn))
				{
					printf("�p�X���܂� \n");
					turn = !turn;
				}
			}
			else
			{
				canPut = false;
			}
			break;
		}

		if ((!checkCanPutAll(COLOR_BLACK)) && (!checkCanPutAll(COLOR_WHITE)))
		{
			int count[COLOR_MAX] = {};

			for (int y = 0; y < BOARD_HEIGHT; y++)
			{
				for (int x = 0; x < BOARD_WIDTH; x++)
				{
					if (COLOR_NONE != cells[y][x])
					{
						count[cells[y][x]]++;
					}

				}
			}

			display();

			for (int i = 0; i < COLOR_MAX; i++)
			{
				printf("%s �F %d\n", colorNames[i], count[i]);
			}

			if (count[COLOR_BLACK] == count[COLOR_WHITE])
			{
				printf("���������ł�\n");
			}
			else if (count[COLOR_BLACK] > count[COLOR_WHITE])
			{
				printf("%s �̏����ł� \n", colorNames[COLOR_BLACK]);
			}
			else
			{
				printf("%s �̏����ł� \n", colorNames[COLOR_WHITE]);
			}

			break;
		}
	}

	//�t�@�C���I�[�v��
	FILE* fp;
	errno_t error = fopen_s(&fp, "result.txt", "w");
	if (error != 0)  return false;

	//�t�@�C����������
	char s_buf[BUFFSIZE];
	sprintf_s(s_buf, "�������̂� %s", colorNames[turn]);
	fputs(s_buf, fp);

	//�t�@�C���N���[�Y
	fclose(fp);

	return 0;
}

void display()
{
	system("cls");
	for (int y = 0; y < BOARD_HEIGHT; y++)
	{
		for (int x = 0; x < BOARD_WIDTH; x++)
		{
			if (cursorX == x && cursorY == y)
			{
				printf("�E");
			}
			else
			{
				switch (cells[y][x])
				{
				case COLOR_NONE:
					printf("��");
					break;
				case COLOR_BLACK:
					printf("�Z");
					break;
				case COLOR_WHITE:
					printf("��");
					break;
				default:
					break;
				}
			}
		}
		printf("\n");
	}
}

bool checkCanPut(int argColor, int argCursorX, int argCursorY, bool argTurnOver)
{
	if (COLOR_NONE != cells[argCursorY][argCursorX])
	{
		return false;
	}

	for (int i = 0; i < DIRECTION_MAX; i++)
	{
		int x = argCursorX;
		int y = argCursorY;

		x += directions[i][0];
		y += directions[i][1];

		if ((!argColor) != cells[y][x])
		{
			continue;
		}

		while (1)
		{
			x += directions[i][0];
			y += directions[i][1];

			if (x < 0 || x >= BOARD_WIDTH || y < 0 || y > BOARD_HEIGHT)
			{
				break;
			}
			if (COLOR_NONE == cells[y][x])
			{
				break;
			}
			if (argColor == cells[y][x])
			{
				if (!argTurnOver)
				{
					return true;
				}

				int turnOverX = argCursorX;
				int turnOverY = argCursorY;

				while (1)
				{
					cells[turnOverY][turnOverX] = argColor;

					turnOverX += directions[i][0];
					turnOverY += directions[i][1];

					if (x == turnOverX && y == turnOverY)
					{
						break;
					}
				}
			}
		}
	}

	return false;
}

bool checkCanPutAll(int argColor)
{
	for (int y = 0; y < BOARD_HEIGHT; y++)
	{
		for (int x = 0; x < BOARD_WIDTH; x++)
		{
			if (checkCanPut(argColor, x, y, false))
			{
				return true;
			}
		}
	}

	return false;
}