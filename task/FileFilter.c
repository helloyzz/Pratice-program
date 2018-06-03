/*
	作者：于哲周
	日期：2018/6/1 
	读取文件，逐个字节进行读取进行解析
	有注释，默认 二种状态进行过滤 
*/
#include <stdio.h>
#include <stdlib.h>

#define SPACE ' '
#define HT '\t'
#define BREAKLINE '\n'
#define COMMENT '/'
#define STARCOMMENT '*'

//buf大小 
#define BUFFERSIZE 1024
//flag的各个状态
enum {
	DEFAULT, COMM
};

int flag = DEFAULT;	//解析标志 
int starFlag = 0;	//是否为 '/**/' 形式的注释 
int doubleFlag = 0; //是否为 '//' 形式的注释 
int index = 0;		//buf索引 
char* buf = NULL;

//清理并初始化buf 
void clearBuffer() {
	int i;
	for(i = 0; i<index; i++) {
		buf[i] = 0;
	}
	index = 0;
}
//向buf中添加元素如果为空或超出范围则创建新buf 
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
//把回车写入流 
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
	//没有断定是否为注释的时候进入 
	if(!starFlag && !doubleFlag) {
		if( index >= 2 && 
			buf[index-2] == COMMENT && 
			c != STARCOMMENT &&
			c != COMMENT ) {
			flag = DEFAULT;			//如果不为注释还原flag状态 
		} else if(index >= 2 && buf[index-2] == COMMENT && c == STARCOMMENT) {
			starFlag = 1;
		} else if(index >= 2 && buf[index-2] == COMMENT && c == COMMENT) {
			doubleFlag = 1;
		}
	}
	//确定是注释清除buf数据，恢复flag默认值 
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
	char readPath[400] = {0};	//要读取的文件 
	char writePath[400] = {0};	//要写入的文件 
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
	
	//主循环对源文件的每个字节进行解析 
    while ((c = fgetc(fRead)) != EOF) {
    	putchar(c);
		if(c == COMMENT || flag == COMM) {  //注释解析
			commentParse(c, fWrite);
		} else if(flag == DEFAULT) {  //默认解析
			defaultParse(c, fWrite);
		}
    }
    //buf不为空写入流后删除 
    if(buf) {
    	writeToStream(fWrite);
		free(buf);	
	}
    fclose(fRead);
    fclose(fWrite);
	return 0;
}
