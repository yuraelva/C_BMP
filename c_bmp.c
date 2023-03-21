#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ビットマップ画像の読み取り
int loadBmp(char fn[]){
  int w,h,bit;
  FILE *fp,*fpout;               // ファイルポインタの宣言
  unsigned char hdr[54];  // ヘッダ格納用の配列

  int i;                  // ループ用変数

  // bmpファイルをバイナリモードで読み取り
  fp = fopen(fn,"r");
  // 画像ファイルが見つからない場合のエラー処理
  if(fp==NULL){
      printf("Not found : %s \n", fn);	exit(-1);
  }
  // ヘッダ情報の読み込み
  for(i=0; i<54; i++){
    	hdr[i] = fgetc(fp);
  }

  // 画像がビットマップで無い場合のエラー処理
  if(!(hdr[0]=='B'&& hdr[1]=='M')){
	    printf("%Not BMP file : &s \n", fn);  exit(-1);
  }

  // ヘッダ情報から画像の幅、高さ、ビットの深さを抽出
  *w = hdr[18] + hdr[19]*256
  *h = hdr[22] + hdr[23]*256;
  *bit = hdr[28];
  int size = *w * *h * *bit/8 + *w%4 * *h; //実際のデータ部のサイズ
  unsigned int bmp[size + 54]; //bmpファイル全体のサイズ
  unsigned char buf[(size + 54) * 2]; //bmpファイル全体を10進数で表し，その一桁ずつを入力する場合のサイズ
  for(i = 0;i<54;i++)bmp[i] = hdr[i];//ヘッダーを代入
  for(i = 0;i<size;i++){
    bmp[i+54]= fgetc(fp);
  }
  int bufnum=0;
  for(i=0;i<size + 54;i++){//10進数を16進数に変換
    int int1 = bmp[i]/16;
    int int2 = bmp[i]%16;
    char hex1,hex2;
    if(int1 >= 10){
      hex1 = 'A' + int1 - 10;
    }
    else{
      hex1 = int1 + '0';
    }
    if(int2 >= 10){
      hex2 = 'A' + int2 - 10;
    }
    else{
      hex2 = int2 + '0';
    }
    buf[bufnum] = hex1;
    buf[bufnum+1] = hex2;
    printf("%c%c ",buf[bufnum],buf[bufnum+1]);
    bufnum += 2;
  }
  buf[bufnum] = '\0';
  //printf("%s\n",buf);
  fclose(fp);
  return 0;
}

int main(int argc,char *argv[]){
    loadBmp(argv[1]);

    return 0;
}
