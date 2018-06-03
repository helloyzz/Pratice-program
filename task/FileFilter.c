/*
	���ߣ�������
	���ڣ�2018/6/1 
	��ȡ�ļ�������ֽڽ��ж�ȡ���н���
	��ע�ͣ�Ĭ�� ����״̬���й��� 
*/
#include <stdio.h>
#include <stdlib.h>

#define SPACE ' '
#define HT '\t'
#define BREAKLINE '\n'
#define COMMENT '/'
#define STARCOMMENT '*'

//buf��С 
#define BUFFERSIZE 1024
//flag�ĸ���״̬
enum {
	DEFAULT, COMM
};

int flag = DEFAULT;	//������־ 
int starFlag = 0;	//�Ƿ�Ϊ '/**/' ��ʽ��ע�� 
int doubleFlag = 0; //�Ƿ�Ϊ '//' ��ʽ��ע�� 
int index = 0;		//buf���� 
char* buf = NULL;

//������ʼ��buf 
void clearBuffer() {
	int i;
	for(i = 0; i<index; i++) {
		buf[i] = 0;
	}
	index = 0;
}
//��buf�����Ԫ�����Ϊ�ջ򳬳���Χ�򴴽���buf 
void addElement(char c) {
	int i;
	char* temp = NULL;
	if(buf == NULL) buf = (char*)malloc(BUFFERSIZE);
	if(index >= BUFFERSIZE) {
		temp = (char*)malloc(BUFFERSIZE<<2);
		for(i=0; i<index; i++) {
			temp[i] = buf[i];
		}
		free(buf);
		buf = temp;
	}
	buf[index] = c;
	index++;
}
void writeToStream(FILE* fWrite) {
	int i;
	for(i=0; i<index; i++) {
		fputc(buf[i], fWrite);
	}
	clearBuffer();
}
//�ѻس�д���� 
void writeBreakLineToStream(FILE* fWrite) {
	int i;
	for(i=0; i<index; i++) {
		if(buf[i] == BREAKLINE) fputc(buf[i], fWrite);
	}
}

void defaultParse(int c, FILE* fWrite) {
	if(c != SPACE && c != HT) addElement(c);
	if(c == BREAKLINE) {
		writeToStream(fWrite);	
		clearBuffer();
	}
}
void commentParse(int c, FILE* fWrite) {
	int i;
	if( flag == DEFAULT && index ) writeToStream(fWrite); 
	flag = COMM;
	if(c != SPACE && c != HT) {
		addElement(c);
	}
	//û�ж϶��Ƿ�Ϊע�͵�ʱ����� 
	if(!starFlag && !doubleFlag) {
		if( index >= 2 && 
			buf[index-2] == COMMENT && 
			c != STARCOMMENT &&
			c != COMMENT ) {
			flag = DEFAULT;			//�����Ϊע�ͻ�ԭflag״̬ 
		} else if(index >= 2 && buf[index-2] == COMMENT && c == STARCOMMENT) {
			starFlag = 1;
		} else if(index >= 2 && buf[index-2] == COMMENT && c == COMMENT) {
			doubleFlag = 1;
		}
	}
	//ȷ����ע�����buf���ݣ��ָ�flagĬ��ֵ 
	if( index >= 2 && 
		((c == COMMENT && buf[index-2] == STARCOMMENT && starFlag) ||
		(doubleFlag && c == BREAKLINE)) ) {
		starFlag = 0;
		doubleFlag = 0;
		flag = DEFAULT;
		writeBreakLineToStream(fWrite);
		clearBuffer();
	}
}

int main() {
	int c = 0;
	FILE* fRead = NULL;
	FILE* fWrite = NULL;
	char readPath[400] = {0};	//Ҫ��ȡ���ļ� 
	char writePath[400] = {0};	//Ҫд����ļ� 
	printf("read file path: ");
	scanf("%s", readPath);
	printf("write file path: ");
	scanf("%s", writePath);

	fRead = fopen(readPath, "r");
	fWrite = fopen(writePath, "wb");
	if(!fRead && !fWrite) {
		printf("read error!\n");
		return EXIT_FAILURE;
	}
	
	//��ѭ����Դ�ļ���ÿ���ֽڽ��н��� 
    while ((c = fgetc(fRead)) != EOF) {
    	putchar(c);
		if(c == COMMENT || flag == COMM) {  //ע�ͽ���
			commentParse(c, fWrite);
		} else if(flag == DEFAULT) {  //Ĭ�Ͻ���
			defaultParse(c, fWrite);
		}
    }
    //buf��Ϊ��д������ɾ�� 
    if(buf) {
    	writeToStream(fWrite);
		free(buf);	
	}
    fclose(fRead);
    fclose(fWrite);
	return 0;
}
