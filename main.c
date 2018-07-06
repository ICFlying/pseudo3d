
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pseudo3D.h"
#include "view.h"

#define SCROLL_DIV  (_3D_PI/16)
#define MOVE_DIV  10

int main(void)
{
    char input[16];

    //初始化一个多边形
    _3D_PointArray_Type *dpat0, *dpat1, *dpat2, *dpat3, *dpat4;

    //XYZ坐标轴
    if((dpat0 = _3D_pointArray_init(6, 
        _3D_XYZ_ScanLen*1.00, 0.00, 0.00, 0x800000, 
        -_3D_XYZ_ScanLen*1.00, 0.00, 0.00, 0x800000, 
        0.00, _3D_XYZ_ScanLen*1.00, 0.00, 0x008080, 
        0.00, -_3D_XYZ_ScanLen*1.00, 0.00, 0x008080, 
        0.00, 0.00, _3D_XYZ_ScanLen*1.00, 0x008000, 
        0.00, 0.00, -_3D_XYZ_ScanLen*1.00, 0x008000
        )) == NULL)
    {
        printf("_3D_pointArray_init failed\r\n");
        return -1;
    }
    _3D_ppLink_add(dpat0, 0x800000, 0, 1, 1);
    _3D_ppLink_add(dpat0, 0x008000, 2, 1, 3);
    _3D_ppLink_add(dpat0, 0x008080, 4, 1, 5);
    _3D_comment_add(dpat0, -_3D_XYZ_ScanLen-20, 0, 4, "X", 0, 0x800000);
    _3D_comment_add(dpat0, _3D_XYZ_ScanLen, 0, 0, "-X", 0, 0x800000);
    _3D_comment_add(dpat0, 0, _3D_XYZ_ScanLen+12, 8, "Y", 0, 0x008080);
    _3D_comment_add(dpat0, 0, -_3D_XYZ_ScanLen-4, 8, "-Y", 0, 0x008080);
    _3D_comment_add(dpat0, 0, 4, _3D_XYZ_ScanLen+16, "Z", 0, 0x008000);
    _3D_comment_add(dpat0, 0, 8, -_3D_XYZ_ScanLen-2, "-Z", 0, 0x008000);

    //指南针
    if((dpat1 = _3D_pointArray_init(6, 
        -30.00, 0.00, 0.00, 0x800000, 
        0.00, 10.00, 0.00, 0x808080, 
        30.00, 0.00, 0.00, 0x008080, 
        0.00, -10.00, 0.00, 0x808080, 
        0.00, 0.00, 10.00, 0x808080, 
        0.00, 0.00, -10.00, 0x808080
        )) == NULL)
    {
        printf("_3D_pointArray_init failed\r\n");
        return -1;
    }
    _3D_ppLink_add(dpat1, 0xFF0000, 0, 2, 1, 3);
    _3D_ppLink_add(dpat1, 0x0080FF, 2, 2, 1, 3);
    _3D_ppLink_add(dpat1, 0xFF0000, 1, 1, 3);
    _3D_ppLink_add(dpat1, 0x808080, 4, 1, 5);
    // _3D_comment_add(dpat1, -30.00, 0.00, 0.00, "N", 0, 0xFF0000);
    // _3D_comment_add(dpat1, 30.00, 0.00, 0.00, "S", 0, 0x0080FF);

    //目标
    if((dpat2 = _3D_pointArray_init(1, 
        0.00, 0.00, 0.00, 0xFFFFFF
        )) == NULL)
    {
        printf("_3D_pointArray_init failed\r\n");
        return -1;
    }
    dpat2->orginConnect = true;
    _3D_comment_add(dpat2, 0.00, 0.00, 0.00, "target", 0, 0xFFFFFF);


    //初始转角
    // dpat2->raxyz[0] = _3D_PI/8;
    // dpat2->raxyz[1] = _3D_PI/8;
    // dpat2->raxyz[2] = _3D_PI/8;

    while(1)
    {
        //
        PRINT_CLEAR();

        //
        _3D_angle_to_xyz(dpat2);
        _3D_angle_to_xyz(dpat1);
        _3D_angle_to_xyz(dpat0);
        
        //    
        _3D_draw3D(VIEW_X_SIZE/2, VIEW_Y_SIZE/2, dpat0);
        _3D_draw3D(VIEW_X_SIZE/2, 30, dpat1);
        _3D_draw3D(VIEW_X_SIZE/2, VIEW_Y_SIZE/2, dpat2);
        
        //
        PRINT_EN();

        // dpat2->raxyz[0] += SCROLL_DIV;
        // dpat2->raxyz[1] += SCROLL_DIV;
        // dpat2->raxyz[2] += SCROLL_DIV;

        if(scanf("%s", input))
        {
            //x scroll
            if(input[0] == '3')
                dpat2->raxyz[0] += SCROLL_DIV*strlen(input);
            else if(input[0] == '1')
                dpat2->raxyz[0] -= SCROLL_DIV*strlen(input);
            //y scroll
            else if(input[0] == 'w')
                dpat2->raxyz[1] += SCROLL_DIV*strlen(input);
            else if(input[0] == '2')
                dpat2->raxyz[1] -= SCROLL_DIV*strlen(input);
            //z scroll
            else if(input[0] == 'q')
                dpat2->raxyz[2] += SCROLL_DIV*strlen(input);
            else if(input[0] == 'e')
                dpat2->raxyz[2] -= SCROLL_DIV*strlen(input);
            
            //z move
            if(input[0] == 's')
                dpat2->mvxyz[2] += MOVE_DIV*strlen(input);
            else if(input[0] == 'x')
                dpat2->mvxyz[2] -= MOVE_DIV*strlen(input);
            //y move
            else if(input[0] == 'z')
                dpat2->mvxyz[1] += MOVE_DIV*strlen(input);
            else if(input[0] == 'c')
                dpat2->mvxyz[1] -= MOVE_DIV*strlen(input);
            //x move
            else if(input[0] == 'd')
                dpat2->mvxyz[0] += MOVE_DIV*strlen(input);
            else if(input[0] == 'a')
                dpat2->mvxyz[0] -= MOVE_DIV*strlen(input);

            //指南针: z scroll
            else if(input[0] == 'v')
                dpat1->raxyz[2] += SCROLL_DIV*strlen(input);
            else if(input[0] == 'b')
                dpat1->raxyz[2] -= SCROLL_DIV*strlen(input);

            else if(input[0] == 'r')
            {
                _3D_reset(dpat0);
                _3D_reset(dpat1);
                _3D_reset(dpat2);
            }
        }

        usleep(100000);
    }
}


