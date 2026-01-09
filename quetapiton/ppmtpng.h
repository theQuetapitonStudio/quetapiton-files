#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static uint32_t crc32(const unsigned char *buf, size_t len) {
    uint32_t crc = ~0;
    size_t i,j;
    for(i=0;i<len;i++){
        crc ^= buf[i];
        for(j=0;j<8;j++)
            crc = (crc >> 1) ^ (0xEDB88320 & -(crc & 1));
    }
    return ~crc;
}

static void write_u32_be(FILE* f, uint32_t v) {
    fputc((v>>24)&0xFF,f);
    fputc((v>>16)&0xFF,f);
    fputc((v>>8)&0xFF,f);
    fputc(v&0xFF,f);
}

static int ppm_to_png(const char* ppm_file, const char* png_file) {
    FILE* f = fopen(ppm_file,"rb");
    if(!f) return 1;

    char format[3];
    int w,h,maxval;
    if(fscanf(f,"%2s\n%d %d\n%d\n", format,&w,&h,&maxval)!=4){ fclose(f); return 2; }
    if(strcmp(format,"P6")!=0){ fclose(f); return 3; }

    size_t data_size = w*h*3;
    unsigned char *data = (unsigned char*) malloc(data_size);
    if(!data){ fclose(f); return 4; }
    if(fread(data,1,data_size,f)!=data_size){ free(data); fclose(f); return 5; }
    fclose(f);

    f = fopen(png_file,"wb");
    if(!f){ free(data); return 6; }

    unsigned char pngsig[8] = {137,80,78,71,13,10,26,10};
    fwrite(pngsig,1,8,f);

    unsigned char ihdr[13];
    ihdr[0]=(w>>24)&0xFF; ihdr[1]=(w>>16)&0xFF; ihdr[2]=(w>>8)&0xFF; ihdr[3]=w&0xFF;
    ihdr[4]=(h>>24)&0xFF; ihdr[5]=(h>>16)&0xFF; ihdr[6]=(h>>8)&0xFF; ihdr[7]=h&0xFF;
    ihdr[8]=8; ihdr[9]=2; ihdr[10]=0; ihdr[11]=0; ihdr[12]=0;

    write_u32_be(f,13); fwrite("IHDR",1,4,f); fwrite(ihdr,1,13,f);

    unsigned char ihdr_crc[17];
    memcpy(ihdr_crc,"IHDR",4); memcpy(ihdr_crc+4,ihdr,13);
    write_u32_be(f, crc32(ihdr_crc,17));

    size_t rowbytes = w*3;
    size_t bufsize = (rowbytes+1)*h + 6;
    unsigned char *buf = (unsigned char*) malloc(bufsize);
    if(!buf){ free(data); fclose(f); return 7; }

    size_t p=0;
    buf[p++] = 0x78; buf[p++] = 0x01; // header zlib
    int y;
    for(y=0;y<h;y++){
        buf[p++]=0; // filtro 0
        memcpy(buf+p,data+y*rowbytes,rowbytes);
        p+=rowbytes;
    }

    uint32_t s1=1,s2=0;
    size_t i;
    for(i=2;i<p;i++){ s1=(s1+buf[i])%65521; s2=(s2+s1)%65521; }
    uint32_t adler=(s2<<16)|s1;
    buf[p++] = (adler>>24)&0xFF; buf[p++] = (adler>>16)&0xFF;
    buf[p++] = (adler>>8)&0xFF; buf[p++] = adler&0xFF;

    write_u32_be(f,p); fwrite("IDAT",1,4,f); fwrite(buf,1,p,f);

    unsigned char *idat_crc = (unsigned char*) malloc(p+4);
    if(!idat_crc){ free(buf); free(data); fclose(f); return 8; }
    memcpy(idat_crc,"IDAT",4); memcpy(idat_crc+4,buf,p);
    write_u32_be(f, crc32(idat_crc,p+4));
    free(idat_crc); free(buf); free(data);

    write_u32_be(f,0); fwrite("IEND",1,4,f);
    write_u32_be(f, crc32((unsigned char*)"IEND",4));

    fclose(f);
    return 0;
}
