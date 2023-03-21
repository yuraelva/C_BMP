#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// �r�b�g�}�b�v�摜�̓ǂݎ��
int loadBmp(char fn[]){
  int w,h,bit;
  FILE *fp,*fpout;               // �t�@�C���|�C���^�̐錾
  unsigned char hdr[54];  // �w�b�_�i�[�p�̔z��

  int i;                  // ���[�v�p�ϐ�

  // bmp�t�@�C�����o�C�i�����[�h�œǂݎ��
  fp = fopen(fn,"r");
  // �摜�t�@�C����������Ȃ��ꍇ�̃G���[����
  if(fp==NULL){
      printf("Not found : %s \n", fn);	exit(-1);
  }
  // �w�b�_���̓ǂݍ���
  for(i=0; i<54; i++){
    	hdr[i] = fgetc(fp);
  }

  // �摜���r�b�g�}�b�v�Ŗ����ꍇ�̃G���[����
  if(!(hdr[0]=='B'&& hdr[1]=='M')){
	    printf("%Not BMP file : &s \n", fn);  exit(-1);
  }

  // �w�b�_��񂩂�摜�̕��A�����A�r�b�g�̐[���𒊏o
  *w = hdr[18] + hdr[19]*256
  *h = hdr[22] + hdr[23]*256;
  *bit = hdr[28];
  int size = *w * *h * *bit/8 + *w%4 * *h; //���ۂ̃f�[�^���̃T�C�Y
  unsigned int bmp[size + 54]; //bmp�t�@�C���S�̂̃T�C�Y
  unsigned char buf[(size + 54) * 2]; //bmp�t�@�C���S�̂�10�i���ŕ\���C���̈ꌅ������͂���ꍇ�̃T�C�Y
  for(i = 0;i<54;i++)bmp[i] = hdr[i];//�w�b�_�[����
  for(i = 0;i<size;i++){
    bmp[i+54]= fgetc(fp);
  }
  int bufnum=0;
  for(i=0;i<size + 54;i++){//10�i����16�i���ɕϊ�
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
