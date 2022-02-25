#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int copyFile(const char* srcPath, const char* destpath)
{
	//�R�s�[���ƃR�s�[�悪����bb
	if (strcmp(srcPath, destpath) == 0)
	{
		return 0;
	}

	int result = 1;

	//�o�C�i�����[�h�ŊJ��
	FILE* fpSrc = fopen(srcPath, "rb");
	FILE* fpDust = fopen(destpath, "wb");
	if (fpSrc == NULL || fpDust == NULL)
	{
		result == 0;
	}
	if (result != 0)
	{
		for (;;)
		{
			char c;
			//1�o�C�g�ǂݍ���
			if (fread(&c, sizeof(c), 1, fpSrc) < 1)
			{
				if (feof(fpSrc))
				{
					break;
				}
				else
				{
					result = 0;
					break;
				}
			}

			//1�o�C�g��������
			if (fwrite(&c, sizeof(c), 1, fpDust) < 1)
			{
				result = 0;
				break;
			}
		}
	}
	if (fpDust != NULL)
	{
		if (fclose(fpDust) == EOF)
		{
			result = 0;
		}
	}
	if (fpSrc != NULL)
	{
		if (fclose(fpSrc) == EOF)
		{
			result = 0;
		}
	}
	return result;
}

int renameFile(const char* oldName, const char* newName)
{
	return !(rename(oldName, newName));
}

