#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int copyFile(const char* srcPath, const char* destpath)
{
	//コピー元とコピー先が同じbb
	if (strcmp(srcPath, destpath) == 0)
	{
		return 0;
	}

	int result = 1;

	//バイナリモードで開く
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
			//1バイト読み込む
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

			//1バイト書き込む
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
	printf("保存ファイル名をtxt形式で指定してください->");
	gets_s(name);

	fp = fopen(name, "w");
	if (fp == NULL)
	{
		printf("%sがオープンできません。\n");
		exit(1);
	}

	while (1)
	{
		printf("文字を入力してください->");
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
		
		printf("1:1行変更 2;1行削除 3:削除 4:保存 5:現在の状態 6:追加 7:ファイルコピー 8:名前変更 9:終了\n");
		printf("\n行いたいメニュー番号を選択してください->");
		scanf("%d", &i);
		if (i == 1)
		{
			int line = 0;
			printf("\n\n1行変更が選ばれました\n");
			fp = fopen(name, "r");
			if (fp == NULL)
			{
				printf("%sがオープンできません。\n");
				exit(1);
			}
			printf(" %sの内容 \n",name);
			while ((ch = fgetc(fp)) != EOF) 
			{
				printf("%c", ch);
			}
			fclose(fp);

			fp = fopen(name, "r");
			if (fp == NULL)
			{
				printf("%sがオープンできません。\n");
				exit(1);
			}
			for (b = 0; b < sizeof(arr) / sizeof(arr[0]) && fgets(arr[b], sizeof(arr[b]), fp); b++)
			{
				line++;
			}
			fclose(fp);
			while (1)
			{
				printf("変更したい行を選択してください->");
				scanf("%d", &a);
				if (a <= line)
				{
					arr[a - 1][0] = '\0';
					break;
				}
				else
				{
					printf("\nそんなに行数はありません");
				}
			}
			
			fp = fopen(name, "w+");
			if (fp == NULL)
			{
				printf("%sがオープンできません。\n");
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
								printf("%sがオープンできません。\n");
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
						printf("\n文字を入力してください->");
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
			printf("\n\n1行削除が選択されました\n");
			fp = fopen(name, "r");
			if (fp == NULL)
			{
				printf("%sがオープンできません。\n");
				exit(1);
			}
			printf(" \n%sの内容 \n", name);
			while ((ch = fgetc(fp)) != EOF)
			{
				printf("%c", ch);
			}
			fclose(fp);
			fp = fopen(name, "r");
			if (fp == NULL)
			{
				printf("%sがオープンできません。\n");
				exit(1);
			}
			for (b = 0; b < sizeof(arr) / sizeof(arr[0]) && fgets(arr[b], sizeof(arr[b]), fp); b++)
			{
				line++;
			}
			fclose(fp);
			while (1)
			{
				printf("削除したい行を選択してください\n");
				printf("しかし空白行は削除できません->");
				scanf("%d", &a);
				if (a <= line)
				{
					arr[a - 1][0] = '\0';
					break;
				}
				else
				{
					printf("\nそんなに行数はありません");
				}
			}
			fp = fopen(name, "w+");
			if (fp == NULL)
			{
				printf("%sがオープンできません。\n");
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
			printf("\n\n削除が選ばれました\n");
			printf("\n%sを削除します\n",name);
			if (remove(name) == 0)
			{
				printf("\n%sを削除しました。\n", name);
			}
			else
			{
				printf("\n%sを削除できませんでした。\n", name);
			}
			printf("\nプログラムを終了します\n");
			break;
		}
		else if (i == 4)
		{
			printf("\n\n保存が選ばれました\n");
			printf("\n今の状態を保存しました\n");
			fclose(fp);

		}
		else if (i == 5)
		{
			printf("\n\n現在の状態が選ばれました\n");
			fp = fopen(name, "r");
			if (fp == NULL)
			{
				printf("\n%sがオープンできません。\n");
				exit(1);
			}

			printf(" \n現在のテキストファイルの内容 \n");
			while ((ch = fgetc(fp)) != EOF) 
			{
				printf("%c", ch);
			}
			fclose(fp);
		}
		else if (i == 6)
		{
			printf("\n\n追加が選ばれました\n");
			fp = fopen(name, "a");
			if (fp == NULL)
			{
				printf("\n%sがオープンできません。\n");
				exit(1);
			}
			fgets(mozituika, sizeof(mozituika), stdin);
			fprintf(fp, "%s", mozituika);
			while (1)
			{
				printf("\n文字を入力してください\n");
				printf("\nしかし1行空白行ができます->");
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
				printf("%sがオープンできません。\n");
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
				printf("%sがオープンできません。\n");
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
							printf("\n%sがオープンできません。\n");
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
			printf("\n\nファイルコピーが選択されました\n");
			printf("\nファイルをcopy.txtに");
			if (copyFile(name, "copy.txt"))
			{
				puts("\nコピーしました\n");
			}
			else
			{
				puts("\nコピーに失敗しました\n");
			}
		}

		else if (i == 8)
		{
			printf("\n\n名前変更が選択されました\n");
			printf("\nファイルをnew.txtに");
			if (renameFile(name, "new.txt"))
			{
				puts("\n変更しました。\n");
			}
			else
			{
				puts("\n変更が失敗しました。\n");
			}
		}

		else if (i == 9)
		{
			printf("\n\n終了が選ばれました\n");
			printf("\nプログラムを終了します\n");
			break;
		}
		else if (i >= 10)
		{
			printf("\n1～9までの中から選んでください\n");
		}
	}
	return 0;
}
