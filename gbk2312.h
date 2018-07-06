
#ifndef _GBK2312_H
#define _GBK2312_H

//传入字符串,识别并返回第一个字或字符的点阵数据
// utf8_code : 传入字符串,例如: gbk_getArrayByUtf8("字符A", ...);
// buf : 用来接收点阵数据的指针
// bufLen : buf可用长度
// type : 字体代号, 例如: 160,161,200,201,240,241... 前面两位数代表点阵大小,后面1表示使用粗体,160表示16x16点阵
//返回: -1/失败  其它/识别并使用掉的字节数,通常ascii是1字节,中文是3字节
int gbk_getArrayByUtf8(unsigned char *utf8_code, unsigned char *buf, unsigned int *bufLen, int type);

//接下来要输出的字或字符的宽度(像素)
int gbk_getStringWidthByUtf8(unsigned char *utf8_code, int type, int space);

#endif