int main(void)
{
	FILE* fp;
	char name[100];
	char mozi[100];
	char namenew[100];
	char mozituika[100];
	int i,b,d;
	int a = 1;
	int line = 0;
	char arr[1000][100];
	char ch;
	printf("�ۑ��t�@�C������txt�`���Ŏw�肵�Ă�������->");
	gets_s(name);

	fp = fopen(name, "w");
	if (fp == NULL)
	{
		printf("%s���I�[�v���ł��܂���B\n");
		exit(1);
	}

	while (1)
	{
		printf("��������͂��Ă�������->");
		a = a + 1;
		gets_s(mozi);
		if (mozi[0] == 0)
		{
			break;
		}
		else
		{
			fputs(mozi, fp);
			fputc('\n', fp);
		}
	}
	fclose(fp);
	
	while (1)
	{
		
		printf("1:1�s�ύX 2;1�s�폜 3:�폜 4:�ۑ� 5:���݂̏�� 6:�ǉ� 7:�t�@�C���R�s�[ 8:���O�ύX 9:�I��\n");
		printf("\n�s���������j���[�ԍ���I�����Ă�������->");
		scanf("%d", &i);
		if (i == 1)
		{
			int line = 0;
			printf("\n\n1�s�ύX���I�΂�܂���\n");
			fp = fopen(name, "r");
			if (fp == NULL)
			{
				printf("%s���I�[�v���ł��܂���B\n");
				exit(1);
			}
			printf(" %s�̓��e \n",name);
			while ((ch = fgetc(fp)) != EOF) 
			{
				printf("%c", ch);
			}
			fclose(fp);

			fp = fopen(name, "r");
			if (fp == NULL)
			{
				printf("%s���I�[�v���ł��܂���B\n");
				exit(1);
			}
			for (b = 0; b < sizeof(arr) / sizeof(arr[0]) && fgets(arr[b], sizeof(arr[b]), fp); b++)
			{
				line++;
			}
			fclose(fp);
			while (1)
			{
				printf("�ύX�������s��I�����Ă�������->");
				scanf("%d", &a);
				if (a <= line)
				{
					arr[a - 1][0] = '\0';
					break;
				}
				else
				{
					printf("\n����Ȃɍs���͂���܂���");
				}
			}
			
			fp = fopen(name, "w+");
			if (fp == NULL)
			{
				printf("%s���I�[�v���ł��܂���B\n");
				exit(1);
			}
			for (b = 0; b < line; b++)
			{
				if (arr[b][0] != '\0')
				{
					fputs(arr[b], fp);
				}
				else
				{
						fgets(mozituika, sizeof(mozituika), stdin);
						fprintf(fp, "%s", mozituika);
						if (mozituika[0] == '\n')
						{
							remove(name);
							fp = fopen(name, "w+");
							if (fp == NULL)
							{
								printf("%s���I�[�v���ł��܂���B\n");
								exit(1);
							}
							for (d = 0; d < b; d++)
							{
								if (arr[d][0] != '\0')
								{
									fputs(arr[d], fp);
								}
							}
						}
						
					while (1)
					{
						printf("\n��������͂��Ă�������->");
						a = a + 1;
						gets_s(mozi);
						if (mozi[0] == 0)
						{
							break;
						}
						else
						{
							fputs(mozi, fp);
							fputc('\n', fp);
						}
					}
				}
			}
			fclose(fp);
		}
		else if (i == 2)
		{
			printf("\n\n1�s�폜���I������܂���\n");
			fp = fopen(name, "r");
			if (fp == NULL)
			{
				printf("%s���I�[�v���ł��܂���B\n");
				exit(1);
			}
			printf(" \n%s�̓��e \n", name);
			while ((ch = fgetc(fp)) != EOF)
			{
				printf("%c", ch);
			}
			fclose(fp);
			fp = fopen(name, "r");
			if (fp == NULL)
			{
				printf("%s���I�[�v���ł��܂���B\n");
				exit(1);
			}
			for (b = 0; b < sizeof(arr) / sizeof(arr[0]) && fgets(arr[b], sizeof(arr[b]), fp); b++)
			{
				line++;
			}
			fclose(fp);
			while (1)
			{
				printf("�폜�������s��I�����Ă�������\n");
				printf("�������󔒍s�͍폜�ł��܂���->");
				scanf("%d", &a);
				if (a <= line)
				{
					arr[a - 1][0] = '\0';
					break;
				}
				else
				{
					printf("\n����Ȃɍs���͂���܂���");
				}
			}
			fp = fopen(name, "w+");
			if (fp == NULL)
			{
				printf("%s���I�[�v���ł��܂���B\n");
				exit(1);
			}
			for (b = 0; b < line; b++)
			{
				if (arr[b][0] != '\0')
				{
					fputs(arr[b], fp);
				}
			}
			fclose(fp);
		}
		else if (i == 3)
		{
			printf("\n\n�폜���I�΂�܂���\n");
			printf("\n%s���폜���܂�\n",name);
			if (remove(name) == 0)
			{
				printf("\n%s���폜���܂����B\n", name);
			}
			else
			{
				printf("\n%s���폜�ł��܂���ł����B\n", name);
			}
			printf("\n�v���O�������I�����܂�\n");
			break;
		}
		else if (i == 4)
		{
			printf("\n\n�ۑ����I�΂�܂���\n");
			printf("\n���̏�Ԃ�ۑ����܂���\n");
			fclose(fp);

		}
		else if (i == 5)
		{
			printf("\n\n���݂̏�Ԃ��I�΂�܂���\n");
			fp = fopen(name, "r");
			if (fp == NULL)
			{
				printf("\n%s���I�[�v���ł��܂���B\n");
				exit(1);
			}

			printf(" \n���݂̃e�L�X�g�t�@�C���̓��e \n");
			while ((ch = fgetc(fp)) != EOF) 
			{
				printf("%c", ch);
			}
			fclose(fp);
		}
		else if (i == 6)
		{
			printf("\n\n�ǉ����I�΂�܂���\n");
			fp = fopen(name, "a");
			if (fp == NULL)
			{
				printf("\n%s���I�[�v���ł��܂���B\n");
				exit(1);
			}
			fgets(mozituika, sizeof(mozituika), stdin);
			fprintf(fp, "%s", mozituika);
			while (1)
			{
				printf("\n��������͂��Ă�������\n");
				printf("\n������1�s�󔒍s���ł��܂�->");
				a = a + 1;
				gets_s(mozituika);
				if (mozituika[0] == 0)
				{
					break;
				}
				else
				{
					fputs(mozituika, fp);
					fputc('\n', fp);
				}
			}
			fclose(fp);

			fp = fopen(name, "r");
			if (fp == NULL)
			{
				printf("%s���I�[�v���ł��܂���B\n");
				exit(1);
			}
			for (b = 0; b < sizeof(arr) / sizeof(arr[0]) && fgets(arr[b], sizeof(arr[b]), fp); b++)
			{
				line++;
			}
			fclose(fp);
			
			arr[a - 1][0] = '\0';
			fp = fopen(name, "w+");
			if (fp == NULL)
			{
				printf("%s���I�[�v���ł��܂���B\n");
				exit(1);
			}
			for (b = 0; b <line; b++)
			{
				if (arr[b][0] != '\0')
				{
					fputs(arr[b], fp);
				}
				else
				{
					fgets(mozituika, sizeof(mozituika), stdin);
					fprintf(fp, "%s", mozituika);
					if (mozituika[0] == '\0')
					{
						remove(name);
						fp = fopen(name, "w+");
						if (fp == NULL)
						{
							printf("\n%s���I�[�v���ł��܂���B\n");
							exit(1);
						}
						for (d = 0; d < b; d++)
						{
							if (arr[d][0] != '\0')
							{
								fputs(arr[d], fp);
							}
						}
					}
				}
			}
			fclose(fp);

		}
		else if (i == 7)
		{
			printf("\n\n�t�@�C���R�s�[���I������܂���\n");
			printf("\n�t�@�C����copy.txt��");
			if (copyFile(name, "copy.txt"))
			{
				puts("\n�R�s�[���܂���\n");
			}
			else
			{
				puts("\n�R�s�[�Ɏ��s���܂���\n");
			}
		}

		else if (i == 8)
		{
			printf("\n\n���O�ύX���I������܂���\n");
			printf("\n�t�@�C����new.txt��");
			if (renameFile(name, "new.txt"))
			{
				puts("\n�ύX���܂����B\n");
			}
			else
			{
				puts("\n�ύX�����s���܂����B\n");
			}
		}

		else if (i == 9)
		{
			printf("\n\n�I�����I�΂�܂���\n");
			printf("\n�v���O�������I�����܂�\n");
			break;
		}
		else if (i >= 10)
		{
			printf("\n1�`9�܂ł̒�����I��ł�������\n");
		}
	}
	return 0;
}
